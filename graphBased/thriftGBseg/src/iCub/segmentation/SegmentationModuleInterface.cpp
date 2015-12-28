// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <iCub/segmentation/SegmentationModuleInterface.h>
#include <yarp/os/idl/WireTypes.h>

namespace yarp { namespace sig {


class SegmentationModuleInterface_set_sigma : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_set_k : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_set_minRegion : public yarp::os::Portable {
public:
  double newValue;
  void init(const double newValue);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_get_sigma : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_get_k : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_get_minRegion : public yarp::os::Portable {
public:
  double _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_get_num_components : public yarp::os::Portable {
public:
  int32_t _return;
  void init();
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

class SegmentationModuleInterface_get_component_around : public yarp::os::Portable {
public:
  Pixel objCenter;
  std::vector<Pixel>  _return;
  void init(const Pixel& objCenter);
  virtual bool write(yarp::os::ConnectionWriter& connection);
  virtual bool read(yarp::os::ConnectionReader& connection);
};

bool SegmentationModuleInterface_set_sigma::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_sigma",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModuleInterface_set_sigma::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModuleInterface_set_sigma::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModuleInterface_set_k::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_k",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModuleInterface_set_k::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModuleInterface_set_k::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModuleInterface_set_minRegion::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_minRegion",1,2)) return false;
  if (!writer.writeDouble(newValue)) return false;
  return true;
}

bool SegmentationModuleInterface_set_minRegion::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  return true;
}

void SegmentationModuleInterface_set_minRegion::init(const double newValue) {
  this->newValue = newValue;
}

bool SegmentationModuleInterface_get_sigma::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_sigma",1,2)) return false;
  return true;
}

bool SegmentationModuleInterface_get_sigma::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModuleInterface_get_sigma::init() {
  _return = (double)0;
}

bool SegmentationModuleInterface_get_k::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_k",1,2)) return false;
  return true;
}

bool SegmentationModuleInterface_get_k::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModuleInterface_get_k::init() {
  _return = (double)0;
}

bool SegmentationModuleInterface_get_minRegion::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_minRegion",1,2)) return false;
  return true;
}

bool SegmentationModuleInterface_get_minRegion::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readDouble(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModuleInterface_get_minRegion::init() {
  _return = (double)0;
}

bool SegmentationModuleInterface_get_num_components::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("get_num_components",1,3)) return false;
  return true;
}

bool SegmentationModuleInterface_get_num_components::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void SegmentationModuleInterface_get_num_components::init() {
  _return = 0;
}

bool SegmentationModuleInterface_get_component_around::write(yarp::os::ConnectionWriter& connection) {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(5)) return false;
  if (!writer.writeTag("get_component_around",1,3)) return false;
  if (!writer.write(objCenter)) return false;
  return true;
}

bool SegmentationModuleInterface_get_component_around::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  {
    _return.clear();
    uint32_t _size0;
    yarp::os::idl::WireState _etype3;
    reader.readListBegin(_etype3, _size0);
    _return.resize(_size0);
    uint32_t _i4;
    for (_i4 = 0; _i4 < _size0; ++_i4)
    {
      if (!reader.readNested(_return[_i4])) {
        reader.fail();
        return false;
      }
    }
    reader.readListEnd();
  }
  return true;
}

void SegmentationModuleInterface_get_component_around::init(const Pixel& objCenter) {
  this->objCenter = objCenter;
}

