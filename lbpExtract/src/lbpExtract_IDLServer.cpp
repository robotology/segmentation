// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <lbpExtract_IDLServer.h>
#include <yarp/os/idl/WireTypes.h>



class lbpExtract_IDLServer_reset : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_quit : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setRadius : public yarp::os::Portable {
public:
  int32_t radius;
  bool _return;
  void init(const int32_t radius);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getRadius : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setNeighbours : public yarp::os::Portable {
public:
  int32_t neighbours;
  bool _return;
  void init(const int32_t neighbours);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getNeighbours : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getTopBound : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setTopBound : public yarp::os::Portable {
public:
  int32_t topBound;
  bool _return;
  void init(const int32_t topBound);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getMinArcLength : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setMinArcLength : public yarp::os::Portable {
public:
  int32_t minArcLength;
  bool _return;
  void init(const int32_t minArcLength);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getMaxArcLength : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setMaxArcLength : public yarp::os::Portable {
public:
  int32_t maxArcLength;
  bool _return;
  void init(const int32_t maxArcLength);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_getNumIteration : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_setNumIteration : public yarp::os::Portable {
public:
  int32_t numIteration;
  bool _return;
  void init(const int32_t numIteration);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_resetAllValues : public yarp::os::Portable {
public:
  bool _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class lbpExtract_IDLServer_get_component_around : public yarp::os::Portable {
public:
  int32_t x;
  int32_t y;
  yarp::os::Bottle _return;
  void init(const int32_t x, const int32_t y);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

bool lbpExtract_IDLServer_reset::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("reset",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_reset::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_reset::init() {
  _return = false;
}

bool lbpExtract_IDLServer_quit::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("quit",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_quit::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_quit::init() {
  _return = false;
}

bool lbpExtract_IDLServer_setRadius::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setRadius",1,1)) return false;
  if (!writer.writeI32(radius)) return false;
  return true;
}

bool lbpExtract_IDLServer_setRadius::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setRadius::init(const int32_t radius) {
  _return = false;
  this->radius = radius;
}

bool lbpExtract_IDLServer_getRadius::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getRadius",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getRadius::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getRadius::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_setNeighbours::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setNeighbours",1,1)) return false;
  if (!writer.writeI32(neighbours)) return false;
  return true;
}

bool lbpExtract_IDLServer_setNeighbours::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setNeighbours::init(const int32_t neighbours) {
  _return = false;
  this->neighbours = neighbours;
}

bool lbpExtract_IDLServer_getNeighbours::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getNeighbours",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getNeighbours::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getNeighbours::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_getTopBound::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getTopBound",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getTopBound::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getTopBound::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_setTopBound::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setTopBound",1,1)) return false;
  if (!writer.writeI32(topBound)) return false;
  return true;
}

bool lbpExtract_IDLServer_setTopBound::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setTopBound::init(const int32_t topBound) {
  _return = false;
  this->topBound = topBound;
}

bool lbpExtract_IDLServer_getMinArcLength::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getMinArcLength",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getMinArcLength::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getMinArcLength::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_setMinArcLength::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setMinArcLength",1,1)) return false;
  if (!writer.writeI32(minArcLength)) return false;
  return true;
}

bool lbpExtract_IDLServer_setMinArcLength::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setMinArcLength::init(const int32_t minArcLength) {
  _return = false;
  this->minArcLength = minArcLength;
}

bool lbpExtract_IDLServer_getMaxArcLength::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getMaxArcLength",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getMaxArcLength::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getMaxArcLength::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_setMaxArcLength::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setMaxArcLength",1,1)) return false;
  if (!writer.writeI32(maxArcLength)) return false;
  return true;
}

bool lbpExtract_IDLServer_setMaxArcLength::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setMaxArcLength::init(const int32_t maxArcLength) {
  _return = false;
  this->maxArcLength = maxArcLength;
}

