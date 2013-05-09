// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <SegmentationModuleInterface.h>
#include <yarp/os/idl/WireTypes.h>

namespace yarp { namespace sig {


class SegmentationModuleInterface_set_sigma : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_sigma",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModuleInterface_set_k : public yarp::os::Portable {
public:
  double newValue;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("set_k",1,2)) return false;
    if (!writer.writeDouble(newValue)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    return true;
  }
};

class SegmentationModuleInterface_set_minRegion : public yarp::os::Portable {
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

class SegmentationModuleInterface_get_sigma : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_sigma",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) {
      reader.fail();
      return false;
    }
    return true;
  }
};

class SegmentationModuleInterface_get_k : public yarp::os::Portable {
public:
  double _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(2)) return false;
    if (!writer.writeTag("get_k",1,2)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readDouble(_return)) {
      reader.fail();
      return false;
    }
    return true;
  }
};

class SegmentationModuleInterface_get_minRegion : public yarp::os::Portable {
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
    if (!reader.readDouble(_return)) {
      reader.fail();
      return false;
    }
    return true;
  }
};

class SegmentationModuleInterface_get_num_components : public yarp::os::Portable {
public:
  int32_t _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(3)) return false;
    if (!writer.writeTag("get_num_components",1,3)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListReturn()) return false;
    if (!reader.readI32(_return)) {
      reader.fail();
      return false;
    }
    return true;
  }
};

class SegmentationModuleInterface_get_component_around : public yarp::os::Portable {
public:
  Pixel objCenter;
  std::vector<Pixel>  _return;
  virtual bool write(yarp::os::ConnectionWriter& connection) {
    yarp::os::idl::WireWriter writer(connection);
    if (!writer.writeListHeader(5)) return false;
    if (!writer.writeTag("get_component_around",1,3)) return false;
    if (!writer.write(objCenter)) return false;
    return true;
  }
  virtual bool read(yarp::os::ConnectionReader& connection) {
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
};

void SegmentationModuleInterface::set_sigma(const double newValue) {
  SegmentationModuleInterface_set_sigma helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModuleInterface::set_k(const double newValue) {
  SegmentationModuleInterface_set_k helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
void SegmentationModuleInterface::set_minRegion(const double newValue) {
  SegmentationModuleInterface_set_minRegion helper;
  helper.newValue = newValue;
  yarp().write(helper,helper);
}
double SegmentationModuleInterface::get_sigma() {
  double _return = (double)0;
  SegmentationModuleInterface_get_sigma helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModuleInterface::get_k() {
  double _return = (double)0;
  SegmentationModuleInterface_get_k helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
double SegmentationModuleInterface::get_minRegion() {
  double _return = (double)0;
  SegmentationModuleInterface_get_minRegion helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
int32_t SegmentationModuleInterface::get_num_components() {
  int32_t _return = 0;
  SegmentationModuleInterface_get_num_components helper;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
std::vector<Pixel>  SegmentationModuleInterface::get_component_around(const Pixel& objCenter) {
  std::vector<Pixel>  _return;
  SegmentationModuleInterface_get_component_around helper;
  helper.objCenter = objCenter;
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool SegmentationModuleInterface::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  yarp::os::ConstString tag = reader.readTag();
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
    if (reader.noMore()) { reader.fail(); return false; }
    yarp::os::ConstString next_tag = reader.readTag();
    if (next_tag=="") break;
    tag = tag + "_" + next_tag;
  }
  return false;
}
}} // namespace


