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
  bool read(yarp::os::idl::WireReader& reader) {
    if (!reader.readI32(x)) {
      reader.fail();
      return false;
    }
    if (!reader.readI32(y)) {
      reader.fail();
      return false;
    }
    return !reader.isError();
  }
  bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(2)) return false;
    return read(reader);
  }
  bool write(yarp::os::idl::WireWriter& writer) {
    if (!writer.writeI32(x)) return false;
    if (!writer.writeI32(y)) return false;
    return !writer.isError();
  }
  bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    return write(writer);
  }
};

#endif

