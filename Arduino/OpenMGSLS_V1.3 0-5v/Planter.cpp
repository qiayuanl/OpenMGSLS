// 
// 
// 
#include "Planter.h"

 PlanterClass::PlanterClass(float a,float v,float s,float df,float dx,int c)
	 :RadVal_MaxAngle(a / 180.0 * PI), Countervail_Voltage(5 / v), Speed(s),Dis_F_Theta(df),Dis_XYMotor(dx), Cycle(c)
{
}

 void PlanterClass::Plane_XY(float point[3], unsigned short *x, unsigned short *y, int *t)
	 //plan the xy monent data and turn to  DAVal
	 //and put the XY arry address in two pointer
 {
	 Goal_X = point[0];
	 Goal_Y = point[1];
	 Dis_X = Goal_X - Start_X;
	 Dis_Y = Goal_Y - Start_Y;
	 Times_LinearLnterpolation = sqrt(Dis_X*Dis_X + Dis_Y*Dis_Y) / Speed*Cycle;

	 if (Times_LinearLnterpolation != 0) { //calculate all the LinearLnterpolation
		 unsigned short *DAVal_X = new unsigned short[Times_LinearLnterpolation];
		 unsigned short *DAVal_Y = new unsigned short[Times_LinearLnterpolation];
		 if (Dis_X != 0) {
			 Plus_X = (Dis_X) / Times_LinearLnterpolation;
		 }
		 else
		 {
			 Plus_X = 0;
		 }
		 if (Dis_Y == 0) {
			 Plus_Y = (Dis_Y) / Times_LinearLnterpolation;
		 }
		 else {
			 Plus_Y = 0;
		 }

		 Plane_X = Start_X;
		 Plane_Y = Start_Y;

		 while (T_LinearLnterpolation != Times_LinearLnterpolation)
		 {
			 Plane_X = Plane_X + Plus_X;
			 Plane_Y = Plane_Y + Plus_Y;
			 DAVal_X[T_LinearLnterpolation] = DisToDA_X(Plane_X, Plane_Y);
			 DAVal_Y[T_LinearLnterpolation] = DisToDA_Y(Plane_Y);
			 T_LinearLnterpolation++;
		 }
		 x = DAVal_X;
		 y = DAVal_Y;
		 *t = T_LinearLnterpolation;
		 Start_X = Goal_X;
		 Start_Y = Goal_Y;
		 T_LinearLnterpolation = 0;
	 }
	 else {//when the dis is evry small
		 *t = 0;
		 unsigned short DAVal_X[1] = { DisToDA_X(Goal_X, Goal_Y) };
		 unsigned short DAVal_Y[1] = { DisToDA_Y(Goal_Y) };
		 x = DAVal_X;
		 y = DAVal_Y;
		 Start_X = Goal_X;
		 Start_Y = Goal_Y;
	 }
 }

int PlanterClass::DisToDA_X(float x, float y) {
	RadVal_X = atan(x / (sqrtf(Dis_F_Theta*Dis_F_Theta + y*y) + Dis_XYMotor));
	RadVal_Y = atan(y / Dis_F_Theta);

	return atan((x- (Dis_F_Theta*tan(RadVal_X)*(1 / cos(RadVal_Y) - 1)) )/ (sqrtf(Dis_F_Theta*Dis_F_Theta + y*y) + Dis_XYMotor)) / RadVal_MaxAngle * 32768 + 32767;
}

int PlanterClass::DisToDA_Y(float y) {
	return  RadVal_Y / RadVal_MaxAngle * 32768 + 32767;
}

