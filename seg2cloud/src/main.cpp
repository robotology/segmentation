/* 
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Ugo Pattacini, Tanis Mar
 * email:  ugo.pattacini@iit.it, tanis.mar@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iomanip>

#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/math/Math.h>

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::math;


/*******************************************************************************/
class Seg2cloudModule : public RFModule, public PortReader
{
protected:
    vector<cv::Point> contour;
    vector<cv::Point> floodPoints;
    cv::Point seed;
    cv::Rect rect;

    string homeContextPath;
    string savename;
    string fileFormat;
    int fileCount;

    int downsampling;
    double spatial_distance;
    int color_distance;
    Mutex mutex;    
    bool polygon,flood3d,flood,seg;
    bool seedAuto;
    bool saving;

    BufferedPort<ImageOf<PixelMono> > portDispIn;
    BufferedPort<ImageOf<PixelRgb> > portDispOut;
    BufferedPort<ImageOf<PixelRgb> > portImgIn;
    BufferedPort<Bottle> portPointsOut;
    BufferedPort<Bottle> portPoints2DOut;

    Port portSeedIn;
    //Port portContour;
    RpcClient portSFM;
    RpcClient portSeg;
    RpcServer portRpc;

    std::string                         name;               //name of the module

    /*******************************************************************************/
    bool read(ConnectionReader &connection)
    {
        Bottle data; data.read(connection);
        cout << " Read: " << data.toString() << endl;
        if (data.size()>=2)
        {
            LockGuard lg(mutex);
            cv::Point point(data.get(0).asInt(),data.get(1).asInt());
            contour.push_back(point);
            if (contour.size()>12){
                contour.pop_back();               
            }
            seed = point;
        }

        return true;
    }

public:
    /*******************************************************************************/
    bool configure(ResourceFinder &rf)
    {
        name = rf.check("name", Value("seg2cloud"), "Getting module name").asString();

        homeContextPath=rf.getHomeContextPath().c_str();
        savename = rf.check("savename", Value("cloud3D"), "Default file savename").asString();
        saving = rf.check("savingClouds", Value(false), "Toggle save clouds as file").asBool();
        fileFormat = rf.check("format", Value("off"), "Default file format").asString();
        seedAuto = rf.check("seedAuto", Value(true), "Automatic seed computation").asBool();


        cout << "Files will be saved in "<< homeContextPath << " folder, as " << savename <<"N." << fileFormat <<", with increasing numeration N"  << endl;
        fileCount = 0;

        downsampling=std::max(1,rf.check("downsampling",Value(1)).asInt());
        spatial_distance=rf.check("spatial_distance",Value(0.005)).asDouble();
        color_distance=rf.check("color_distance",Value(6)).asInt();


        printf("Opening ports\n" );
        bool ret= true;
        ret = ret && portDispIn.open("/"+name+"/disp:i");
        ret = ret && portImgIn.open("/"+name+"/img:i");
        ret = ret && portSeedIn.open("/"+name+"/seed:i");        

        ret = ret && portPointsOut.open("/"+name+"/pnt:o");
        ret = ret && portPoints2DOut.open("/"+name+"/pnt2D:o");
        ret = ret && portDispOut.open("/"+name+"/disp:o");

        ret = ret && portSFM.open("/"+name+"/SFM:rpc");
        ret = ret && portSeg.open("/"+name+"/seg:rpc");
        ret = ret && portRpc.open("/"+name+"/rpc:i");

        if (!ret){
            printf("Problems opening ports\n");
            return false;
        }
        printf("Ports opened\n");

        portSeedIn.setReader(*this);
        attach(portRpc);

        polygon=flood3d=flood=seg=false;

        seed.x = -1; seed.y = -1;       // Negativ values mean undefined seed

        rect = cv::Rect(1, 1, 0,0);

        return true;
    }

    /*******************************************************************************/
    bool interruptModule()
    {
        portDispIn.interrupt();
        portDispOut.interrupt();
        portImgIn.interrupt();
        portPointsOut.interrupt();
        portPoints2DOut.interrupt();
        portSFM.interrupt();
        portSeg.interrupt();
        portRpc.interrupt();
        return true;
    }

