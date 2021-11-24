// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2012 Elena Ceseracciu, RBCS - Istituto Italiano di Tecnologia
 * CopyPolicy: Released under the terms of the GNU GPL v2.0 and later.
 *
 */

#include <string>
#include <iostream>
using namespace std;


#include "SegmModule.h"
#include "segment-image.h"


// yarp
#include <yarp/os/Network.h>
using namespace yarp::os;
using namespace yarp::sig;

void YarpImageToRGBImage(image<rgb> * im, ImageOf<PixelRgb> * yarpIm) {

        for (int y = 0; y < im->height(); y++) {

            for (int x = 0; x < im->width(); x++) {

              imRef(im, x, y).r = yarpIm->pixel(x,y).r;
              imRef(im, x, y).g = yarpIm->pixel(x,y).g;
              imRef(im, x, y).b = yarpIm->pixel(x,y).b;


            }

        }

}





void RGBImageToYarpImage(image<rgb> * im, ImageOf<PixelRgb> * yarpIm) {

        for (int y = 0; y < im->height(); y++) {

            for (int x = 0; x < im->width(); x++) {

              yarpIm->pixel(x,y).r = (uchar) imRef(im, x, y).r;

              yarpIm->pixel(x,y).g = (uchar) imRef(im, x, y).g;

              yarpIm->pixel(x,y).b = (uchar) imRef(im, x, y).b;



            }

        }

}

void GBSegmModule::set_sigma(const double newValue) {sigma=(float)newValue;}
void GBSegmModule::set_k(const double newValue){k=(float)newValue;}
void GBSegmModule::set_minRegion(const double newValue){min_size=(int)newValue;}
double GBSegmModule::get_sigma(){return sigma;}
double GBSegmModule::get_k(){return k;}
double GBSegmModule::get_minRegion(){return min_size;}
int32_t GBSegmModule::get_num_components(){return num_components;}
std::vector< Pixel > GBSegmModule::get_component_around(const Pixel& objCenter)
{
    vector<Pixel> result;
    result.clear();
    lock_guard<mutex> lg(segMutex);
    rgb componentColor = imRef(seg, objCenter.x, objCenter.y);
    for (int y = 0; y < seg->height(); y++) {

            for (int x = 0; x < seg->width(); x++) {

              if (imRef(seg, x, y) == componentColor)
                result.push_back(Pixel(x, y));


            }

        }

    return result;
}


GBSegmModule::GBSegmModule() : _stamp(0,0)
{
    input = NULL;
    seg = NULL;
    // parameters default values
    sigma = 0.8F;
    k= 700;
    min_size = 700;
}

GBSegmModule::~GBSegmModule()
{
 if(input)
     delete input;
 if (seg)
     delete seg;
}


bool GBSegmModule::configure (yarp::os::ResourceFinder &rf)
{
    if (rf.check("help","if present, display usage message")) {
        printf("Call with --from configfile.ini\n");
        return false;
    }
   
    if (rf.check("name"))
        setName(rf.find("name").asString().c_str());
    else setName("GBSeg");


    //override defaults if specified - TODO: range checking
    if(rf.check("sigma")) sigma = (float)rf.find("sigma").asFloat64();      
    if(rf.check("k")) k = (float)rf.find("k").asFloat64();      
    if(rf.check("minRegion")) min_size = rf.find("minRegion").asInt32();  

    std::string slash="/";
    _imgPort.open(slash + getName("/rawImg:i"));
    _configPort.open(slash + getName("/conf"));
    _viewPort.open(slash +getName("/viewImg:o"));
    attach(_configPort);

    //read an image to get the dimensions
    ImageOf<PixelRgb> *yrpImgIn;    
    yrpImgIn = _imgPort.read();
    if (yrpImgIn == NULL)   // this is the case if module is requested to quit while waiting for image
        return true;
    input=new image<rgb>(yrpImgIn->width(), yrpImgIn->height(), true);

// 
//     //THIS IS NOT REQUIRED - INPUT IMAGES ARE ALWAYS RGB
//     //IF DIM == 3 THEN THE PROCESSING CLASS CONVERTS TO LUV
//     //IF DIM == 1 THEN THE PROCESSING CLASS ONLY USES THE FIRST CHANNEL
//     //WE USE HUE CHANNEL, SO MUST CONVERT FROM RGB TO HSV
//     //check compatibility of image depth 
//     /*if (yrpImgIn->getPixelSize() != dim_) 
//     {
//             cout << endl << "Incompatible image depth" << endl;
//             return false;
//     }*/ 
// 
//     //override internal image dimension if necessary
//     if( width_ > orig_width_ )
//             width_ = orig_width_;
//     if( height_ > orig_height_ )
//             height_ = orig_height_;
// 
//     //allocate memory for image buffers and get the pointers
// 
//     inputImage.resize(width_, height_); inputImage_ = inputImage.getRawImage();
//     inputHsv.resize(width_, height_); inputHsv_ = inputHsv.getRawImage();
//     inputHue.resize(width_, height_); inputHue_ = inputHue.getRawImage();
//     filtImage.resize(width_, height_);  filtImage_ = filtImage.getRawImage();
//     segmImage.resize(width_, height_);  segmImage_ = segmImage.getRawImage();
//     gradMap.resize(width_, height_);    gradMap_ = (float*)gradMap.getRawImage();
//     confMap.resize(width_, height_);    confMap_ = (float*)confMap.getRawImage();
//     weightMap.resize(width_, height_);  weightMap_ = (float*)weightMap.getRawImage();
//     labelImage.resize(width_, height_);
//     labelView.resize(width_, height_);

    return true;
}

bool GBSegmModule::close()
{
    _imgPort.close();
    _viewPort.close();
    _configPort.close();

    // also deallocate image _frame
    return true;
}

bool GBSegmModule::interruptModule(){
    
    _imgPort.interrupt();
    _configPort.interrupt();
    _viewPort.interrupt();

    return true;
}

bool GBSegmModule::updateModule()
{
    ImageOf<PixelRgb> *yrpImgIn;
    static int cycles = 0;

    yrpImgIn = _imgPort.read();
    if (yrpImgIn == NULL)   // this is the case if module is requested to quit while waiting for image
        return true;

    bool use_private_stamp;
    Stamp s;
    if(!_imgPort.getEnvelope(s))
    {
            cout << "No stamp found in input image. Will use private stamp" << endl;
            use_private_stamp = true;
    }
    else
    {
            cout << "Received image #" << s.getCount() << " generated at time " << s.getTime() << endl;
            use_private_stamp = false;
    }

    if(cycles == 0)
            _timestart = yarp::os::Time::now();
    cycles++;

    cout << "converting image of size " << yrpImgIn->width() << yrpImgIn->height() <<" to size" << input->width() << input->height() << endl;
    YarpImageToRGBImage(input, yrpImgIn);
    cout << "converted" << endl;
    segMutex.lock();
    if(seg)
        delete seg;
    seg=segment_image(input, sigma, k, min_size, &num_components);
    segMutex.unlock();
    
    cout << "processed" << endl;
    //prepare timestamps
    if(use_private_stamp)
    {
        _stamp.update();
        _viewPort.setEnvelope(_stamp);
    }
    else
    {
        _viewPort.setEnvelope(s);
    }



    ImageOf<PixelRgb> &yrpImgView = _viewPort.prepare();
    //Rescale image if required

    yrpImgView.resize(seg->width(), seg->height());
    RGBImageToYarpImage(seg, &yrpImgView);
    _viewPort.write();


    //report the frame rate
    if(cycles % 100 == 0)
    {
            double cps = ((double)cycles)/(yarp::os::Time::now() - _timestart);
            printf("fps: %02.2f\n", cps);
    }
    return true;
}


