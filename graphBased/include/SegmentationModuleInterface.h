// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_SegmentationModuleInterface
#define YARP_THRIFT_GENERATOR_SegmentationModuleInterface

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <Pixel.h>

class SegmentationModuleInterface;


class SegmentationModuleInterface : public yarp::os::Wire {
public:
  SegmentationModuleInterface() { yarp().setOwner(*this); }
  virtual void set_sigma(const double newValue);
  virtual void set_k(const double newValue);
  virtual void set_minRegion(const double newValue);
  virtual double get_sigma();
  virtual double get_k();
  virtual double get_minRegion();
  virtual int32_t get_num_components();
  virtual std::vector<Pixel>  get_component_around(const Pixel& objCenter);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

#endif

