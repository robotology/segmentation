enum SpeedUpLevelComm{NO_SPEEDUP_COMM, MED_SPEEDUP_COMM, HIGH_SPEEDUP_COMM}

service SegmentationModule
{
void set_sigmaS(1:double newValue);		
void set_sigmaR(1:double newValue);		
void set_minRegion(1:double newValue);  
void set_gradWindRad(1:double newValue); 
void set_threshold(1:double newValue); 
void set_mixture(1:double newValue);  
void set_speedup(1: SpeedUpLevelComm newSpeedLevel); 
double get_sigmaS();		
double get_sigmaR();		
double get_minRegion();  
double get_gradWindRad(); 
double get_threshold(); 
double get_mixture();  
SpeedUpLevelComm get_speedup(); 
}
