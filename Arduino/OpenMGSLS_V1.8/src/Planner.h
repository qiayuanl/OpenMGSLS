// Planner.h

#include <Arduino.h>
#include "config.h"
#include "Command.h"

extern int DAValBufferPlanCouter_int_Planner;
extern int DAValBufferMoveCouter_int_Planner;
extern int DAValBufferLen_int_Planner;

extern bool NeedOpenLaser_boolArry_Planner[DA_VAL_BUFF_SIZE];
extern int Times_LinearLnterpolation_intArry_Planner[DA_VAL_BUFF_SIZE];
extern unsigned short DAValBufferX_ushortPointer_Planner[DA_VAL_BUFF_SIZE][DA_VAL_ARRY_SIZE];
extern unsigned short DAValBufferY_ushortPointer_Planner[DA_VAL_BUFF_SIZE][DA_VAL_ARRY_SIZE];

void PlaneXY_Planner();
unsigned short DisToDA_X(float x, float y);
unsigned short DisToDA_Y(float y);
