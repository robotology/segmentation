/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Vadim Tikhanoff, Carlo Ciliberto
 * email:  vadim.tikhanoff@iit.it
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

/**
\defgroup blobExtractor Blob Extractor
 Module that uses the data from the lumaChroma module to extract blobs that are available.
 \ref blobExtractor application.

 \section intro_sec Description
 This module is responsible for extracting all the blobs 
 based upon the \ref lumaChroma module. To this end, it receives 
 an image input from the lumaChroma and acts upon it to retreive 
 the blobs and their moments (orientation and principal axes)
 
 The commands sent as bottles to the module port
 /<modName>/rpc are the following:
 
 (notation: [.] identifies a vocab, <.> specifies a double,
 "." specifies a string)

 <b>THRESH</b> \n
 format: [thresh] <10.0> \n
 action: Applies a fixed-level threshold to each array element, defaults 10.0 (input array is the image).
 reply: ok
 
 <b>ERODE</b> \n
 format: [erode] <8.0> \n
 action: Erodes an image by using a specific structuring element, defaults 8.0.
 reply: ok
 
 <b>DILATE</b> \n
 format: [dilate] <3.0> \n
 action: Dilates an image by using a specific structuring element., defaults 3.0.
 reply: ok
 
 \section lib_sec Libraries
 - YARP libraries, OpenCV.
 
 \section portsc_sec Ports Created
 - \e /<modName>/img:i receives the image acquired from the
 lumaChroma module previously specified through the command-line
 parameters.
 
 - \e /<modName>/img:o streams out the binary images displaying all blobs.
 
 - \e /<modName>/propImg:o streams out the camera image propagated for synchronisation.

 - \e /<modName>/blobs:o streams out a yarp list containing all the blobs information, such as bounding box and moments if selected.

 - \e /<modName>/binary:o streams out a cleaned binary image containing only blobs detected (without noise).

 
 \section parameters_sec Parameters
 --name \e name
 - specify the module stem-name, which is
 \e blobExtractor by default. The stem-name is used as
 prefix for all open ports.
 
 --thresh \e value
 - specify the threshold value. Applies a fixed-level threshold to each array element. The default value is 10.0.
 
 --erode_itr \e value
 - specify the erode value. Erodes an image by using a specific structuring element. The default value is 8.0.
 
 --dilate_itr \e value
 - specify the dilate value. Dilates an image by using a specific structuring element. The default value is 3.0.
 
 --gaussian_winsize \e value
 - specify the gaussian winsize value for the smoothing of the image. The default value is 9.0.
 
 --window_ratio \e value
 - specify the window_ratio value. The default value is 0.6.

 --details \e string
 - specify the details option. If set to on it provides information on the orientation and principal axes for each blob sent to the /<modName>/blobs:o port. The default value is off.
 
 --maxHeight \e value
 - specify the maxHeight value. This sets the value for the max height of the blob extraction. The default value is 150.

 --maxWidth \e value
 - specify the maxWidth value. This sets the value for the max width of the blob extraction. The default value is 150.
 
 
 \section tested_os_sec Tested OS
 Windows, Linux, Mac OS

 \author Vadim Tikhanoff
 */
 
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/os/Stamp.h>

#include <yarp/sig/Image.h>
#include <yarp/sig/Vector.h>

#include <yarp/cv/Cv.h>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <mutex>

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::cv;

class BlobDetectorThread: public PeriodicThread
{
private:
    ResourceFinder                   &rf;

    BufferedPort<ImageOf<PixelMono>> port_i_img;
    BufferedPort<Image>              port_i_propImg; // extra port just to propagate image
    Port                             port_o_img;
    Port                             port_o_propImg;
    Port                             port_o_blobs;
    Port                             port_o_clean;
    cv::Mat                          imgProp;

    int                              gaussian_winsize;
                                     
    double                           window_ratio;
    double                           thresh;
    int                              erode_itr;
    int                              dilate_itr;
    int                              maxHeight;
    int                              maxWidth;
                                     
    mutex                            mtx;
    mutex                            contours;
    Bottle                           blobs;
    Bottle                           non_blobs;
                                     
    int                              offset;
                                     
    Vector                           area, orientation, axe1, axe2;
    int                              numBlobs;
                                     
