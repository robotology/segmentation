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
 \defgroup icub_blobExtractor Blob Extractor

 Module that uses the data from the lumaChroma module to extract blobs that are available.
 \ref icub_blobExtractor application.

 \section intro_sec Description
 This module is responsible for extracting all the blobs 
 based upon the \ref icub_lumaChroma module. To this end, it receives 
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
#include <yarp/os/RateThread.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Stamp.h>

#include <yarp/sig/Image.h>
#include <yarp/sig/Vector.h>

#include <gsl/gsl_math.h>

#include <opencv2/opencv.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace cv;

class BlobDetectorThread: public RateThread
{
private:
    ResourceFinder              &rf;

    BufferedPort<Image>         port_i_img;
	BufferedPort<Image>         port_i_propImg; // extra port just to propagate image
    Port                        port_o_img;
	Port                        port_o_propImg;
    Port                        port_o_blobs;
	Port                        port_o_clean;
	IplImage 					*imgProp;

    int                         gaussian_winsize;

    double                      window_ratio;
    double                      thresh;
    int                         erode_itr;
    int                         dilate_itr;
    int                         maxHeight;
    int                         maxWidth;

    Semaphore                   mutex;
    Semaphore                   contours;
    Bottle                      blobs;
    Bottle                      non_blobs;

    int                         offset;

    yarp::sig::Vector           area, orientation, axe1, axe2;
    int                         numBlobs;
    
    CvPoint                     tmpCenter[500],pt1, pt2;
    int                         numObj;
    double                      thetatmp;

public:
    BlobDetectorThread(ResourceFinder &_rf)
        :RateThread(5),rf(_rf)
    {
    }
    
    string                        details;

    virtual bool threadInit()
    {
        string name=rf.find("name").asString().c_str();

        port_i_img.open(("/"+name+"/img:i").c_str());
		port_i_propImg.open(("/"+name+"/propImg:i").c_str());
        port_o_img.open(("/"+name+"/img:o").c_str());
		port_o_propImg.open(("/"+name+"/propImg:o").c_str());

        port_o_blobs.open(("/"+name+"/blobs:o").c_str());
		port_o_clean.open(("/"+name+"/binary:o").c_str());

        gaussian_winsize=rf.check("gaussian_winsize",Value(9)).asInt();

        thresh=rf.check("thresh",Value(10.0)).asDouble();
        erode_itr=rf.check("erode_itr",Value(8)).asInt();
        dilate_itr=rf.check("dilate_itr",Value(3)).asInt();
        window_ratio=rf.check("window_ratio",Value(0.6)).asDouble();

        maxHeight = rf.check("maxHeight",Value(150)).asInt();
        maxWidth  = rf.check("maxWidth",Value(150)).asInt();
        
        details=rf.check("details",Value("off")).asString();

        offset=rf.check("offset",Value(0)).asInt();
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
        mutex.wait();
        thresh = newThreshold;
        mutex.post();
    }

