// 
// 
// 

#include "Movement.h"
#include "config.h"
#include "ComData.h"
#include "DAC_8522.h"
int X_DAVal_Now = 0;
int Y_DAVal_Now = 0;


int XY_Interpolation_Times = 0;

float Old_Point[4] = { 0 };
float Now_Point[4] = { 0 };
float Goal_Point[4] = { 0 };
float GCode_Point_Old[4] = { 0 };
float LinearLnterpolation = 0;

float X_Val_Countervail = 0;
float X_Val_Remainder = 0;
float Y_Val_Remainder = 0;
float X_Val_Interpolation = 0;
float Y_Val_Interpolation = 0;

float XY_Val_Remainder = 0;
float XY_Time = 0;

void Movement_setup() {

	pinMode(SS_X_Pin, OUTPUT);
	pinMode(SS_Y_Pin, OUTPUT);
	//home all axis
	DAC8552_Write(SS_X_Pin, 0x30, 0);
	DAC8552_Write(SS_X_Pin, 0x34, 0);
	DAC8552_Write(SS_Y_Pin, 0x30, 0);
	DAC8552_Write(SS_Y_Pin, 0x34, 0);
}

int X_DistanToDA(float X_Dis, float Y_Dis) {

	X_Dis = fabsf(X_Dis);
	return (int)(atan(X_Dis / (sqrtf(powf(FTheta_Dis, 2) + powf(Y_Dis, 2)) + XYmotor_Dis)) * 180 / PI / MGMax_Angle * 65536);
}

int Y_DistanToDA(float Dis) {

	Dis = fabsf(Dis);
	return (int)(atan(Dis / FTheta_Dis) * 180 / PI / MGMax_Angle * 65536);
}

float X_Countervail(float X_Dis, float Y_Dis) {

	float X_RadVal = atan(X_Dis / (sqrtf(powf(FTheta_Dis, 2) + powf(Y_Dis, 2)) + XYmotor_Dis));
	float Y_RadVal = atan(Y_Dis / FTheta_Dis);
	return X_Factor_Countervail*FTheta_Dis*tan(X_RadVal)*(1 / cos(Y_RadVal) - 1);
}