    cv::Point                        tmpCenter[500], pt1, pt2;
    int                              numObj;
    double                           thetatmp;

public:
    BlobDetectorThread(ResourceFinder &_rf)
        :PeriodicThread(0.005),rf(_rf) { }
    
    string details;

    virtual bool threadInit()
    {
        string name=rf.find("name").asString();

        port_i_img.open("/"+name+"/img:i");
        port_i_propImg.open("/"+name+"/propImg:i");
        port_o_img.open("/"+name+"/img:o");
        port_o_propImg.open("/"+name+"/propImg:o");

        port_o_blobs.open("/"+name+"/blobs:o");
        port_o_clean.open("/"+name+"/binary:o");

        gaussian_winsize=rf.check("gaussian_winsize",Value(9)).asInt32();

        thresh=rf.check("thresh",Value(10.0)).asFloat64();
        erode_itr=rf.check("erode_itr",Value(8)).asInt32();
        dilate_itr=rf.check("dilate_itr",Value(3)).asInt32();
        window_ratio=rf.check("window_ratio",Value(0.6)).asFloat64();

        maxHeight = rf.check("maxHeight",Value(150)).asInt32();
        maxWidth  = rf.check("maxWidth",Value(150)).asInt32();
        
        details=rf.check("details",Value("off")).asString();

        offset=rf.check("offset",Value(0)).asInt32();
        //details = false;
        numBlobs = 0;
        orientation.clear();
        axe1.clear();
        axe2.clear();
        area.clear();
        area.resize(500);
        orientation.resize(500);
        axe1.resize(500);
        axe2.resize(500);

        return true;
    }

    virtual void setThreshold(double newThreshold)
    {
        lock_guard<mutex> lg(mtx);
        thresh = newThreshold;
    }

    virtual void run()
    {
        if (ImageOf<PixelMono> *img=port_i_img.read(false))
        {
            Stamp ts;
            port_i_img.getEnvelope(ts);

            cv::Mat gray=toCvMat(*img);
            cv::Mat imgProp=gray.clone();
            imgProp.setTo(cv::Scalar::all(0));

            cv::GaussianBlur(gray,gray,cv::Size(gaussian_winsize,gaussian_winsize),0.0);
            cv::threshold(gray,gray,thresh,255.0,cv::THRESH_BINARY);
            cv::equalizeHist(gray,gray); //normalize brightness and increase contrast
            cv::erode(gray,gray,cv::Mat(),cv::Point(-1,-1),erode_itr);
            cv::dilate(gray,gray,cv::Mat(),cv::Point(-1,-1),dilate_itr);

            lock_guard<mutex> lg(mtx);
            blobs.clear();
            non_blobs.clear();

            int w_offset=cvRound(0.5*gray.size().width*(1.0-window_ratio));
            int h_offset=cvRound(0.5*gray.size().height*(1.0-window_ratio));
            int itr = 0;
            for (int row=h_offset; row<gray.size().height-h_offset; row++)
            {
                for (int col=w_offset; col<gray.size().width-w_offset; col++)
                {
                    if (gray.at<uchar>(row,col)==255)
                    {
                        cv::Rect comp;
                        cv::floodFill(gray,cv::Point(col,row),cv::Scalar(255-(blobs.size()+non_blobs.size()+1)),&comp);

                        if (5<comp.width && comp.width<maxWidth && 5<comp.height && comp.height<maxHeight)
                        {
                            Bottle &b=blobs.addList();
                            b.addFloat64(comp.x-offset);
                            b.addFloat64(comp.y-offset);
                            b.addFloat64(comp.x+comp.width+offset);
                            b.addFloat64(comp.y+comp.height+offset);
                            if (details=="on")
                            {
                                if (orientation.size() > 0 )
                                {
                                    b.addFloat64(orientation[itr+1]);
                                    b.addInt32((int)axe2[itr+1]);
                                    b.addInt32((int)axe1[itr+1]);
                                }                         
                            }
                            itr++;
                        }
                        else
                        {
                            Bottle &n=non_blobs.addList();
                            n.addFloat64(comp.x-offset);
                            n.addFloat64(comp.y-offset);
                            n.addFloat64(comp.x+comp.width+offset);
                            n.addFloat64(comp.y+comp.height+offset);
                            if (details=="on")
                            {
                                if (orientation.size() > 0 )
                                {
                                    n.addFloat64(orientation[itr+1]);
                                    n.addInt32((int)axe2[itr+1]);
                                    n.addInt32((int)axe1[itr+1]);
                                }                         
                            }
                            itr++;
                        }
                    }
                }
            }

            cleanBlobs(gray);

            if (details=="on")
            {
                lock_guard<mutex> lg(contours);
                processImg(gray);
            }
            
            port_o_img.setEnvelope(ts);
            port_o_img.write(*img);

            port_o_blobs.setEnvelope(ts);
            port_o_blobs.write(blobs);
            Image *prop= port_i_propImg.read(false);  
            
            if (prop!=NULL)
            {
                port_o_propImg.setEnvelope(ts);
                port_o_propImg.write(*prop);
            }

            if (!imgProp.empty())
            {
                ImageOf<PixelMono> sendImg;
                sendImg.resize(imgProp.size().width,imgProp.size().height);
                imgProp.copyTo(toCvMat(sendImg));
                port_o_clean.setEnvelope(ts);
                port_o_clean.write(sendImg);
            }
        }
    }

