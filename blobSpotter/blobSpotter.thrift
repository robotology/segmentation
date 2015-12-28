#blobSpotter.thrift

/**
* blobSpotter_IDLServer
*
* Interface. 
*/

service blobSpotter_IDLServer
{
    /**
     * Gets the minimum allowed area for segmenting
     * @return i32 of minimum area
     */
    i32 getMaxArea();
    
    /**
     * Gets the maximum allowed area for segmenting
     * @return i32 of maximum area
     */
    i32 getMinArea();
    
    /**
     * Gets the maximum top bound on the Y axis
     * @return i32 of maximum area
     */
    i32 getTopBound();
    
    /**
     * sets the maximum allowed area for segmenting
     * @return true/false on success/failure
     */
    bool setMaxArea(1:i32 index);
    
    /**
     * sets the minimum allowed area for segmenting
     * @return true/false on success/failure
     */
    bool setMinArea(1:i32 index);
    
    /**
     * Sets the maximum top bound on the Y axis
     * @return true/false on success/failure
     */
    bool setTopBound(1:i32 index);
    
    /**
    * Initializes a histogram.
    * This enables the input from the roi port, 
    * then waits for the user to select region 
    * on image.
    * @return i32 of histogram index
    */
    i32 newHist();
    
    /**
     * Gets the current index of histograms
     * @return true/false on success/failure
     */
    i32 getCurHist();

    /**
     * Gets the total number of available histograms
     * @return true/false on success/failure
     */
    i32 getTotHist();

    /**
     * Sets which histogram to use
     * @return true/false on success/failure
     */
    bool setHist(1:i32 index);

    /**
     * Resets all the histograms
     * @return true/false on success/failure
     */
    bool reset();

    /**
     * Quit the module.
     * @return true/false on success/failure
     */
    bool quit();

}