void Move_XY() {

	X_Val_Remainder = GCode_Point_Com[0] - GCode_Point_Old[0];
	Y_Val_Remainder = GCode_Point_Com[1] - GCode_Point_Old[1];
	XY_Val_Remainder = sqrtf(pow(X_Val_Remainder, 2) + pow(Y_Val_Remainder, 2));
	XY_Time = XY_Val_Remainder / XY_Speed;
	LinearLnterpolation = LinearLnterpolation_Cycle*XY_Time;
	X_Val_Interpolation = X_Val_Remainder / (LinearLnterpolation + (XY_Time - LinearLnterpolation*0.0004) / 0.0004);
	Y_Val_Interpolation = Y_Val_Remainder / (LinearLnterpolation + (XY_Time - LinearLnterpolation*0.0004) / 0.0004);

	if (Y_Val_Remainder > -0.000001 & Y_Val_Remainder < 0.000001) {
		Goal_Point[0] = GCode_Point_Old[0];
 
		if (X_Val_Remainder > 0) {

			while (Goal_Point[0] < GCode_Point_Com[0]- X_Val_Interpolation){
				Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
				Move_X(Goal_Point[0], Goal_Point[1]);
			//	Serial.println(Goal_Point[0]);
			}
		}

		else if (X_Val_Remainder < 0) {

			while(Goal_Point[0] > GCode_Point_Com[0] - X_Val_Interpolation){
				Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
				Move_X(Goal_Point[0], Goal_Point[1]);
			//	Serial.println(Goal_Point[0]);
			}
		}
	}
	else if (X_Val_Remainder > -0.000001&&X_Val_Remainder < 0.000001) {
		Goal_Point[1] = GCode_Point_Old[1];
		if (Y_Val_Remainder > 0) {

			while (Goal_Point[1] < GCode_Point_Com[1] - Y_Val_Interpolation){
				Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
				Move_X(Goal_Point[0], Goal_Point[1]);
				Move_Y(Goal_Point[1]);
			//	Serial.println(Goal_Point[1]);

			}
		}
		else if (Y_Val_Remainder < 0) {

			while (Goal_Point[1] > GCode_Point_Com[1] - Y_Val_Interpolation) {
				Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
				Move_X(Goal_Point[0], Goal_Point[1]);
				Move_Y(Goal_Point[1]);
			//	Serial.println(Goal_Point[1]);

			}
		}

	}
else {
	Goal_Point[0] = GCode_Point_Old[0];
	Goal_Point[1] = GCode_Point_Old[1];
		if (X_Val_Remainder > 0) {

			if (Y_Val_Remainder > 0) {

				while (Goal_Point[0] < GCode_Point_Com[0] - X_Val_Interpolation && Goal_Point[1] < GCode_Point_Com[1] - Y_Val_Interpolation) {

					Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
					Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
					Move_X(Goal_Point[0], Goal_Point[1]);
					Move_Y(Goal_Point[1]);

				} 

			}

			if (Y_Val_Remainder < 0) {

				while (Goal_Point[0] < GCode_Point_Com[0] - X_Val_Interpolation && Goal_Point[1] > GCode_Point_Com[1] - Y_Val_Interpolation) {
					Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
					Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
					Move_X(Goal_Point[0], Goal_Point[1]);
					Move_Y(Goal_Point[1]);

				} 
			}

		}
		else if (X_Val_Remainder < 0) {

			if (Y_Val_Remainder > 0) {

				while (Goal_Point[0] > GCode_Point_Com[0] - X_Val_Interpolation && Goal_Point[1] < GCode_Point_Com[1] - Y_Val_Interpolation) {
					Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
					Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
					Move_X(Goal_Point[0], Goal_Point[1]);
					Move_Y(Goal_Point[1]);

				} 
			}

			if (Y_Val_Remainder < 0) {

				while (Goal_Point[0] > GCode_Point_Com[0] - X_Val_Interpolation && Goal_Point[1] > GCode_Point_Com[1] - Y_Val_Interpolation) {
					Goal_Point[0] = Goal_Point[0] + X_Val_Interpolation;
					Goal_Point[1] = Goal_Point[1] + Y_Val_Interpolation;
					Move_X(Goal_Point[0], Goal_Point[1]);
					Move_Y(Goal_Point[1]);

				} 
			}

		}

	}


	Move_X(GCode_Point_Com[0], GCode_Point_Com[1]);
	Move_Y(GCode_Point_Com[1]);

	GCode_Point_Old[0] = GCode_Point_Com[0];
	GCode_Point_Old[1] = GCode_Point_Com[1];

}

void Move_X(float X_Goal, float Y_Goal) {
	if (X_Goal > 0) {
		X_Goal = X_Goal - X_Countervail(X_Goal, Y_Goal);
		DAC8552_Write(SS_X_Pin, 0x34, 0);
		DAC8552_Write(SS_X_Pin, 0x30, X_DistanToDA(X_Goal,Y_Goal));
	}
	else if (X_Goal < 0) {
		X_Goal = X_Goal - X_Countervail(X_Goal, Y_Goal);
		DAC8552_Write(SS_X_Pin, 0x30, 0);
		DAC8552_Write(SS_X_Pin, 0x34, X_DistanToDA(X_Goal,Y_Goal));
	}
	else if (X_Goal == 0) {
		DAC8552_Write(SS_X_Pin, 0x30, 0);
		DAC8552_Write(SS_X_Pin, 0x34, 0);
	}
}
void Move_Y(float Y_Goal) {
	if (Y_Goal > 0) {
		DAC8552_Write(SS_Y_Pin, 0x34, 0);
		DAC8552_Write(SS_Y_Pin, 0x30, Y_DistanToDA(Y_Goal));
	}
	else if (Y_Goal < 0) {
		DAC8552_Write(SS_Y_Pin, 0x30, 0);
		DAC8552_Write(SS_Y_Pin, 0x34, Y_DistanToDA(Y_Goal));
	}
	else if (Y_Goal == 0) {
		DAC8552_Write(SS_Y_Pin, 0x30, 0);
		DAC8552_Write(SS_Y_Pin, 0x34, 0);
	}
}



