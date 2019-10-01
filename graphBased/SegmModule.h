// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2012 Elena Ceseracciu, RBCS - Istituto Italiano di Tecnologia
 * CopyPolicy: Released under the terms of the GNU GPL v2.0 and later.
 *
 */

#ifndef __SEGMMODULE__
#define __SEGMMODULE__

#include <mutex>

// yarp
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Stamp.h>

/**
 *
 * Segmentation Module
 *
 *
 */
#include "image.h"
#include "misc.h"
#include "SegmentationModuleInterface.h" //Thrift interface

class GBSegmModule : public yarp::os::RFModule, public yarp::sig::SegmentationModuleInterface {

private:
    double _timestart;
   
    float sigma;
    float k;
    int min_size;
    int num_components;
    
    image<rgb> *input;
    image<rgb> *seg;
    
    std::mutex segMutex;
    
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _imgPort;      //input image
  //  yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _rawPort;      //raw image 
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _viewPort;     //output image - segmentation (modes of each detected object), edges, etc (configurable)
   // yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelInt> >       _labelPort;    //output image with labels 
   // yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >       _filtPort;     //output the mean shift filtered image
    yarp::os::Port                                          _configPort;   //to configure the module
  //  yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelMono> >      _labelViewPort; //to visualize the labels

    yarp::os::Stamp _stamp;

public:
    GBSegmModule();
    ~GBSegmModule();

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
    virtual void set_sigma(const double newValue);
    virtual void set_k(const double newValue);
    virtual void set_minRegion(const double newValue);
    virtual double get_sigma();
    virtual double get_k();
    virtual double get_minRegion();
    virtual int32_t get_num_components();
    virtual std::vector<yarp::sig::Pixel>  get_component_around(const yarp::sig::Pixel& objCenter);
};


#endif

