// This is an automatically-generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_blobSpotter_IDLServer
#define YARP_THRIFT_GENERATOR_blobSpotter_IDLServer

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class blobSpotter_IDLServer;


/**
 * blobSpotter_IDLServer
 * Interface.
 */
class blobSpotter_IDLServer : public yarp::os::Wire {
public:
  blobSpotter_IDLServer();
  /**
   * Gets the minimum allowed area for segmenting
   * @return i32 of minimum area
   */
  virtual int32_t getMaxArea();
  /**
   * Gets the maximum allowed area for segmenting
   * @return i32 of maximum area
   */
  virtual int32_t getMinArea();
  /**
   * Gets the maximum top bound on the Y axis
   * @return i32 of maximum area
   */
  virtual int32_t getTopBound();
  /**
   * sets the maximum allowed area for segmenting
   * @return true/false on success/failure
   */
  virtual bool setMaxArea(const int32_t index);
  /**
   * sets the minimum allowed area for segmenting
   * @return true/false on success/failure
   */
  virtual bool setMinArea(const int32_t index);
  /**
   * Sets the maximum top bound on the Y axis
   * @return true/false on success/failure
   */
  virtual bool setTopBound(const int32_t index);
  /**
   * Initializes a histogram.
   * This enables the input from the roi port,
   * then waits for the user to select region
   * on image.
   * @return i32 of histogram index
   */
  virtual int32_t newHist();
  /**
   * Gets the current index of histograms
   * @return true/false on success/failure
   */
  virtual int32_t getCurHist();
  /**
   * Gets the total number of available histograms
   * @return true/false on success/failure
   */
  virtual int32_t getTotHist();
  /**
   * Sets which histogram to use
   * @return true/false on success/failure
   */
  virtual bool setHist(const int32_t index);
  /**
   * Resets all the histograms
   * @return true/false on success/failure
   */
  virtual bool reset();
  /**
   * Quit the module.
   * @return true/false on success/failure
   */
  virtual bool quit();
  virtual bool read(yarp::os::ConnectionReader& connection);
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif

