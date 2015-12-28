// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_lbpExtract_IDLServer
#define YARP_THRIFT_GENERATOR_lbpExtract_IDLServer

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include <yarp/os/Bottle.h>

class lbpExtract_IDLServer;


/**
 * lbpExtract_IDLServer
 * Interface.
 */
class lbpExtract_IDLServer : public yarp::os::Wire {
public:
  lbpExtract_IDLServer();
  /**
   *  Resets all the histograms
   * @return true/false on success/failure
   */
  virtual bool reset();
  /**
   * Quit the module.
   * @return true/false on success/failure
   */
  virtual bool quit();
  /**
   * Sets the radius of the lbp operators
   * @param radius integer containing the radius
   * @return true/false on success/failure
   */
  virtual bool setRadius(const int32_t radius);
  /**
   * Gets the radius of the lbp operators
   * @return the current radius of the lpb operator
   */
  virtual int32_t getRadius();
  /**
   * Sets the neighbours value of the lbp operators
   * @param neighbours integer containing the number of neighbours
   * @return true/false on success/failure
   */
  virtual bool setNeighbours(const int32_t neighbours);
  /**
   * Gets the neighbours of the lbp operators
   * @return the current radius of the lpb operator
   */
  virtual int32_t getNeighbours();
  /**
   * Gets the top bound (Y) limit for the blobs
   * @return the current top bound limit
   */
  virtual int32_t getTopBound();
  /**
   * Sets the top bound (Y) limit for the blobs
   * @param topBound, integer containing the topBound
   * @return true/false on success/failure
   */
  virtual bool setTopBound(const int32_t topBound);
  /**
   * Gets the minimum arc length of the allowed blobs
   * @return the current minimum arc length
   */
  virtual int32_t getMinArcLength();
  /**
   * Sets the minimum arc length of the allowed blobs
   * @param minArcLength, integer containing the minArcLength
   * @return true/false on success/failure
   */
  virtual bool setMinArcLength(const int32_t minArcLength);
  /**
   * Gets the maximum arc length of the allowed blobs
   * @return the current maximum arc length
   */
  virtual int32_t getMaxArcLength();
  /**
   * Sets the maximum arc length of the allowed blobs
   * @param maxArcLength, integer containing the maxArcLength
   * @return true/false on success/failure
   */
  virtual bool setMaxArcLength(const int32_t maxArcLength);
  /**
   * Gets the number of iteration for the grabCut segmentation algorithm
   * @return the current maximum arc length
   */
  virtual int32_t getNumIteration();
  /**
   * Sets the number of iteration for the grabCut segmentation algorithm
   * @param numIteration
   * @return true/false on success/failure
   */
  virtual bool setNumIteration(const int32_t numIteration);
  /**
   * resets all values to the default ones. (acts as a backup)
   * @return true/false on success/failure
   */
  virtual bool resetAllValues();
  /**
   * Gets all the components (points) that belong to any of the segmented blobs
   * @param x: x coordinate of seed point
   * @param y: y coordinate of seed point
   * @return Bottle containing a list of points bellonging to the segmented blob
   */
  virtual yarp::os::Bottle get_component_around(const int32_t x, const int32_t y);
  virtual bool read(yarp::os::ConnectionReader& connection);
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif

