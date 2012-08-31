// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_SegmentationModule
#define YARP_THRIFT_GENERATOR_SegmentationModule

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <SpeedUpLevelComm.h>

class SegmentationModule;


class SegmentationModule : public yarp::os::Wire {
public:
  SegmentationModule() { yarp().setOwner(*this); }
  virtual void set_sigmaS(const double newValue);
  virtual void set_sigmaR(const double newValue);
  virtual void set_minRegion(const double newValue);
  virtual void set_gradWindRad(const double newValue);
  virtual void set_threshold(const double newValue);
  virtual void set_mixture(const double newValue);
  virtual void set_speedup(const SpeedUpLevelComm newSpeedLevel);
  virtual double get_sigmaS();
  virtual double get_sigmaR();
  virtual double get_minRegion();
  virtual double get_gradWindRad();
  virtual double get_threshold();
  virtual double get_mixture();
  virtual SpeedUpLevelComm get_speedup();
  virtual bool read(yarp::os::ConnectionReader& connection);
};

#endif

