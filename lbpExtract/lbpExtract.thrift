#regionExtract.thrift


struct Bottle{}
(
    yarp.name = "yarp::os::Bottle"
    yarp.includefile="yarp/os/Bottle.h"
)

/**
* lbpExtract_IDLServer
*
* Interface.
*/

service lbpExtract_IDLServer
{
    /**
     *  Resets all the histograms
     * @return true/false on success/failure
     */
    bool reset();

    /**
     * Quit the module.
     * @return true/false on success/failure
     */
    bool quit();

    /**
     * Sets the radius of the lbp operators
     * @param radius integer containing the radius
     * @return true/false on success/failure
     **/
    bool setRadius(1:i32 radius);

    /**
     * Gets the radius of the lbp operators
     * @return the current radius of the lpb operator
     **/
    i32 getRadius();

    /**
     * Sets the neighbours value of the lbp operators
     * @param neighbours integer containing the number of neighbours
     * @return true/false on success/failure
     **/
    bool setNeighbours(1:i32 neighbours);

    /**
     * Gets the neighbours of the lbp operators
     * @return the current radius of the lpb operator
     **/
    i32 getNeighbours();

    /**
    * Gets the top bound (Y) limit for the blobs
    * @return the current top bound limit
    **/
    i32 getTopBound();

    /**
     * Sets the top bound (Y) limit for the blobs
     * @param topBound, integer containing the topBound
     * @return true/false on success/failure
     **/
    bool setTopBound(1:i32 topBound);

    /**
    * Gets the minimum arc length of the allowed blobs
    * @return the current minimum arc length
    **/
    i32 getMinArcLength();

    /**
    * Sets the minimum arc length of the allowed blobs
    * @param minArcLength, integer containing the minArcLength
    * @return true/false on success/failure
    **/
    bool setMinArcLength(1:i32 minArcLength);

    /**
    * Gets the maximum arc length of the allowed blobs
    * @return the current maximum arc length
    **/
    i32 getMaxArcLength();

    /**
    * Sets the maximum arc length of the allowed blobs
    * @param maxArcLength, integer containing the maxArcLength
    * @return true/false on success/failure
    **/
    bool setMaxArcLength(1:i32 maxArcLength);

    /**
     * Gets the maximum area of the allowed blobs
     * @return the current maximum area
     **/
    i32 getMaxArea();

    /**
     * Sets the maximum area of the allowed blobs
     * @param maxArea, integer containing the maxArea
     * @return true/false on success/failure
     **/
    bool setMaxArea(1:i32 maxArea);

    /**
     * Gets the minimum area of the allowed blobs
     * @return the current minimum area
     **/
    i32 getMinArea();

    /**
     * Sets the minimum area of the allowed blobs
     * @param minArea, integer containing the minArea
     * @return true/false on success/failure
     **/
    bool setMinArea(1:i32 minArea);

    /**
     * Gets the minimum width of the linear elements of the allowed blobs
     * @return the current minimum width
     **/
    i32 getMinWidth();

    /**
     * Sets the minimum width of the linear elements of the allowed blobs
     * @param minWidth, integer containing the minWidth
     * @return true/false on success/failure
     **/
    bool setMinWidth(1:i32 minWidth);

    /**
     * Gets the number of iteration for the grabCut segmentation algorithm
     * @return the current maximum arc length
     **/
    i32 getNumIteration();

    /**
     * Sets the number of iteration for the grabCut segmentation algorithm
     * @param numIteration
     * @return true/false on success/failure
     **/
    bool setNumIteration(1:i32 numIteration);

    /**
    * resets all values to the default ones. (acts as a backup)
    * @return true/false on success/failure
    **/
    bool resetAllValues();
    
    /**
     * Sets the offset of the bounding box. This increases the size of the bb
     * to add more backgound
     * @return true/false on success/failure
     **/
    bool setbbOffset(1:i32 offset);
    
    /**
     * Gets the current offset of the bounding box. 
     * @return true/false on success/failure
     **/
    i32 getbbOffset();

    /**
     * Sets the verbosity of the algorithm
     * @param boolVerbosity
     * @return true/false on success/failure
     **/
    bool verbosity(1:i32 boolVerbosity);

    /**
     * Gets all the components (points) that belong to any of the segmented blobs
     * @param x: x coordinate of seed point
     * @param y: y coordinate of seed point
     * @return Bottle containing a list of points belonging to the segmented blob
     **/
    Bottle get_component_around(1:i32 x, 2:i32 y);
}
