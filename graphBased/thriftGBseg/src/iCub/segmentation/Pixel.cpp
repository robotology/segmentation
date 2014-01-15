// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <iCub/segmentation/Pixel.h>

namespace yarp { namespace sig {
bool Pixel::read(yarp::os::idl::WireReader& reader) {
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

bool Pixel::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListHeader(2)) return false;
  return read(reader);
}

bool Pixel::write(yarp::os::idl::WireWriter& writer) {
  if (!writer.writeI32(x)) return false;
  if (!writer.writeI32(y)) return false;
  return !writer.isError();
}

bool Pixel::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  return write(writer);
}
}} // namespace