    virtual void threadRelease()
    {
        port_i_img.close();
        port_o_img.close();
        port_o_blobs.close();
        port_i_propImg.close();   
        port_o_clean.close();
        port_o_propImg.close();
    }

    bool execReq(const Bottle &command, Bottle &reply)
    {
        if(command.get(0).asVocab32()==Vocab32::encode("thresh"))
        {
            lock_guard<mutex> lg(mtx);
            thresh = command.get(1).asFloat64();
            reply.addVocab32("ok");
            return true;
        }
        if(command.get(0).asVocab32()==Vocab32::encode("erode"))
        {
            lock_guard<mutex> lg(mtx);
            erode_itr = command.get(1).asInt32();
            reply.addVocab32("ok");
            return true;
        }
        if(command.get(0).asVocab32()==Vocab32::encode("dilate"))
        {
            lock_guard<mutex> lg(mtx);
            dilate_itr = command.get(1).asInt32();
            reply.addVocab32("ok");
            return true;
        }

        return false;
    }

    void cleanBlobs(cv::Mat &image)
    {
        for (int i=0; i<blobs.size(); i++)
        {
            cv::Point cog(-1,-1);
            if ((i>=0) && (i<blobs.size()))
            {
                cv::Point tl,br;
                Bottle *item=blobs.get(i).asList();
                if (item==NULL)
                    cout << "ITEM IS NULL" << cog.x << cog.y <<endl;

                tl.x=(int)item->get(0).asFloat64() - 2;
                tl.y=(int)item->get(1).asFloat64() - 2;
                br.x=(int)item->get(2).asFloat64() + 2;
                br.y=(int)item->get(3).asFloat64() + 2;
            
                image(cv::Rect(tl.x,tl.y,br.x-tl.x,br.y-tl.y)).copyTo(imgProp(cv::Rect(tl.x,tl.y,br.x-tl.x,br.y-tl.y)));
            }
        }
    }

    void processImg(cv::Mat &image)
    {
        for (int i=0; i<blobs.size(); i++)
        {
            cv::Point cog(-1,-1);
            if ((i>=0) && (i<blobs.size()))
            {
                cv::Point tl,br;
                Bottle *item=blobs.get(i).asList();
                if (item==NULL)
                    cout << "ITEM IS NULL" << cog.x << cog.y <<endl;

                tl.x=(int)item->get(0).asFloat64() - 10;
                tl.y=(int)item->get(1).asFloat64() - 10;
                br.x=(int)item->get(2).asFloat64() + 10;
                br.y=(int)item->get(3).asFloat64() + 10;

                cog.x=(tl.x + br.x)>>1;
                cog.y=(tl.y + br.y)>>1;     
        
                cv::Mat imageRoi=image(cv::Rect(tl.x,tl.y,br.x-tl.x,br.y-tl.y));
                getOrientations(imageRoi);
            }
        }
        numBlobs = 0;
        numObj = 0;
    }

