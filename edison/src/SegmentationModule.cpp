// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <SegmentationModule.h>
#include <yarp/os/idl/WireTypes.h>



class SegmentationModule_set_sigmaS : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_sigmaR : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_minRegion : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_gradWindRad : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_threshold : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_mixture : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_set_speedup : public yarp::os::Portable {
public:
  SpeedUpLevelComm newSpeedLevel;
  void init(const SpeedUpLevelComm newSpeedLevel);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_sigmaS : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_sigmaR : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_minRegion : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_gradWindRad : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_threshold : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_mixture : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModule_get_speedup : public yarp::os::Portable {
public:
  SpeedUpLevelComm _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

bool SegmentationModule_set_sigmaS::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_sigmaS",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_sigmaS::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_sigmaS::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_sigmaR::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_sigmaR",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_sigmaR::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_sigmaR::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_minRegion::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_minRegion",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_minRegion::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_minRegion::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_gradWindRad::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_gradWindRad",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_gradWindRad::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_gradWindRad::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_threshold::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_threshold",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_threshold::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_threshold::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_mixture::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_mixture",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModule_set_mixture::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_mixture::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModule_set_speedup::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_speedup",1,2)) return false;
  if (!writer.writeI32((int32_t)newSpeedLevel)) return false;
  return true;
}

bool SegmentationModule_set_speedup::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModule_set_speedup::init(const SpeedUpLevelComm newSpeedLevel) {
  this->newSpeedLevel = newSpeedLevel;
}

bool SegmentationModule_get_sigmaS::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_sigmaS",1,2)) return false;
  return true;
}

bool SegmentationModule_get_sigmaS::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_sigmaS::init() {
  _return = (double)0;
}

bool SegmentationModule_get_sigmaR::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_sigmaR",1,2)) return false;
  return true;
}

bool SegmentationModule_get_sigmaR::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_sigmaR::init() {
  _return = (double)0;
}

bool SegmentationModule_get_minRegion::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_minRegion",1,2)) return false;
  return true;
}

bool SegmentationModule_get_minRegion::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_minRegion::init() {
  _return = (double)0;
}

bool SegmentationModule_get_gradWindRad::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_gradWindRad",1,2)) return false;
  return true;
}

bool SegmentationModule_get_gradWindRad::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_gradWindRad::init() {
  _return = (double)0;
}

bool SegmentationModule_get_threshold::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_threshold",1,2)) return false;
  return true;
}

bool SegmentationModule_get_threshold::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_threshold::init() {
  _return = (double)0;
}

bool SegmentationModule_get_mixture::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_mixture",1,2)) return false;
  return true;
}

bool SegmentationModule_get_mixture::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModule_get_mixture::init() {
  _return = (double)0;
}

bool SegmentationModule_get_speedup::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_speedup",1,2)) return false;
  return true;
}

bool SegmentationModule_get_speedup::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  int32_t ecast0;
  SpeedUpLevelCommVocab cvrt1;
  if (!reader.readEnum(ecast0,cvrt1)) {
    reader.fail();
    return false;
  } else {
    _return = (SpeedUpLevelComm)ecast0;
  }
  return true;
}

void SegmentationModule_get_speedup::init() {
  _return = (SpeedUpLevelComm)0;
}