SegmentationModuleInterface::SegmentationModuleInterface() {
  yarp().setOwner(*this);
}
void SegmentationModuleInterface::set_sigma(const double newValue) {
  SegmentationModuleInterface_set_sigma helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModuleInterface::set_sigma(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModuleInterface::set_k(const double newValue) {
  SegmentationModuleInterface_set_k helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModuleInterface::set_k(const double newValue)");
  }
  yarp().write(helper,helper);
}
void SegmentationModuleInterface::set_minRegion(const double newValue) {
  SegmentationModuleInterface_set_minRegion helper;
  helper.init(newValue);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","void SegmentationModuleInterface::set_minRegion(const double newValue)");
  }
  yarp().write(helper,helper);
}
double SegmentationModuleInterface::get_sigma() {
  double _return = (double)0;
  SegmentationModuleInterface_get_sigma helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModuleInterface::get_sigma()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModuleInterface::get_k() {
  double _return = (double)0;
  SegmentationModuleInterface_get_k helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModuleInterface::get_k()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModuleInterface::get_minRegion() {
  double _return = (double)0;
  SegmentationModuleInterface_get_minRegion helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","double SegmentationModuleInterface::get_minRegion()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t SegmentationModuleInterface::get_num_components() {
  int32_t _return = 0;
  SegmentationModuleInterface_get_num_components helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","int32_t SegmentationModuleInterface::get_num_components()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
std::vector<Pixel>  SegmentationModuleInterface::get_component_around(const Pixel& objCenter) {
  std::vector<Pixel>  _return;
  SegmentationModuleInterface_get_component_around helper;
  helper.init(objCenter);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","std::vector<Pixel>  SegmentationModuleInterface::get_component_around(const Pixel& objCenter)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool SegmentationModuleInterface::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "set_sigma") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_sigma(newValue);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(0)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_k") {
      double newValue;
      if (!reader.readDouble(newValue)) {
        reader.fail();
        return false;
      }
      set_k(newValue);
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
    if (tag == "get_sigma") {
      double _return;
      _return = get_sigma();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeDouble(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_k") {
      double _return;
      _return = get_k();
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
    if (tag == "get_num_components") {
      int32_t _return;
      _return = get_num_components();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "get_component_around") {
      Pixel objCenter;
      if (!reader.read(objCenter)) {
        reader.fail();
        return false;
      }
      std::vector<Pixel>  _return;
      _return = get_component_around(objCenter);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        {
          if (!writer.writeListBegin(BOTTLE_TAG_LIST, static_cast<uint32_t>(_return.size()))) return false;
          std::vector<Pixel> ::iterator _iter5;
          for (_iter5 = _return.begin(); _iter5 != _return.end(); ++_iter5)
          {
            if (!writer.writeNested((*_iter5))) return false;
          }
          if (!writer.writeListEnd()) return false;
        }
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

std::vector<std::string> SegmentationModuleInterface::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.push_back("*** Available commands:");
    helpString.push_back("set_sigma");
    helpString.push_back("set_k");
    helpString.push_back("set_minRegion");
    helpString.push_back("get_sigma");
    helpString.push_back("get_k");
    helpString.push_back("get_minRegion");
    helpString.push_back("get_num_components");
    helpString.push_back("get_component_around");
    helpString.push_back("help");
  }
  else {
    if (functionName=="set_sigma") {
      helpString.push_back("void set_sigma(const double newValue) ");
      helpString.push_back("Set sigma (smoothing) parameter for the algorithm ");
      helpString.push_back("@param newValue new value for sigma parameter ");
    }
    if (functionName=="set_k") {
      helpString.push_back("void set_k(const double newValue) ");
      helpString.push_back("Set k (scale factor for boundary-detection threshold function) parameter for the algorithm ");
      helpString.push_back("@param newValue new value for k parameter ");
    }
    if (functionName=="set_minRegion") {
      helpString.push_back("void set_minRegion(const double newValue) ");
      helpString.push_back("Set minRegion parameter for the algorithm, i.e., the minimum size of any segmented component ");
      helpString.push_back("@param newValue new value for minRegion parameter ");
    }
    if (functionName=="get_sigma") {
      helpString.push_back("double get_sigma() ");
      helpString.push_back("Get sigma (smoothing) parameter for the algorithm ");
      helpString.push_back("@return current value for sigma parameter ");
    }
    if (functionName=="get_k") {
      helpString.push_back("double get_k() ");
      helpString.push_back("Get k (scale factor for boundary-detection threshold function) parameter for the algorithm ");
      helpString.push_back("@return current value for k parameter ");
    }
    if (functionName=="get_minRegion") {
      helpString.push_back("double get_minRegion() ");
      helpString.push_back("Get minRegion parameter for the algorithm, i.e., the minimum size of any segmented component ");
      helpString.push_back("@return current value for minRegion parameter ");
    }
    if (functionName=="get_num_components") {
      helpString.push_back("int32_t get_num_components() ");
      helpString.push_back("Get the number of segmented components that have been detected in the last provided image ");
      helpString.push_back("@return number of segmented components ");
    }
    if (functionName=="get_component_around") {
      helpString.push_back("std::vector<Pixel>  get_component_around(const Pixel& objCenter) ");
      helpString.push_back("Get the list of pixels corresponding to the component to which a given pixel belongs ");
      helpString.push_back("@param objCenter a pixel belonging to the region of interest ");
      helpString.push_back("@return list of pixels belonging to the same component as the input pixels ");
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
}} // namespace


