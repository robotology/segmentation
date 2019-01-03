// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2009 Alex Bernardino, Vislab, IST/ISR
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef __EDISONSEGMMODULE__
#define __EDISONSEGMMODULE__

 // std
#include <stdio.h>


// OpenCV
#include <opencv2/opencv.hpp>

// yarp
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Stamp.h>

/**
 *
 * Edison Segmentation Module
 *
 *
 */
#include <segm/msImageProcessor.h>
#include "SegmentationModule.h"

class EdisonSegmModule : public yarp::os::RFModule, public SegmentationModule {

private:
    double _timestart;
    int orig_height_, height_, orig_width_, width_, dim_;       //input image dimensions
    
    //internal storage for the input image - must be RGB
    yarp::sig::ImageOf<yarp::sig::PixelRgb> inputImage;
    unsigned char * inputImage_;

    //internal storage for hsv image, only needed for dim = 1.
    yarp::sig::ImageOf<yarp::sig::PixelRgb> inputHsv;
    unsigned char * inputHsv_;

    //internal storage for hue channel, only needed for dim = 1.
    yarp::sig::ImageOf<yarp::sig::PixelMono> inputHue;
    unsigned char * inputHue_;

    //store the weight maps
    yarp::sig::ImageOf<yarp::sig::PixelFloat> gradMap;
    float * gradMap_;
    
    yarp::sig::ImageOf<yarp::sig::PixelFloat> confMap;
    float * confMap_;
    
    yarp::sig::ImageOf<yarp::sig::PixelFloat> weightMap;
    float * weightMap_;

    //float * custMap_; //????? Is this really needed

    //storage for the output images
    yarp::sig::ImageOf<yarp::sig::PixelRgb> filtImage;
    unsigned char * filtImage_;

    yarp::sig::ImageOf<yarp::sig::PixelRgb> segmImage;
    unsigned char * segmImage_;

    yarp::sig::ImageOf<yarp::sig::PixelInt> labelImage;

    yarp::sig::ImageOf<yarp::sig::PixelMono> labelView; // for visualizing the labels - debug stuff

    //store the output edges and boundaries
    int *edges_, numEdges_;
    int *boundaries_, numBoundaries_;

    //parameters for mean shift
    int sigmaS;     //spatial bandwidth
    float sigmaR;       //range bandwidth
    int minRegion;  //area of the smallest objects to consider
    
    //parameters for synergistic segmentation
    int gradWindRad; //Gradient Window Radius
    float threshold; //Edge Strength Threshold [0,1]
    float mixture;   //Mixture Parameter [0,1]

    SpeedUpLevel speedup; //{NO_SPEEDUP, MED_SPEEDUP, HIGH_SPEEDUP} 
    void setSpeedUpValue(int newSpeedUpValue);
    
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _imgPort;      //input image
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _rawPort;      //raw image 
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _viewPort;     //output image - segmentation (modes of each detected object), edges, etc (configurable)
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelInt> >       _labelPort;    //output image with labels 
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _filtPort;     //output the mean shift filtered image
    yarp::os::Port                                          _configPort;   //to configure the module
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelMono> >      _labelViewPort; //to visualize the labels

    yarp::os::Stamp _stamp;

public:
    EdisonSegmModule();
    ~EdisonSegmModule();

    virtual bool configure (yarp::os::ResourceFinder &rf);
    //virtual bool open(yarp::os::Searchable& config);
    virtual bool close();
    virtual bool interruptModule();
    virtual bool updateModule();
      
    bool attach(yarp::os::Port &source)
    {
        return this->yarp().attachAsServer(source);
    }
    
    // rpc interface on _configPort
    virtual void set_sigmaS(const double newValue){sigmaS=(int)newValue;};
    virtual void set_sigmaR(const double newValue){sigmaR=(float)newValue;};
    virtual void set_minRegion(const double newValue){minRegion=(int)newValue;};
    virtual void set_gradWindRad(const double newValue){gradWindRad=(int)newValue;};
    virtual void set_threshold(const double newValue){newValue <=1 ? threshold=(float)newValue: threshold=1; if (threshold <0) threshold =0;};
    virtual void set_mixture(const double newValue){newValue <=1 ? mixture=(float)newValue: mixture=1; if (mixture<0 ) mixture=0;};
    virtual void set_speedup(const SpeedUpLevelComm newSpeedLevel){setSpeedUpValue(newSpeedLevel);};
    virtual double get_sigmaS(){return sigmaS;};
    virtual double get_sigmaR(){return sigmaR;};
    virtual double get_minRegion(){return minRegion;};
    virtual double get_gradWindRad(){return gradWindRad;};
    virtual double get_threshold(){return threshold;};
    virtual double get_mixture(){return mixture;};
    virtual SpeedUpLevelComm get_speedup(){return SpeedUpLevelComm(speedup);};
    
};


#endif