SegmentationModule::SegmentationModule() {
  yarp().setOwner(*this);
}
void SegmentationModule::set_sigmaS(const double newValue) {
  SegmentationModule_set_sigmaS helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_sigmaS(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_sigmaR(const double newValue) {
  SegmentationModule_set_sigmaR helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_sigmaR(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_minRegion(const double newValue) {
  SegmentationModule_set_minRegion helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_minRegion(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_gradWindRad(const double newValue) {
  SegmentationModule_set_gradWindRad helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_gradWindRad(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_threshold(const double newValue) {
  SegmentationModule_set_threshold helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_threshold(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_mixture(const double newValue) {
  SegmentationModule_set_mixture helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_mixture(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModule::set_speedup(const SpeedUpLevelComm newSpeedLevel) {
  SegmentationModule_set_speedup helper;
  helper.init(newSpeedLevel);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModule::set_speedup(const SpeedUpLevelComm newSpeedLevel)");
  }
  yarp().write(helper,helper);
}
double SegmentationModule::get_sigmaS() {
  double _return = (double)0;
  SegmentationModule_get_sigmaS helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_sigmaS()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_sigmaR() {
  double _return = (double)0;
  SegmentationModule_get_sigmaR helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_sigmaR()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_minRegion() {
  double _return = (double)0;
  SegmentationModule_get_minRegion helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_minRegion()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_gradWindRad() {
  double _return = (double)0;
  SegmentationModule_get_gradWindRad helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_gradWindRad()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_threshold() {
  double _return = (double)0;
  SegmentationModule_get_threshold helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_threshold()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_mixture() {
  double _return = (double)0;
  SegmentationModule_get_mixture helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModule::get_mixture()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
SpeedUpLevelComm SegmentationModule::get_speedup() {
  SpeedUpLevelComm _return = (SpeedUpLevelComm)0;
  SegmentationModule_get_speedup helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","SpeedUpLevelComm SegmentationModule::get_speedup()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool SegmentationModule::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "set_sigmaS") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_sigmaS(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_sigmaR") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_sigmaR(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_minRegion") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_minRegion(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_gradWindRad") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_gradWindRad(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_threshold") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_threshold(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_mixture") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_mixture(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_speedup") {
      SpeedUpLevelComm newSpeedLevel;
      int32_t ecast2;
      SpeedUpLevelCommVocab cvrt3;
      if (!reader.readEnum(ecast2,cvrt3)) {
        reader.fail();
        return false;
      } else {
        newSpeedLevel = (SpeedUpLevelComm)ecast2;
      }
      set_speedup(newSpeedLevel);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_sigmaS") {
      double _return;
      _return = get_sigmaS();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_sigmaR") {
      double _return;
      _return = get_sigmaR();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_minRegion") {
      double _return;
      _return = get_minRegion();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_gradWindRad") {
      double _return;
      _return = get_gradWindRad();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_threshold") {
      double _return;
      _return = get_threshold();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_mixture") {
      double _return;
      _return = get_mixture();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_speedup") {
      SpeedUpLevelComm _return;
      _return = get_speedup();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32((int32_t)_return)) return false;
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

std::vector<std::string> SegmentationModule::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.push_back("*** Available commands:");
    helpString.push_back("set_sigmaS");
    helpString.push_back("set_sigmaR");
    helpString.push_back("set_minRegion");
    helpString.push_back("set_gradWindRad");
    helpString.push_back("set_threshold");
    helpString.push_back("set_mixture");
    helpString.push_back("set_speedup");
    helpString.push_back("get_sigmaS");
    helpString.push_back("get_sigmaR");
    helpString.push_back("get_minRegion");
    helpString.push_back("get_gradWindRad");
    helpString.push_back("get_threshold");
    helpString.push_back("get_mixture");
    helpString.push_back("get_speedup");
    helpString.push_back("help");
  }
  else {
    if (functionName=="set_sigmaS") {
      helpString.push_back("void set_sigmaS(const double newValue) ");
    }
    if (functionName=="set_sigmaR") {
      helpString.push_back("void set_sigmaR(const double newValue) ");
    }
    if (functionName=="set_minRegion") {
      helpString.push_back("void set_minRegion(const double newValue) ");
    }
    if (functionName=="set_gradWindRad") {
      helpString.push_back("void set_gradWindRad(const double newValue) ");
    }
    if (functionName=="set_threshold") {
      helpString.push_back("void set_threshold(const double newValue) ");
    }
    if (functionName=="set_mixture") {
      helpString.push_back("void set_mixture(const double newValue) ");
    }
    if (functionName=="set_speedup") {
      helpString.push_back("void set_speedup(const SpeedUpLevelComm newSpeedLevel) ");
    }
    if (functionName=="get_sigmaS") {
      helpString.push_back("double get_sigmaS() ");
    }
    if (functionName=="get_sigmaR") {
      helpString.push_back("double get_sigmaR() ");
    }
    if (functionName=="get_minRegion") {
      helpString.push_back("double get_minRegion() ");
    }
    if (functionName=="get_gradWindRad") {
      helpString.push_back("double get_gradWindRad() ");
    }
    if (functionName=="get_threshold") {
      helpString.push_back("double get_threshold() ");
    }
    if (functionName=="get_mixture") {
      helpString.push_back("double get_mixture() ");
    }
    if (functionName=="get_speedup") {
      helpString.push_back("SpeedUpLevelComm get_speedup() ");
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


