// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <SegmentationModule.h>
#include <yarp/os/idl/WireTypes.h>



class SegmentationModule_set_sigmaS : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_sigmaS",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_sigmaR : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_sigmaR",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_minRegion : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_minRegion",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_gradWindRad : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_gradWindRad",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_threshold : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_threshold",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_mixture : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_mixture",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_set_speedup : public yarp::os::Portable {
public:
  SpeedUpLevelComm newSpeedLevel;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_speedup",1,2)) return false;
    if (!writer.writeI32((int32_t)newSpeedLevel)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModule_get_sigmaS : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_sigmaS",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_sigmaR : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_sigmaR",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_minRegion : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_minRegion",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_gradWindRad : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_gradWindRad",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_threshold : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_threshold",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_mixture : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_mixture",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) return false;
    return true;
  }
};

class SegmentationModule_get_speedup : public yarp::os::Portable {
public:
  SpeedUpLevelComm _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_speedup",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    int32_t ecast0;
    SpeedUpLevelCommVocab cvrt1;
    if (!reader.readEnum(ecast0,cvrt1)) return false;
    _return = (SpeedUpLevelComm)ecast0;
    return true;
  }
};

void SegmentationModule::set_sigmaS(const double newValue) {
  SegmentationModule_set_sigmaS helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_sigmaR(const double newValue) {
  SegmentationModule_set_sigmaR helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_minRegion(const double newValue) {
  SegmentationModule_set_minRegion helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_gradWindRad(const double newValue) {
  SegmentationModule_set_gradWindRad helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_threshold(const double newValue) {
  SegmentationModule_set_threshold helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_mixture(const double newValue) {
  SegmentationModule_set_mixture helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModule::set_speedup(const SpeedUpLevelComm newSpeedLevel) {
  SegmentationModule_set_speedup helper;
  helper.newSpeedLevel = newSpeedLevel;
  yarp().write(helper,helper);
}
double SegmentationModule::get_sigmaS() {
  double _return = (double)0;
  SegmentationModule_get_sigmaS helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_sigmaR() {
  double _return = (double)0;
  SegmentationModule_get_sigmaR helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_minRegion() {
  double _return = (double)0;
  SegmentationModule_get_minRegion helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_gradWindRad() {
  double _return = (double)0;
  SegmentationModule_get_gradWindRad helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_threshold() {
  double _return = (double)0;
  SegmentationModule_get_threshold helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModule::get_mixture() {
  double _return = (double)0;
  SegmentationModule_get_mixture helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
SpeedUpLevelComm SegmentationModule::get_speedup() {
  SpeedUpLevelComm _return = (SpeedUpLevelComm)0;
  SegmentationModule_get_speedup helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool SegmentationModule::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) return false;
  yarp::os::ConstString tag = reader.readTag();
  while (!reader.isError()) {    // TODO: use quick lookup, this is just a test
    if (tag == "set_sigmaS") {
      double newValue;
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readDouble(newValue)) return false;
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
      if (!reader.readEnum(ecast2,cvrt3)) return false;
      newSpeedLevel = (SpeedUpLevelComm)ecast2;
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
    yarp::os::ConstString next_tag = reader.readTag();
    if (next_tag=="") break;
    tag = tag + "_" + next_tag;
  }
  return false;
}


