//Elena Ceseracciu - RBCS, Istituto Italiano di Tecnologia, 2012
namespace yarp yarp.sig
/**
*  graphBasedSegmentationInterface
*
* Interface for a module that performs graphBasedSegmentation (with k, sigma, minRegion parameters)
*/

/// @cond

/**
 *Pixel position in the image frame
 */
struct Pixel
{
/** Index of pixel along horizontal axis */
1: i32 x;
/** Index of pixel along vertical axis */
2: i32 y;
}

/**
 * Interface for module that performs graph-based segmentation
 */
service SegmentationModuleInterface
{
/** Set sigma (smoothing) parameter for the algorithm
 * @param newValue new value for sigma parameter 
 */
void set_sigma(1:double newValue);
/** Set k (scale factor for boundary-detection threshold function) parameter for the algorithm
 * @param newValue new value for k parameter 
 */                
void set_k(1:double newValue);     
/** Set minRegion parameter for the algorithm, i.e., the minimum size of any segmented component
 * @param newValue new value for minRegion parameter 
 */        
void set_minRegion(1:double newValue);  
/** Get sigma (smoothing) parameter for the algorithm
 * @return current value for sigma parameter 
 */
double get_sigma();
/** Get k (scale factor for boundary-detection threshold function) parameter for the algorithm
 * @return current value for k parameter 
 */                
double get_k();    
/** Get minRegion parameter for the algorithm, i.e., the minimum size of any segmented component
 * @return current value for minRegion parameter 
 */        
double get_minRegion(); 
/** Get the number of segmented components that have been detected in the last provided image
 * @return number of segmented components
 */ 
i32 get_num_components();
/** Get the list of pixels corresponding to the component to which a given pixel belongs
 * @param objCenter a pixel belonging to the region of interest
 * @return list of pixels belonging to the same component as the input pixels
 */
list<Pixel> get_component_around(1:Pixel objCenter);
}

/// @endcond