    /*******************************************************************************/
    bool close()
    {
        portDispIn.close();
        portDispOut.close();
        portImgIn.close();
        portPointsOut.close();
        portPoints2DOut.close();
        portSFM.close();
        portSeg.close();
        portRpc.close();
        return true;
    }

    /*******************************************************************************/
    double getPeriod()
    {
        return 0.1;
    }

    /*******************************************************************************/
    bool updateModule()
    {
        ImageOf<PixelMono> *imgDispIn=portDispIn.read();
        if (imgDispIn==NULL)
            return false;

        ImageOf<PixelRgb> *imgIn=portImgIn.read();
        if (imgIn==NULL)
            return false;

        LockGuard lg(mutex);
        
        ImageOf<PixelRgb> &imgDispOut=portDispOut.prepare();
        imgDispOut.resize(imgDispIn->width(),imgDispIn->height());

        cv::Mat imgInMat=cv::cvarrToMat((IplImage*)imgIn->getIplImage());
        cv::Mat imgDispInMat=cv::cvarrToMat((IplImage*)imgDispIn->getIplImage());
        cv::Mat imgDispOutMat=cv::cvarrToMat((IplImage*)imgDispOut.getIplImage());
        cv::cvtColor(imgDispInMat,imgDispOutMat,CV_GRAY2RGB);

        vector<vector<cv::Point> > contours;
        contours.push_back(contour);
        cv::drawContours(imgDispOutMat,contours,0,cv::Scalar(255,255,0));
        cv::rectangle(imgDispOutMat,rect,cv::Scalar(255,50,0));

        if ((seed.x>0) && (seed.y>0)){
            clearRec();
            cv::circle(imgDispOutMat,seed, 3,cv::Scalar(0,0,255), 2);

        }

        if (polygon||flood3d||flood||seg){

            clearRec();

            // Create variables to store points in any case
            Bottle &bpoints=portPointsOut.prepare();            
            vector<Vector> points;

            if (polygon){
                if (contour.size()>3)
                {
                    cout << "3D points from selected contour "<<endl;

                    pointsFromContour(imgIn, contour, rect, points, bpoints);

                    cout << "Retrieved " << points.size() << " 3D points"  <<endl;

                    contour.clear();

                }else{
                    cout << "Please select a polygon on the image before calling 'polygon' " << endl;
                }


            } else if (flood3d)
            {
                 cout << "Getting seed "<<endl;


                if (seedAuto){  // Autoseed overwrites present values of 'seed'
                    if(!getDepthSeed(imgDispInMat,seed)){
                        portPointsOut.unprepare();
                        portDispOut.write();
                        return true;
                    }
                }else
                // Wait for click only if seed is not auto and coords have not been given by command or on a previous click.
                if ((seed.x<0) && (seed.y<0))
                {
                    cout << " click for a seed" << endl;
                    portPointsOut.unprepare();
                    portDispOut.write();
                    return true;
                }
                // If none of the conditions apply, means seed was either given by command or clicked before.

                cout << "3D points flood3D "<<endl;

                // Use the seed point to get points from SFM with the Flood3D command, and spatial_distance given
                Bottle cmdSFM,replySFM;
                cmdSFM.addString("Flood3D");
                cmdSFM.addInt(seed.x);
                cmdSFM.addInt(seed.y);
                cmdSFM.addDouble(spatial_distance);                
                bool ok = portSFM.write(cmdSFM,replySFM);                
                if (ok)
                {
                    for (int i=0; i<replySFM.size(); i+=5)
                    {
                        int x=replySFM.get(i+0).asInt();
                        int y=replySFM.get(i+1).asInt();
                        PixelRgb px=imgIn->pixel(x,y);

                        Vector point(6,0.0);
                        point[0]=replySFM.get(i+2).asDouble();
                        point[1]=replySFM.get(i+3).asDouble();
                        point[2]=replySFM.get(i+4).asDouble();
                        point[3]=px.r;
                        point[4]=px.g;
                        point[5]=px.b;

                        points.push_back(point);
                        floodPoints.push_back(cv::Point(x,y));

                        Bottle &bpoint = bpoints.addList();
                        bpoint.addDouble(point[0]);
                        bpoint.addDouble(point[1]);
                        bpoint.addDouble(point[2]);
                    }
                    cout << "Retrieved " << points.size() << " 3D points"  <<endl;
                }else{
                    cout << " SFM didn't reply" << endl;
                    return true;
                }
            }


            else if (flood)
            {
                // Get or read seed
                if ((seed.x<0) && (seed.y<0))
                {
                    cout << " click for a seed" << endl;
                    portPointsOut.unprepare();
                    portDispOut.write();
                    return true;
                }

                cout << "Extracting 3D points from 2D color flood blob"<<endl;
                // Set flooding parameters
                //PixelMono c = imgDispIn->pixel(seed.x,seed.y);
                cv::Scalar delta(color_distance);

                // flood region and copy flood onto mask
                cv::Mat mask = cv::Mat::zeros(imgInMat.rows + 2, imgInMat.cols + 2, CV_8U);
                cv::floodFill(imgDispInMat, mask, seed, cv::Scalar(255), NULL, delta, delta,  4 + (255 << 8) | cv::FLOODFILL_FIXED_RANGE| cv::FLOODFILL_MASK_ONLY);

                // Get the contours of the color flooded region from mask.
                vector<vector<cv::Point> > contoursFlood;
                vector<cv::Vec4i> hierarchy;
                cv::findContours(mask, contoursFlood, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                vector<cv::Point> contourFlood = contoursFlood[0];

                // Get the 3D points from the 2D points within the contour.
                pointsFromContour(imgIn, contourFlood, rect, points, bpoints);

                cout << "Retrieved " << points.size() << " 3D points"  <<endl;
            }

            else if (seg)
            {
                // Wait for click only if seed is not auto and coords have not been given by command or on a previous click.
                if ((seed.x<0) && (seed.y<0))
                {
                    cout << " click for a seed" << endl;
                    portPointsOut.unprepare();
                    portDispOut.write();
                    return true;
                }
                // If none of the conditions apply, means seed was either given by command or clicked before.

                cout << "Extracting 3D points from segmented blob "<<endl;

                // Get segmented region from external segmentation module
                Bottle cmdSeg, replySeg;
                cmdSeg.addString("get_component_around");
                cmdSeg.addInt(seed.x);
                cmdSeg.addInt(seed.y);
                if (portSeg.write(cmdSeg,replySeg))
                {
                    Bottle* pixelList=replySeg.get(0).asList();

                    if (pixelList->size()==0)
                    {
                        cout << "Empty bottle received" <<endl;
                        seg=false;
                        points.clear();
                        bpoints.clear();
                        portPointsOut.write(); // Return empty bottle if no data was received.
                        return true;
                    }

                    cout << "Read " << pixelList->size() << " points from segmentation algorithm" <<endl;
                    cv::Mat binImg = cv::Mat(imgDispInMat.rows, imgDispInMat.cols, CV_8U, 0.0);
                    for (int i=0; i<pixelList->size(); i++)
                    {
                        Bottle* point=pixelList->get(i).asList();
                        int x = point->get(0).asDouble();
                        int y = point->get(1).asDouble();
                        binImg.at<uchar>(y,x) = 255;
                    }

                    // Get the contours of the segmented region.
                    vector<vector<cv::Point> > contoursSeg;
                    vector<cv::Vec4i> hierarchy;
                    cv::findContours(binImg, contoursSeg, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
                    vector<cv::Point> contourSeg = contoursSeg[0];
                    //cout << "Contours extracted."  <<endl;

                    // Get the 3D points from the 2D points within the contour.
                    pointsFromContour(imgIn, contourSeg, rect, points, bpoints);

                    cout << "Retrieved " << points.size() << " 3D points"  <<endl;
                }else{

                    cout << "Segmentation module did not provide reply" << endl;
                    return true;
                }
            }

            //------------------------//
            // Send and/or  save points
            if (points.size()>0)
            {
                if (saving){
                    saveCloud(points);
                }
                for (int t = 0; t < 10; t++){
                    portPointsOut.write();
                    cout << " 3D points sent time" << t << endl;
                    Time::delay(0.2);
                }

            }else {
                portPointsOut.unprepare();                
            }

            seed.x = -1; seed.y = -1; // Reset seed after each rec call
            polygon=flood=flood3d=seg=false;
            points.clear();
            bpoints.clear();
        }        

        if (floodPoints.size()>0){
            PixelRgb color(130,255,0);
            Bottle &bpoints2D = portPoints2DOut.prepare();
            bpoints2D.clear();
            for (size_t i=0; i<floodPoints.size(); i++){
                imgDispOut.pixel(floodPoints[i].x,floodPoints[i].y)=color;
                Bottle &bpoint2D = bpoints2D.addList();
                // Remember that cv::Points are (x =column, y = row) and YARP coords are (u = row, v = column)
                bpoint2D.addInt(floodPoints[i].x);
                bpoint2D.addInt(floodPoints[i].y);

            }
            // Send images and 2D points for a second
            for (int t = 0; t < 10; t++){
                portDispOut.write();
                portPoints2DOut.write();
                cout << " 2D points sent time" << t << endl;
                Time::delay(0.2);
            }
            floodPoints.clear();
            return true;
        }else{ 
            portPoints2DOut.unprepare();
        }


        portDispOut.write();
        return true;
    }


    /*******************************************************************************/
    bool saveCloud(const vector<Vector> &points)
    {
        ofstream fout;
        stringstream fileName;
        string fileNameFormat;
        fileName.str("");
        fileName << homeContextPath + "/" + savename.c_str() << fileCount;

        if (fileFormat == "ply")
        {
            fileNameFormat = fileName.str()+".ply";
            cout << "Saving as " << fileNameFormat << endl;
            fout.open(fileNameFormat.c_str());
            if (fout.is_open())
            {
                fout << "ply\n";
                fout << "format ascii 1.0\n";
                fout << "element vertex " << points.size() <<"\n";
                fout << "property float x\n";
                fout << "property float y\n";
                fout << "property float z\n";
                fout << "property uchar diffuse_red\n";
                fout << "property uchar diffuse_green\n";
                fout << "property uchar diffuse_blue\n";
                fout << "end_header\n";

                for (unsigned int i=0; i<points.size(); i++){
                    fout << points[i][0] << " " <<      points[i][1] << " " <<      points[i][2] << " " << (int)points[i][3] << " " << (int)points[i][4] << " " << (int)points[i][5] << "\n";
                    //plyfile << cloud->at(i).x << " " << cloud->at(i).y << " " << cloud->at(i).z << " " << (int)cloud->at(i).r << " " << (int)cloud->at(i).g << " " << (int)cloud->at(i).b << "\n";
                }

                fout.close();
                cout << "Points saved as " << fileNameFormat << endl;
                fileCount++;
            }

        }else if (fileFormat == "off"){
            fileNameFormat = fileName.str()+".off";
            cout << "Saving as " << fileNameFormat << endl;
            fout.open(fileNameFormat.c_str());
            if (fout.is_open())
            {

                fout<<"COFF"<<endl;
                fout<<points.size()<<" 0 0"<<endl;
                fout<<endl;
                for (size_t i=0; i<points.size(); i++)
                {
                    fout<<points[i].subVector(0,2).toString(3,4).c_str()<<" "<<
                          points[i].subVector(3,5).toString(0,3).c_str()<<endl;
                }
                fout<<endl;
            }

            fout.close();
            cout << "Points saved as " << fileNameFormat << endl;
            fileCount++;

        }else if (fileFormat == "none"){
            cout << "Points not saved" << endl;
        }
    }


    /*******************************************************************************/
    bool pointsFromContour(const ImageOf<PixelRgb> *imgIn, const vector<cv::Point> contourIn, cv::Rect &boundBox, vector<Vector> &pointsInContour, Bottle &bpoints)
    {
        boundBox = cv::boundingRect(contourIn);

        Bottle cmd,reply;
        cmd.addString("Rect");
        cmd.addInt(boundBox.x);     cmd.addInt(boundBox.y);
        cmd.addInt(boundBox.width); cmd.addInt(boundBox.height);
        cmd.addInt(downsampling);
        if (portSFM.write(cmd,reply))
        {
            int idx=0;
            for (int x=boundBox.x; x<boundBox.x+boundBox.width; x+=downsampling)
            {
                for (int y=boundBox.y; y<boundBox.y+boundBox.height; y+=downsampling)
                {
                    if (cv::pointPolygonTest(contourIn,cv::Point2f((float)x,(float)y),false)>0.0)
                    {                        
                        floodPoints.push_back(cv::Point(x,y));

                        Vector point(6,0.0);
                        point[0]=reply.get(idx+0).asDouble();
                        point[1]=reply.get(idx+1).asDouble();
                        point[2]=reply.get(idx+2).asDouble();

                        Bottle &bpoint = bpoints.addList();
                        bpoint.addDouble(point[0]);
                        bpoint.addDouble(point[1]);
                        bpoint.addDouble(point[2]);

                        if (norm(point)>0.0)
                        {
                            PixelRgb px=imgIn->pixel(x,y);
                            point[3]=px.r;
                            point[4]=px.g;
                            point[5]=px.b;

                            bpoint.addDouble(point[3]);
                            bpoint.addDouble(point[4]);
                            bpoint.addDouble(point[5]);

                            pointsInContour.push_back(point);
                        }
                    }

                    idx+=3;
                }
            }
        }
    }



    /*******************************************************************************/
    bool getDepthSeed(cv::Point2i &seedPoint)
    {
        ImageOf<PixelMono> *imgDispIn=portDispIn.read();
        if (imgDispIn==NULL)
            return false;

        cv::Mat imgDispInMat=cv::cvarrToMat((IplImage*)imgDispIn->getIplImage());

        return getDepthSeed(imgDispInMat,seedPoint);
    }


    bool getDepthSeed(const cv::Mat &disparity,cv::Point2i &seedPoint)
    {
        cout << "Finding seed automatically" << endl;
        cv::Mat depth = disparity.clone();

        /* Filter */
        int gaussSize = 5;
        double sigmaX1 = 1.5;
        double sigmaY1 = 1.5;
        cv::GaussianBlur(depth, depth, cv::Size(gaussSize,gaussSize), sigmaX1, sigmaY1);

        cv::threshold(depth, depth, 30, -1, CV_THRESH_TOZERO);

        int dilate_niter = 4;
        int erode_niter = 2;
        double sigmaX2 = 2;
        double sigmaY2 = 2;

        cv::dilate(depth, depth, cv::Mat(), cv::Point(-1,-1), dilate_niter, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());

        cv::GaussianBlur(depth, depth, cv::Size(gaussSize,gaussSize), sigmaX2, sigmaY2, cv::BORDER_DEFAULT);

        cv::erode(depth, depth, cv::Mat(), cv::Point(-1,-1), erode_niter, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());


        /* Find closest valid blob */
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;

        int fillFlags = 8 | ( 255 << 8 ) | cv::FLOODFILL_FIXED_RANGE; // flags for floodFill

        cv::Mat aux = depth.clone();

        int minBlobSize = 300;
        int fillSize = 0;
        int imageThreshRatioLow = 10;
        int imageThreshRatioHigh = 20;
        while (fillSize < minBlobSize){

            cv::minMaxLoc( aux, &minVal, &maxVal, &minLoc, &maxLoc );

            // if its too small, paint it black and search again
            fillSize = floodFill(aux, maxLoc, 0, 0, cv::Scalar(maxVal/imageThreshRatioLow), cv::Scalar(maxVal/imageThreshRatioHigh), fillFlags);

        }
        // paint closest valid blob white
        cv::Mat fillMask(depth.rows+2, depth.cols+2, CV_8U);
        fillMask.setTo(0);
        cv::floodFill(depth, fillMask, maxLoc, 255, 0, cv::Scalar(maxVal/imageThreshRatioLow), cv::Scalar(maxVal/imageThreshRatioHigh), cv::FLOODFILL_MASK_ONLY + fillFlags);

        /* Find contours */
        std::vector<std::vector<cv::Point > > contours;
        std::vector<cv::Vec4i> hierarchy;

        // use aux because findContours modifies the input image
        aux = fillMask(cv::Range(1,depth.rows+1), cv::Range(1,depth.cols+1)).clone();
        cv::findContours( aux, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );


        /* If any blob is found check again that only the biggest valid blob is selected */
        int blobI = -1;
        double blobSizeOld = -1, blobSize = -1;
        for( int c = 0; c < contours.size(); c++ ){

            // find the area of contour
            blobSize = cv::contourArea(contours[c]);

            // select only the biggest valid blob
            if( blobSize > minBlobSize && blobSize > blobSizeOld)
            {
                blobI = c;
                blobSizeOld = blobSize;
            }
        }

        /* If any blob is found (after the double-check) */
        if (blobI>=0)
        {
            /* Get the Bounding Box */
            cv::Rect blobBox = cv::boundingRect(contours[blobI]);

            double seedValid = -1;      // false
            cv::Point2i seedAux;
            seedAux.x = blobBox.tl().x;
            seedAux.y = blobBox.tl().y;
            while (seedValid < 0){              // Move diagonally through the image until a point inside the blob is found.
                seedAux.x = seedAux.x + 4;
                seedAux.y = seedAux.y + 1;


                cv::circle(depth, seedAux, 1, cv::Scalar(0,0,0),2);

                if ((seedAux.x > blobBox.br().x ) ||(seedAux.y > blobBox.br().y )){
                    cout << "Seed could not be found"<< endl;
                    return false;
                }

                seedValid = pointPolygonTest(contours[blobI], seedAux, false );
            }

            seedPoint.x = seedAux.x+2;     // add a small margin to be fully inside the contour
            seedPoint.y = seedAux.y+2;

            cout << "Seed found at " << seedPoint.x << " ," << seedPoint.y << endl;

            return true;
        }else{
            cout << "Seed could not be determined " << endl;
            return false;
        }
    }


    /*******************************************************************************/
    void clearRec()
    {
        //contour.clear();
        floodPoints.clear();
        rect = cv::Rect(1,1,0,0);

        return;
    }


    /*******************************************************************************/
    bool respond(const Bottle &command, Bottle &reply)
    {
        string cmd=command.get(0).asString().c_str();
        int ack=Vocab::encode("ack");
        int nack=Vocab::encode("nack");

        if (cmd=="clear")
        {
            clearRec();
            reply.addVocab(ack);
            return true;
        }

        else if (cmd=="seedAuto"){
            seedAuto = command.get(1).asBool();
            cout << "Automatic seeding is " << seedAuto << endl;
            reply.addVocab(ack);
            return true;
        }

        else if (cmd=="saving"){
            saving = command.get(1).asBool();
            cout << "Saving clouds as files is " << saving << endl;
            reply.addVocab(ack);
            return true;
        }

        else if (cmd=="setFormat")
        {
            if (command.size()>=2){
                string format = command.get(1).asString();
                if ((format=="ply")||(format=="off")||(format=="none")){
                    fileFormat = format;
                    reply.addVocab(ack);
                    reply.addString("Format set correctly");
                } else {
                    reply.addVocab(nack);
                    reply.addString("No valid format chosen. Choose ply/off/none");
                }
            }
        }

        else if (cmd=="setFileName")
        {
            if (command.size()>=2){
                savename = command.get(1).asString();
                reply.addVocab(ack);
                reply.addString("File Name set correctly");
            }
        }

        else if (cmd=="help")
        {
            reply.addVocab(Vocab::encode("many"));
            reply.addString("Available commands are:");
            reply.addString("help - produces this help");
            reply.addString("clear - Clears displays and saved points");
            reply.addString("setFormat string(fileformat)- Sets the format in which the points will be saved. 'fileformat' can be  'ply', 'off' or 'none'.");
            reply.addString("setFileName string(filename)- Sets the base name given to the files where the 3D points will be saved. ");
            reply.addString("saving (bool) - Activates/deactivated saving each reconstructed cloud in file.");
            reply.addString("---------- Extraction Methods -----------");
            reply.addString("polygon - Gets pointcloud from the selected polygon on the disp image");
            reply.addString("flood int(color_distance) int int (coords(opt))- Gets pointcloud from 2D color flood using the parameter color_distance. Optionally coords can be given by command.");
            reply.addString("flood3d double(spatial_distance) int int (coords(opt))- gets pointcloud from 3D color flood (based on depth with parameter spatial_distance). Optionally coords can be given by command.");
            reply.addString("seg int int (coords(opt))- gets pointcloud from an externally segmented blob. Optionally coords can be given by command.");
            reply.addString("seedAuto (bool) - Toggles from manual (click) seed to 'automatic' one for flood3d");
            return true;
        }

        else if ((cmd=="polygon") || (cmd=="flood3d")|| (cmd=="flood")|| (cmd=="seg"))
        {
            if (portSFM.getOutputCount()==0)
                reply.addVocab(nack);
            else
            {
                LockGuard lg(mutex);
                if (cmd=="polygon")
                {
                    if (contour.size()>2)
                    {
                        polygon=true;
                        reply.addVocab(ack);
                    }
                    else
                        reply.addVocab(nack);
                }
                else if (cmd=="flood3d")
                {

                    contour.clear();
                    floodPoints.clear();
                    if (command.size()>=2){
                        spatial_distance=command.get(1).asDouble();                        
                    }


                    if (seedAuto) // Autoseed overwrites present values of 'seed'
                    {
                        if(!getDepthSeed(seed))
                        {
                            cout << "couldnt retrieve autoseed "<< endl;
                        }

                    }else if (command.size()>=4){
                        seed.x=command.get(2).asInt();
                        seed.y=command.get(3).asInt();

                    }else if ((seed.x <0) && (seed.y<0)){
                        cout << "seed needs to be clicked" << endl;
                    }

                    reply.addVocab(ack);
                    // Remember that cv::Points are (x =column, y = row) and YARP coords are (u = row, v = column)
                    reply.addInt(seed.x);
                    reply.addInt(seed.y);
                    reply.addDouble(spatial_distance);
                    flood3d=true;

                }
                else if (cmd=="flood")
                {
                    reply.addVocab(ack);
                    contour.clear();
                    floodPoints.clear();
                    if (command.size()>=2){
                        color_distance=command.get(1).asInt();
                        reply.addInt(color_distance);
                    }

                    if (command.size()>=4){
                        seed.x=command.get(2).asInt();
                        seed.y=command.get(3).asInt();
                        reply.addInt(seed.x);
                        reply.addInt(seed.y);
                    }
                    flood=true;

                }
                else if (cmd=="seg")
                {
                    contour.clear();
                    reply.addVocab(ack);
                    if (command.size()>=3){
                        seed.x=command.get(1).asInt();
                        seed.y=command.get(2).asInt();
                        reply.addInt(seed.x);
                        reply.addInt(seed.y);
                    }                   
                    seg=true;
                    
                }
            }
        }


        else 
            RFModule::respond(command,reply);
        
        return true;
    }
};


/*******************************************************************************/
int main(int argc,char *argv[])
{   
    Network yarp;
    if (!yarp.checkNetwork())
    {
        yError("unable to find YARP server!");
        return 1;
    }

    Seg2cloudModule mod;
    ResourceFinder rf;
    rf.setDefaultContext("seg2cloud");
    rf.configure(argc,argv);
    return mod.runModule(rf);
}

