// config.h

//ComData
#define Serial_Speed 650000
#define Serial_Delay 12//microsencords 
//DAC_8522

#define SPI_Speed 50000000
#define RerferVoltage 5.025 // Get the DAC8522 +5V Voltage an put it in here

//Movememt
#define SS_X_Pin 12
#define SS_Y_Pin 13 


#define XY_Speed 2000.0 //  mm per seconds
#define X_Factor_Countervail 7.1
#define FTheta_Dis 330//distance between F-Theta and plane
#define StrokeMax_Dis 100
#define XYmotor_Dis 8
#define MGMax_Angle 10 //the Mirror galvanometer max angle
#define LinearLnterpolation_Cycle 2000.0// per seconds

//Laser
