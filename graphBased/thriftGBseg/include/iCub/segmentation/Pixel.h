// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_STRUCT_Pixel
#define YARP_THRIFT_GENERATOR_STRUCT_Pixel

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

namespace yarp {
  namespace sig {
    class Pixel;
  }
}


/**
 * Pixel position in the image frame
 */
class yarp::sig::Pixel : public yarp::os::idl::WirePortable {
public:
  // if you want to serialize this class without nesting, use this helper
  typedef yarp::os::idl::Unwrapped<yarp::sig::Pixel > unwrapped;
  
/**
 * Index of pixel along horizontal axis
 */
  int32_t x;
/**
 * Index of pixel along vertical axis
 */
  int32_t y;
  Pixel() : x(0), y(0) {
  }
  Pixel(const int32_t x,const int32_t y) : x(x), y(y) {
  }
  bool read(yarp::os::idl::WireReader& reader);
  bool read(yarp::os::ConnectionReader& connection);
  bool write(yarp::os::idl::WireWriter& writer);
  bool write(yarp::os::ConnectionWriter& connection);
};

#endif

