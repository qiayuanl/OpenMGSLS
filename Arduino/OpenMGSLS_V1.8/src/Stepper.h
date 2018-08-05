// Stepper.h


#include "config.h"
#include "DueTimer.h"
void Init_Stepper();

void StepperA_Moving();
void StepperB_Moving();
void StepperC_Moving();

void StepperA_StartMove(float dis);
void StepperB_StartMove(float dis);
void StepperC_StartMove(float dis);
extern float Z_Position_Old;
extern bool IsMoving_A;
extern bool IsMoving_B;
extern bool IsMoving_C;
