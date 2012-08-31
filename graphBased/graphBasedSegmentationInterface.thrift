//Elena Ceseracciu - RBCS, Istituto Italiano di Tecnologia, 2012

struct Pixel
{
1: i32 x;
2: i32 y;
}

service SegmentationModuleInterface
{
void set_sigma(1:double newValue);		
void set_k(1:double newValue);		
void set_minRegion(1:double newValue);  
double get_sigma();		
double get_k();		
double get_minRegion();  
i32 get_num_components();
list<Pixel> get_component_around(1:Pixel objCenter);
}