bool lbpExtract_IDLServer_getNumIteration::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("getNumIteration",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_getNumIteration::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_getNumIteration::init() {
  _return = 0;
}

bool lbpExtract_IDLServer_setNumIteration::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("setNumIteration",1,1)) return false;
  if (!writer.writeI32(numIteration)) return false;
  return true;
}

bool lbpExtract_IDLServer_setNumIteration::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_setNumIteration::init(const int32_t numIteration) {
  _return = false;
  this->numIteration = numIteration;
}

bool lbpExtract_IDLServer_resetAllValues::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("resetAllValues",1,1)) return false;
  return true;
}

bool lbpExtract_IDLServer_resetAllValues::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_resetAllValues::init() {
  _return = false;
}

bool lbpExtract_IDLServer_get_component_around::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(5)) return false;
  if (!writer.writeTag("get_component_around",1,3)) return false;
  if (!writer.writeI32(x)) return false;
  if (!writer.writeI32(y)) return false;
  return true;
}

bool lbpExtract_IDLServer_get_component_around::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.read(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void lbpExtract_IDLServer_get_component_around::init(const int32_t x, const int32_t y) {
  this->x = x;
  this->y = y;
}

lbpExtract_IDLServer::lbpExtract_IDLServer() {
  yarp().setOwner(*this);
}
bool lbpExtract_IDLServer::reset() {
  bool _return = false;
  lbpExtract_IDLServer_reset helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::reset()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::quit() {
  bool _return = false;
  lbpExtract_IDLServer_quit helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::quit()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setRadius(const int32_t radius) {
  bool _return = false;
  lbpExtract_IDLServer_setRadius helper;
  helper.init(radius);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setRadius(const int32_t radius)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getRadius() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getRadius helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getRadius()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setNeighbours(const int32_t neighbours) {
  bool _return = false;
  lbpExtract_IDLServer_setNeighbours helper;
  helper.init(neighbours);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setNeighbours(const int32_t neighbours)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getNeighbours() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getNeighbours helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getNeighbours()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getTopBound() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getTopBound helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getTopBound()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setTopBound(const int32_t topBound) {
  bool _return = false;
  lbpExtract_IDLServer_setTopBound helper;
  helper.init(topBound);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setTopBound(const int32_t topBound)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getMinArcLength() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getMinArcLength helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getMinArcLength()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setMinArcLength(const int32_t minArcLength) {
  bool _return = false;
  lbpExtract_IDLServer_setMinArcLength helper;
  helper.init(minArcLength);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setMinArcLength(const int32_t minArcLength)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getMaxArcLength() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getMaxArcLength helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getMaxArcLength()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setMaxArcLength(const int32_t maxArcLength) {
  bool _return = false;
  lbpExtract_IDLServer_setMaxArcLength helper;
  helper.init(maxArcLength);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setMaxArcLength(const int32_t maxArcLength)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t lbpExtract_IDLServer::getNumIteration() {
  int32_t _return = 0;
  lbpExtract_IDLServer_getNumIteration helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t lbpExtract_IDLServer::getNumIteration()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::setNumIteration(const int32_t numIteration) {
  bool _return = false;
  lbpExtract_IDLServer_setNumIteration helper;
  helper.init(numIteration);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::setNumIteration(const int32_t numIteration)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool lbpExtract_IDLServer::resetAllValues() {
  bool _return = false;
  lbpExtract_IDLServer_resetAllValues helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool lbpExtract_IDLServer::resetAllValues()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
yarp::os::Bottle lbpExtract_IDLServer::get_component_around(const int32_t x, const int32_t y) {
  yarp::os::Bottle _return;
  lbpExtract_IDLServer_get_component_around helper;
  helper.init(x,y);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","yarp::os::Bottle lbpExtract_IDLServer::get_component_around(const int32_t x, const int32_t y)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool lbpExtract_IDLServer::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "reset") {
      bool _return;
      _return = reset();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "quit") {
      bool _return;
      _return = quit();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setRadius") {
      int32_t radius;
      if (!reader.readI32(radius)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setRadius(radius);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getRadius") {
      int32_t _return;
      _return = getRadius();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setNeighbours") {
      int32_t neighbours;
      if (!reader.readI32(neighbours)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setNeighbours(neighbours);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getNeighbours") {
      int32_t _return;
      _return = getNeighbours();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getTopBound") {
      int32_t _return;
      _return = getTopBound();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setTopBound") {
      int32_t topBound;
      if (!reader.readI32(topBound)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setTopBound(topBound);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getMinArcLength") {
      int32_t _return;
      _return = getMinArcLength();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setMinArcLength") {
      int32_t minArcLength;
      if (!reader.readI32(minArcLength)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setMinArcLength(minArcLength);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getMaxArcLength") {
      int32_t _return;
      _return = getMaxArcLength();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setMaxArcLength") {
      int32_t maxArcLength;
      if (!reader.readI32(maxArcLength)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setMaxArcLength(maxArcLength);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "getNumIteration") {
      int32_t _return;
      _return = getNumIteration();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "setNumIteration") {
      int32_t numIteration;
      if (!reader.readI32(numIteration)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = setNumIteration(numIteration);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "resetAllValues") {
      bool _return;
      _return = resetAllValues();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_component_around") {
      int32_t x;
      int32_t y;
      if (!reader.readI32(x)) {
        reader.fail();
        return false;
      }
      if (!reader.readI32(y)) {
        reader.fail();
        return false;
      }
      yarp::os::Bottle _return;
      _return = get_component_around(x,y);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.write(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "help") {
      std::string functionName;
      if (!reader.readString(functionName)) {
        functionName = "--all";
      }
      std::vector<std::string> _return=help(functionName);
      yarp::os::idl::WireWriter writer(reader);
        if (!writer.isNull()) {
          if (!writer.writeListHeader(2)) return false;
          if (!writer.writeTag("many",1, 0)) return false;
          if (!writer.writeListBegin(BOTTLE_TAG_INT, static_cast<uint32_t>(_return.size()))) return false;
          std::vector<std::string> ::iterator _iterHelp;
          for (_iterHelp = _return.begin(); _iterHelp != _return.end(); ++_iterHelp)
          {
            if (!writer.writeString(*_iterHelp)) return false;
           }
          if (!writer.writeListEnd()) return false;
        }
      reader.accept();
      return true;
    }
    if (reader.noMore()) { reader.fail(); return false; }
    yarp::os::ConstString next_tag = reader.readTag();
    if (next_tag=="") break;
    tag = tag + "_" + next_tag;
  }
  return false;
}

std::vector<std::string> lbpExtract_IDLServer::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.push_back("*** Available commands:");
    helpString.push_back("reset");
    helpString.push_back("quit");
    helpString.push_back("setRadius");
    helpString.push_back("getRadius");
    helpString.push_back("setNeighbours");
    helpString.push_back("getNeighbours");
    helpString.push_back("getTopBound");
    helpString.push_back("setTopBound");
    helpString.push_back("getMinArcLength");
    helpString.push_back("setMinArcLength");
    helpString.push_back("getMaxArcLength");
    helpString.push_back("setMaxArcLength");
    helpString.push_back("getNumIteration");
    helpString.push_back("setNumIteration");
    helpString.push_back("resetAllValues");
    helpString.push_back("get_component_around");
    helpString.push_back("help");
  }
  else {
    if (functionName=="reset") {
      helpString.push_back("bool reset() ");
      helpString.push_back(" Resets all the histograms ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="quit") {
      helpString.push_back("bool quit() ");
      helpString.push_back("Quit the module. ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="setRadius") {
      helpString.push_back("bool setRadius(const int32_t radius) ");
      helpString.push_back("Sets the radius of the lbp operators ");
      helpString.push_back("@param radius integer containing the radius ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="getRadius") {
      helpString.push_back("int32_t getRadius() ");
      helpString.push_back("Gets the radius of the lbp operators ");
      helpString.push_back("@return the current radius of the lpb operator ");
    }
    if (functionName=="setNeighbours") {
      helpString.push_back("bool setNeighbours(const int32_t neighbours) ");
      helpString.push_back("Sets the neighbours value of the lbp operators ");
      helpString.push_back("@param neighbours integer containing the number of neighbours ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="getNeighbours") {
      helpString.push_back("int32_t getNeighbours() ");
      helpString.push_back("Gets the neighbours of the lbp operators ");
      helpString.push_back("@return the current radius of the lpb operator ");
    }
    if (functionName=="getTopBound") {
      helpString.push_back("int32_t getTopBound() ");
      helpString.push_back("Gets the top bound (Y) limit for the blobs ");
      helpString.push_back("@return the current top bound limit ");
    }
    if (functionName=="setTopBound") {
      helpString.push_back("bool setTopBound(const int32_t topBound) ");
      helpString.push_back("Sets the top bound (Y) limit for the blobs ");
      helpString.push_back("@param topBound, integer containing the topBound ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="getMinArcLength") {
      helpString.push_back("int32_t getMinArcLength() ");
      helpString.push_back("Gets the minimum arc length of the allowed blobs ");
      helpString.push_back("@return the current minimum arc length ");
    }
    if (functionName=="setMinArcLength") {
      helpString.push_back("bool setMinArcLength(const int32_t minArcLength) ");
      helpString.push_back("Sets the minimum arc length of the allowed blobs ");
      helpString.push_back("@param minArcLength, integer containing the minArcLength ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="getMaxArcLength") {
      helpString.push_back("int32_t getMaxArcLength() ");
      helpString.push_back("Gets the maximum arc length of the allowed blobs ");
      helpString.push_back("@return the current maximum arc length ");
    }
    if (functionName=="setMaxArcLength") {
      helpString.push_back("bool setMaxArcLength(const int32_t maxArcLength) ");
      helpString.push_back("Sets the maximum arc length of the allowed blobs ");
      helpString.push_back("@param maxArcLength, integer containing the maxArcLength ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="getNumIteration") {
      helpString.push_back("int32_t getNumIteration() ");
      helpString.push_back("Gets the number of iteration for the grabCut segmentation algorithm ");
      helpString.push_back("@return the current maximum arc length ");
    }
    if (functionName=="setNumIteration") {
      helpString.push_back("bool setNumIteration(const int32_t numIteration) ");
      helpString.push_back("Sets the number of iteration for the grabCut segmentation algorithm ");
      helpString.push_back("@param numIteration ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="resetAllValues") {
      helpString.push_back("bool resetAllValues() ");
      helpString.push_back("resets all values to the default ones. (acts as a backup) ");
      helpString.push_back("@return true/false on success/failure ");
    }
    if (functionName=="get_component_around") {
      helpString.push_back("yarp::os::Bottle get_component_around(const int32_t x, const int32_t y) ");
      helpString.push_back("Gets all the components (points) that belong to any of the segmented blobs ");
      helpString.push_back("@param x: x coordinate of seed point ");
      helpString.push_back("@param y: y coordinate of seed point ");
      helpString.push_back("@return Bottle containing a list of points bellonging to the segmented blob ");
    }
    if (functionName=="help") {
      helpString.push_back("std::vector<std::string> help(const std::string& functionName=\"--all\")");
      helpString.push_back("Return list of available commands, or help message for a specific function");
      helpString.push_back("@param functionName name of command for which to get a detailed description. If none or '--all' is provided, print list of available commands");
      helpString.push_back("@return list of strings (one string per line)");
    }
  }
  if ( helpString.empty()) helpString.push_back("Command not found");
  return helpString;
}