    virtual void run()
    {
        Image *img=port_i_img.read(false);    
        if(img!=NULL)
        {
            Stamp ts;
            port_i_img.getEnvelope(ts);

            IplImage *gray=(IplImage*) img->getIplImage();
			imgProp = cvCloneImage( gray );
			cvZero(imgProp);

            cvSmooth(gray,gray,CV_GAUSSIAN,gaussian_winsize);
            cvThreshold(gray,gray,thresh,255.0,CV_THRESH_BINARY);
            cvEqualizeHist(gray,gray); //normalize brightness and increase contrast.
            cvErode(gray,gray,NULL,erode_itr);
            cvDilate(gray,gray,0,dilate_itr);

            mutex.wait();
            blobs.clear();
            non_blobs.clear();

            int w_offset=cvRound(0.5*gray->width*(1.0-window_ratio));
            int h_offset=cvRound(0.5*gray->height*(1.0-window_ratio));
            int itr = 0;
            for(int row=h_offset; row<gray->height-h_offset; row++)
            {
                uchar *ptr=(uchar*) gray->imageData + row*gray->widthStep;
                for(int col=w_offset; col<gray->width-w_offset; col++)
                {
                    if(ptr[col]==255)
                    {
                        CvConnectedComp comp;
                        cvFloodFill(gray,cvPoint(col,row),cvScalar(255-(blobs.size()+non_blobs.size()+1)),cvScalar(0),cvScalar(0),&comp);

                        if(5<comp.rect.width && comp.rect.width<maxWidth && 5<comp.rect.height && comp.rect.height< maxHeight)
                        {
                            Bottle &b=blobs.addList();
                            b.addDouble(comp.rect.x-offset);
                            b.addDouble(comp.rect.y-offset);
                            b.addDouble(comp.rect.x+comp.rect.width+offset);
                            b.addDouble(comp.rect.y+comp.rect.height+offset);
                            if(details=="on")
                            {
                                if(orientation.size() > 0 )
                                {
                                    b.addDouble(orientation[itr+1]);
                                    b.addInt((int)axe2[itr+1]);
                                    b.addInt((int)axe1[itr+1]);
                                }                         
                            }
                            itr++;
                        }
                        else
                        {
                            Bottle &n=non_blobs.addList();
                            n.addDouble(comp.rect.x-offset);
                            n.addDouble(comp.rect.y-offset);
                            n.addDouble(comp.rect.x+comp.rect.width+offset);
                            n.addDouble(comp.rect.y+comp.rect.height+offset);
                            if(details=="on")
                            {
                                if(orientation.size() > 0 )
                                {
                                    n.addDouble(orientation[itr+1]);
                                    n.addInt((int)axe2[itr+1]);
                                    n.addInt((int)axe1[itr+1]);
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
                contours.wait();
                processImg(gray);
                contours.post(); 
            }
            
            port_o_img.setEnvelope(ts);
            port_o_img.write(*img);

            port_o_blobs.setEnvelope(ts);
            port_o_blobs.write(blobs);
			Image *prop= port_i_propImg.read(false);  
			
			if(prop!=NULL)
			{
				port_o_propImg.setEnvelope(ts);
				port_o_propImg.write(*prop);
			}
			if(imgProp!=NULL)
			{
				ImageOf<PixelMono> *sendImg = new ImageOf<PixelMono>;
				sendImg->resize(imgProp->width, imgProp->height);
				cvCopy(imgProp, (IplImage*)sendImg->getIplImage());
				port_o_clean.setEnvelope(ts);
				port_o_clean.write(*sendImg);
				delete sendImg;
				cvReleaseImage(&imgProp);
			}

            mutex.post();
        }
    }

    virtual void threadRelease()
    {
		if(imgProp!=NULL)
			cvReleaseImage(&imgProp);
        
		port_i_img.close();
        port_o_img.close();
        port_o_blobs.close();
		port_i_propImg.close();   
		port_o_clean.close();
		port_o_propImg.close();
    }


    bool execReq(const Bottle &command, Bottle &reply)
    {
        /*if(command.get(0).asVocab()==Vocab::encode("segment"))
        {
            fprintf(stdout,"segment request received\n");
            mutex.wait();
            if (blobs.size()>0)
                reply=blobs;
            else
                reply.addVocab(Vocab::encode("empty"));
            mutex.post();
            fprintf(stdout,"blobs: %s\n",reply.toString().c_str());
            
            return true;
        }*/
        if(command.get(0).asVocab()==Vocab::encode("thresh"))
        {
            mutex.wait();
            thresh = command.get(1).asDouble();
            mutex.post();
            reply.addVocab(Vocab::encode("ok"));
            return true;
        }
        if(command.get(0).asVocab()==Vocab::encode("erode"))
        {
            mutex.wait();
            erode_itr = command.get(1).asInt();
            mutex.post();
            reply.addVocab(Vocab::encode("ok"));
            return true;
        }
        if(command.get(0).asVocab()==Vocab::encode("dilate"))
        {
            mutex.wait();
            dilate_itr = command.get(1).asInt();
            mutex.post();
            reply.addVocab(Vocab::encode("ok"));
            return true;
        }

        return false;
    }

	void cleanBlobs(IplImage* image)
	{
		for (int i=0; i<blobs.size(); i++)
        {
            CvPoint cog=cvPoint(-1,-1);
            if ((i>=0) && (i<blobs.size()))
            {
                CvPoint tl,br;
                Bottle *item=blobs.get(i).asList();
                if (item==NULL)
                    cout << "ITEM IS NULL" << cog.x << cog.y <<endl;

                tl.x=(int)item->get(0).asDouble() - 2;
                tl.y=(int)item->get(1).asDouble() - 2;
                br.x=(int)item->get(2).asDouble() + 2;
                br.y=(int)item->get(3).asDouble() + 2;
			
				cvSetImageROI(image, cvRect(tl.x, tl.y, br.x - tl.x, br.y- tl.y));   
				cvSetImageROI(imgProp, cvRect(tl.x, tl.y, br.x - tl.x, br.y- tl.y)); 
				cvCopy(image, imgProp );
				cvResetImageROI(image);
				cvResetImageROI(imgProp);

			}
        }
	}

    void processImg(IplImage* image)
    {
        for (int i=0; i<blobs.size(); i++)
        {
            CvPoint cog=cvPoint(-1,-1);
            if ((i>=0) && (i<blobs.size()))
            {
                CvPoint tl,br;
                Bottle *item=blobs.get(i).asList();
                if (item==NULL)
                    cout << "ITEM IS NULL" << cog.x << cog.y <<endl;

                tl.x=(int)item->get(0).asDouble() - 10;
                tl.y=(int)item->get(1).asDouble() - 10;
                br.x=(int)item->get(2).asDouble() + 10;
                br.y=(int)item->get(3).asDouble() + 10;

                cog.x=(tl.x + br.x)>>1;
                cog.y=(tl.y + br.y)>>1;		
		
                cvSetImageROI(image, cvRect(tl.x, tl.y, br.x - tl.x, br.y- tl.y));        									
				getOrientations(image);
                cvResetImageROI(image);
            }
        }
        numBlobs = 0;
        numObj = 0;
    }

    void getOrientations(IplImage* image)
    {
        float line[4];
        CvMemStorage *stor = cvCreateMemStorage(0);
        CvMemStorage *tmpStor = cvCreateMemStorage(0);
        //CvPoint* PointArray;
        //CvPoint2D32f* PointArray2D32f;
        
        CvPoint center;
        CvSize size;
        //fprintf(stdout,"dgb0.1\n");
        IplImage *clone = cvCloneImage( image );
        CvSeq *tmpCont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , tmpStor);
        CvSeq *cont = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint) , stor);
        cvFindContours( clone, tmpStor, &tmpCont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
	    cvFindContours( clone, stor, &cont, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
        cvZero(clone);
        //go first through all contours in order to find if there are some duplications
        for(;tmpCont;tmpCont = tmpCont->h_next){
            numObj++;
            CvBox2D boxtmp = cvMinAreaRect2(tmpCont, tmpStor); 
            //fprintf(stdout,"dgb0.25  %lf  %lf\n", cvRound(boxtmp.center.x), cvRound(boxtmp.center.y));
            tmpCenter[numObj].x = cvRound(boxtmp.center.x);
	        tmpCenter[numObj].y = cvRound(boxtmp.center.y);
	       	area[numObj] = fabs(cvContourArea( tmpCont, CV_WHOLE_SEQ ));
            //fprintf(stdout,"%d X= %d Y= %d\n",numObj, tmpCenter[numObj].x, tmpCenter[numObj].y);
        }
        int inc = 0;
        //check for duplicate center points
        yarp::sig::Vector index;
        index.resize(numObj);
        for (int x=1; x<numObj; x++)
        {
        	if (abs( tmpCenter[x].x -tmpCenter[x+1].x ) < 10 )
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
        for(;cont;cont = cont->h_next)
        {
            numBlobs++;
            bool draw = true;
            for (int i= 0; i<inc; i++)
                if (numBlobs == index[i])	
                	draw = false;
                    
            int count = cont->total;
            
            
            
            if( count < 6 )
                continue;
            
            if (draw)
            {        
                // Alloc memory for contour point set.    
                /*PointArray = (CvPoint*)malloc( count*sizeof(CvPoint) );
                PointArray2D32f= (CvPoint2D32f*)malloc( count*sizeof(CvPoint2D32f) );
                
                cvCvtSeqToArray(cont, PointArray, CV_WHOLE_SEQ);
                for(int i=0; i<count; i++)
                {
                    PointArray2D32f[i].x = (float)PointArray[i].x;
                    PointArray2D32f[i].y = (float)PointArray[i].y;
                }
                 
                CvBox2D box=cvFitEllipse2(PointArray2D32f);
                 */
                
                CvMat* points_f = cvCreateMat( 1, count, CV_32FC2 );
                CvMat points_i = cvMat( 1, count, CV_32SC2, points_f->data.ptr );
                cvCvtSeqToArray(cont, points_f->data.ptr, CV_WHOLE_SEQ );
                cvConvert( &points_i, points_f );
                
                CvBox2D box = cvFitEllipse2(points_f);
                center = cvPointFrom32f(box.center);
                size.width = cvRound(box.size.width*0.5);
                size.height = cvRound(box.size.height*0.5);
                
                //cvEllipse(dst,center,size,box.angle,0,360,cvScalar(0,255,0),2,8,0);
                
                if ((box.size.width > 0) && (box.size.width < 300) && (box.size.height > 0) && (box.size.height < 300))
                {
                    center.x = cvRound(box.center.x);
                    center.y = cvRound(box.center.y);
                    size.width = cvRound(box.size.width*0.5);
                    size.height = cvRound(box.size.height*0.5);
                    //box.angle = box.angle;
                    //cvEllipse(image, center, size, box.angle, 0, 360, CV_RGB(255,255,255), 1, CV_AA, 0);
                
                    //orientation[numBlobs] = (box.angle) - 90.0;//box.angle;
                    axe1[numBlobs] = size.width;
                    axe2[numBlobs] = size.height;
                
                    cvFitLine(cont, CV_DIST_L2, 0, 0.01, 0.01, line);
                    float t = (box.size.width + box.size.height)/2;
                    pt1.x = cvRound(line[2] - line[0] *t );
                    pt1.y = cvRound(line[3] - line[1] *t );
                    pt2.x = cvRound(line[2] + line[0] *t );
                    pt2.y = cvRound(line[3] + line[1] *t );
                    cvLine( image, pt1, pt2, CV_RGB(255,255,255), 2, CV_AA, 0);
                    thetatmp = 0.0;
                    thetatmp = 180 / M_PI * atan2( (double)(pt2.y - pt1.y) , (double)(pt2.x - pt1.x) );
                    
                    if (thetatmp < 0)
                        thetatmp = -thetatmp;
                    else
                        thetatmp = 180 -thetatmp;
                    
                    orientation[numBlobs] = thetatmp;
                }
                //cout << "orientation angles " << theta << endl;
                // Free memory.          
               // free(PointArray);
                //free(PointArray2D32f);
                //fprintf(stdout, "NUMBLOBS %d orient %lf   axe1 %d, axe2 %d \n", numBlobs, orientation[numBlobs], (int)axe1[numBlobs], (int)axe2[numBlobs]);
            }
            //fprintf(stdout,"dgb0.8\n");
        }
        // Free memory.
        cvRelease((void **)&cont); cvRelease((void **)&tmpCont);
		cvClearMemStorage( stor ); cvClearMemStorage( tmpStor );
        cvReleaseMemStorage(&stor);cvReleaseMemStorage(&tmpStor);
        cvReleaseImage(&clone);
       // fprintf(stdout,"dgb0.9\n");
    }
};


class BlobDetectorModule: public RFModule
{
private:
    BlobDetectorThread          *bdThr;

    Port                        rpcPort;


public:
    BlobDetectorModule()
    {}

    virtual bool configure(ResourceFinder &rf)
    {
        bdThr=new BlobDetectorThread(rf);

        if(!bdThr->start())
        {
            delete bdThr;
            return false;
        }

        string name=rf.find("name").asString().c_str();
        rpcPort.open(("/"+name+"/rpc").c_str());
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
            double newThresh = command.get(1).asDouble();
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
    rf.setVerbose(true);
    rf.setDefaultContext("blobExtractor");
    rf.setDefaultConfigFile("config.ini");
    rf.setDefault("name","blobExtractor");
    rf.configure(argc,argv);

    BlobDetectorModule mod;

    return mod.runModule(rf);
}