    void getOrientations(cv::Mat &image)
    {
        vector<vector<cv::Point>> cont;
        cv::findContours(image,cont,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

        //go first through all contours in order to find if there are some duplications
        for (auto &c:cont)
        {
            numObj++;
            cv::RotatedRect boxtmp = cv::minAreaRect(cv::Mat(c));
            tmpCenter[numObj].x = cvRound(boxtmp.center.x);
            tmpCenter[numObj].y = cvRound(boxtmp.center.y);
            area[numObj] = cv::contourArea(c);
        }

        //check for duplicate center points
        int inc = 0;
        Vector index(numObj);
        for (int x=1; x<numObj; x++)
        {
            if (abs( tmpCenter[x].x -tmpCenter[x+1].x ) < 10 )
            {
                if (abs( tmpCenter[x].y -tmpCenter[x+1].y) < 10)
                {
                    if ( area[x] < area[x+1] )
                    {
                        index[inc] = x;
                        inc++;
                    }
                    else
                    {
                        index[inc] = x+1;
                        inc++;
                    }
                } 
            }
        }

        for (auto &c:cont)
        {
            numBlobs++;
            for (int i= 0; i<inc; i++)
                if (numBlobs == index[i])
                    continue;
                    
            if (c.size()<6)
                continue;

            cv::RotatedRect box = cv::fitEllipse(cv::Mat(c));
            cv::Point center = box.center;
            cv::Size size(cvRound(box.size.width*0.5),cvRound(box.size.height*0.5));

            if ((box.size.width > 0) && (box.size.width < 300) && (box.size.height > 0) && (box.size.height < 300))
            {
                axe1[numBlobs] = size.width;
                axe2[numBlobs] = size.height;
            
                vector<float> line(4);
                cv::fitLine(c,line,CV_DIST_L2,0,0.01,0.01);
                float t = (box.size.width + box.size.height)/2;
                pt1.x = cvRound(line[2] - line[0] *t );
                pt1.y = cvRound(line[3] - line[1] *t );
                pt2.x = cvRound(line[2] + line[0] *t );
                pt2.y = cvRound(line[3] + line[1] *t );
                cv::line(image,pt1,pt2,cv::Scalar(255,255,255),2,cv::LINE_AA);
                thetatmp = 0.0;
                thetatmp = (180.0/M_PI) * atan2( (double)(pt2.y - pt1.y) , (double)(pt2.x - pt1.x) );
                
                thetatmp=(thetatmp<0.0?-thetatmp:180.0-thetatmp);
                orientation[numBlobs]=thetatmp;
            }
        }
    }
};


class BlobDetectorModule: public RFModule
{
private:
    BlobDetectorThread  *bdThr;
    Port                rpcPort;

public:
    BlobDetectorModule() { }

    virtual bool configure(ResourceFinder &rf)
    {
        bdThr=new BlobDetectorThread(rf);

        if(!bdThr->start())
        {
            delete bdThr;
            return false;
        }

        string name=rf.find("name").asString();
        rpcPort.open("/"+name+"/rpc");
        attach(rpcPort);

        return true;
    }

    virtual bool interruptModule()
    {
        rpcPort.interrupt();

        return true;
    }

    virtual bool close()
    {
        bdThr->stop();
        delete bdThr;

        rpcPort.close();

        return true;
    }

    virtual double getPeriod()
    {
        return 0.1;
    }

    virtual bool updateModule()
    {
        return true;
    }

    virtual bool respond(const Bottle &command, Bottle &reply)
    {
        reply.clear();
        if (command.get(0).asString()=="details") 
        {
            if (command.get(1).asString()=="on")
            { 
                bdThr->details = "on";
                reply.addString("setting details to ON");
                return true;
            }else
            {
                bdThr->details = "off";
                reply.addString("setting details to OFF");
                return true;
            }         
            return false;     
        } else if (command.get(0).asString()=="thresh") 
        {
            double newThresh = command.get(1).asFloat64();
            if (newThresh<0 || newThresh>255.0)
            {
                reply.addString("Invalid threshold (expecting a value between 0 and 255)");
                return false;
            }
            reply.addString("Setting threshold");
            bdThr->setThreshold(newThresh);
            return true;
        }
        if(bdThr->execReq(command,reply))
            return true;
        else
            return RFModule::respond(command,reply);
    }
};


int main(int argc, char *argv[])
{
    Network yarp;

    if (!yarp.checkNetwork())
        return 1;

    ResourceFinder rf;
    rf.setDefaultContext("blobExtractor");
    rf.setDefaultConfigFile("config.ini");
    rf.setDefault("name","blobExtractor");
    rf.configure(argc,argv);

    BlobDetectorModule mod;

    return mod.runModule(rf);
}


