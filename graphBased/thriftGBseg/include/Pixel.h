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
  // Fields
  /**
   * Index of pixel along horizontal axis
   */
  std::int32_t x;
  /**
   * Index of pixel along vertical axis
   */
  std::int32_t y;

  // Default constructor
  Pixel() : x(0), y(0) {
  }

  // Constructor with field values
  Pixel(const std::int32_t x,const std::int32_t y) : x(x), y(y) {
  }

  // Copy constructor
  Pixel(const Pixel& __alt) : WirePortable(__alt)  {
    this->x = __alt.x;
    this->y = __alt.y;
  }

  // Assignment operator
  const Pixel& operator = (const Pixel& __alt) {
    this->x = __alt.x;
    this->y = __alt.y;
    return *this;
  }

  // read and write structure on a connection
  bool read(yarp::os::idl::WireReader& reader) override;
  bool read(yarp::os::ConnectionReader& connection) override;
  bool write(yarp::os::idl::WireWriter& writer) override;
  bool write(yarp::os::ConnectionWriter& connection) override;

private:
  bool write_x(yarp::os::idl::WireWriter& writer);
  bool nested_write_x(yarp::os::idl::WireWriter& writer);
  bool write_y(yarp::os::idl::WireWriter& writer);
  bool nested_write_y(yarp::os::idl::WireWriter& writer);
  bool read_x(yarp::os::idl::WireReader& reader);
  bool nested_read_x(yarp::os::idl::WireReader& reader);
  bool read_y(yarp::os::idl::WireReader& reader);
  bool nested_read_y(yarp::os::idl::WireReader& reader);

public:

  std::string toString();

  // if you want to serialize this class without nesting, use this helper
  typedef yarp::os::idl::Unwrapped<yarp::sig::Pixel > unwrapped;

  class Editor : public yarp::os::Wire, public yarp::os::PortWriter {
  public:

    Editor() {
      group = 0;
      obj_owned = true;
      obj = new Pixel;
      dirty_flags(false);
      yarp().setOwner(*this);
    }

    Editor(Pixel& obj) {
      group = 0;
      obj_owned = false;
      edit(obj,false);
      yarp().setOwner(*this);
    }

    bool edit(Pixel& obj, bool dirty = true) {
      if (obj_owned) delete this->obj;
      this->obj = &obj;
      obj_owned = false;
      dirty_flags(dirty);
      return true;
    }

    virtual ~Editor() {
    if (obj_owned) delete obj;
    }

    bool isValid() const {
      return obj!=0/*NULL*/;
    }

    Pixel& state() { return *obj; }

    void begin() { group++; }

    void end() {
      group--;
      if (group==0&&is_dirty) communicate();
    }
    void set_x(const std::int32_t x) {
      will_set_x();
      obj->x = x;
      mark_dirty_x();
      communicate();
      did_set_x();
    }
    void set_y(const std::int32_t y) {
      will_set_y();
      obj->y = y;
      mark_dirty_y();
      communicate();
      did_set_y();
    }
    std::int32_t get_x() {
      return obj->x;
    }
    std::int32_t get_y() {
      return obj->y;
    }
    virtual bool will_set_x() { return true; }
    virtual bool will_set_y() { return true; }
    virtual bool did_set_x() { return true; }
    virtual bool did_set_y() { return true; }
    void clean() {
      dirty_flags(false);
    }
    bool read(yarp::os::ConnectionReader& connection) override;
    bool write(yarp::os::ConnectionWriter& connection) override;
  private:

    Pixel *obj;

    bool obj_owned;
    int group;

    void communicate() {
      if (group!=0) return;
      if (yarp().canWrite()) {
        yarp().write(*this);
        clean();
      }
    }
    void mark_dirty() {
      is_dirty = true;
    }
    void mark_dirty_x() {
      if (is_dirty_x) return;
      dirty_count++;
      is_dirty_x = true;
      mark_dirty();
    }
    void mark_dirty_y() {
      if (is_dirty_y) return;
      dirty_count++;
      is_dirty_y = true;
      mark_dirty();
    }
    void dirty_flags(bool flag) {
      is_dirty = flag;
      is_dirty_x = flag;
      is_dirty_y = flag;
      dirty_count = flag ? 2 : 0;
    }
    bool is_dirty;
    int dirty_count;
    bool is_dirty_x;
    bool is_dirty_y;
  };
};

#endif
