// 
// 
// 
//this part of control theory is base on : 
//http://hwml.com/LeibRamp.pdf

#include "Stepper.h"
float Stepper_Multiplier[3];
float Stepper_Delay_Period[3];

int Stepper_Distance_Goal_Step[3];
int Stepper_Distance_Now_Step[3];
int Stepper_Distance_Acceleration_Step[3];

float Z_Position_Old;

bool IsMoving_A;
bool IsMoving_B;
bool IsMoving_C;

int Stepper_Acceleration_Step[3] = {
	STEPPER_A_ACCELERATION*STEPPER_A_STEP_PER_UNIT,
	STEPPER_B_ACCELERATION*STEPPER_B_STEP_PER_UNIT,
	STEPPER_C_ACCELERATION*STEPPER_C_STEP_PER_UNIT,
};

int Stepper_Speed_Step[3]{
	STEPPER_A_SPEED*STEPPER_A_STEP_PER_UNIT,
	STEPPER_B_SPEED*STEPPER_B_STEP_PER_UNIT,
	STEPPER_C_SPEED*STEPPER_C_STEP_PER_UNIT,
};

void Stepper_Init() {
	pinMode(STEPPER_A_PIN_STEP, OUTPUT);
	pinMode(STEPPER_B_PIN_STEP, OUTPUT);
	pinMode(STEPPER_C_PIN_STEP, OUTPUT);
	pinMode(STEPPER_A_PIN_DIR, OUTPUT);
	pinMode(STEPPER_B_PIN_DIR, OUTPUT);
	pinMode(STEPPER_C_PIN_DIR, OUTPUT);
	Stepper_Distance_Acceleration_Step[0] = Stepper_Speed_Step[0] * Stepper_Speed_Step[0] / (2 * Stepper_Acceleration_Step[0]);
	Stepper_Multiplier[0] = Stepper_Acceleration_Step[0] / 1000000.0 / 1000000.0;
	Stepper_Distance_Acceleration_Step[1] = Stepper_Speed_Step[1] * Stepper_Speed_Step[1] / (2 * Stepper_Acceleration_Step[1]);
	Stepper_Multiplier[1] = Stepper_Acceleration_Step[1] / 1000000.0 / 1000000.0;
	Stepper_Distance_Acceleration_Step[2] = Stepper_Speed_Step[2] * Stepper_Speed_Step[2] / (2 * Stepper_Acceleration_Step[2]);
	Stepper_Multiplier[2] = Stepper_Acceleration_Step[2] / 1000000.0 / 1000000.0;
}
void StepperA_StartMove(float dis) {

	Stepper_Distance_Goal_Step[0] = dis*STEPPER_A_STEP_PER_UNIT;

	if (Stepper_Distance_Goal_Step[0] > 0)
		digitalWrite(STEPPER_A_PIN_DIR, STEPPER_A_NEGATE);

	else
		digitalWrite(STEPPER_A_PIN_DIR, !STEPPER_A_NEGATE);

	Stepper_Distance_Goal_Step[0] = abs(Stepper_Distance_Goal_Step[0]);

	if (Stepper_Distance_Acceleration_Step[0] > Stepper_Distance_Goal_Step[0] / 2)
		Stepper_Distance_Acceleration_Step[0] = Stepper_Distance_Goal_Step[0] / 2;

	Stepper_Delay_Period[0] = 1000000.0 / sqrtf(2 * Stepper_Acceleration_Step[0]);
	IsMoving_A = true;
	STEPPER_A_TIMER.attachInterrupt(StepperA_Moving).setPeriod(Stepper_Delay_Period[0]).start();

}
void StepperA_Moving() {
		if (Stepper_Distance_Now_Step[0] < Stepper_Distance_Goal_Step[0]) {
		Stepper_Distance_Now_Step[0]++;
		digitalWrite(STEPPER_A_PIN_STEP, HIGH);
		
		if (Stepper_Distance_Now_Step[0] >= Stepper_Distance_Goal_Step[0] - Stepper_Distance_Acceleration_Step[0])
			Stepper_Delay_Period[0] = Stepper_Delay_Period[0] * (1 + Stepper_Multiplier[0] * Stepper_Delay_Period[0] * Stepper_Delay_Period[0]);
		else if (Stepper_Distance_Now_Step[0] < Stepper_Distance_Acceleration_Step[0])
			Stepper_Delay_Period[0] = Stepper_Delay_Period[0] * (1 - Stepper_Multiplier[0] * Stepper_Delay_Period[0] * Stepper_Delay_Period[0]);
		
		digitalWrite(STEPPER_A_PIN_STEP, LOW);
		STEPPER_A_TIMER.setPeriod(Stepper_Delay_Period[0]).start();
	}
	else {
		STEPPER_A_TIMER.stop();
		IsMoving_A = false;
		Stepper_Distance_Now_Step[0] = 0;
	}
}

void StepperB_StartMove(float dis) {

		Stepper_Distance_Goal_Step[1] = dis*STEPPER_B_STEP_PER_UNIT;
	if (Stepper_Distance_Goal_Step[1] > 0)
		digitalWrite(STEPPER_B_PIN_DIR, STEPPER_B_NEGATE);
	else
		digitalWrite(STEPPER_B_PIN_DIR, !STEPPER_B_NEGATE);

	Stepper_Distance_Goal_Step[1] = abs(Stepper_Distance_Goal_Step[1]);

	if (Stepper_Distance_Acceleration_Step[1] > Stepper_Distance_Goal_Step[1] / 2)
		Stepper_Distance_Acceleration_Step[1] = Stepper_Distance_Goal_Step[1] / 2;

	Stepper_Delay_Period[1] = 1000000.0 / sqrtf(2 * Stepper_Acceleration_Step[1]);
	IsMoving_B = true;
	STEPPER_B_TIMER.attachInterrupt(StepperB_Moving).setPeriod(Stepper_Delay_Period[1]).start();

}
void StepperB_Moving() {
	if (Stepper_Distance_Now_Step[1] < Stepper_Distance_Goal_Step[1]) {
		Stepper_Distance_Now_Step[1]++;
		digitalWrite(STEPPER_B_PIN_STEP, HIGH);

		if (Stepper_Distance_Now_Step[1] >= Stepper_Distance_Goal_Step[1] - Stepper_Distance_Acceleration_Step[1])
			Stepper_Delay_Period[1] = Stepper_Delay_Period[1] * (1 + Stepper_Multiplier[1] * Stepper_Delay_Period[1] * Stepper_Delay_Period[1]);
		else if (Stepper_Distance_Now_Step[1] < Stepper_Distance_Acceleration_Step[1])
			Stepper_Delay_Period[1] = Stepper_Delay_Period[1] * (1 - Stepper_Multiplier[1] * Stepper_Delay_Period[1] * Stepper_Delay_Period[1]);

		digitalWrite(STEPPER_B_PIN_STEP, LOW);
		STEPPER_B_TIMER.setPeriod(Stepper_Delay_Period[1]).start();
	}
	else {
		STEPPER_B_TIMER.stop();
		IsMoving_B = false;
		Stepper_Distance_Now_Step[1] = 0;
	}
}
void StepperC_StartMove(float dis) {

		Stepper_Distance_Goal_Step[2] = dis*STEPPER_C_STEP_PER_UNIT;

	if (Stepper_Distance_Goal_Step[2] > 0)
		digitalWrite(STEPPER_C_PIN_DIR, STEPPER_C_NEGATE);

	else
		digitalWrite(STEPPER_C_PIN_DIR, !STEPPER_C_NEGATE);

	Stepper_Distance_Goal_Step[2] = abs(Stepper_Distance_Goal_Step[2]);

	if (Stepper_Distance_Acceleration_Step[2] > Stepper_Distance_Goal_Step[2] / 2)
		Stepper_Distance_Acceleration_Step[2] = Stepper_Distance_Goal_Step[2] / 2;

	Stepper_Delay_Period[2] = 1000000.0 / sqrtf(2 * Stepper_Acceleration_Step[2]);
	IsMoving_C = true;
	STEPPER_C_TIMER.attachInterrupt(StepperC_Moving).setPeriod(Stepper_Delay_Period[2]).start();

}
void StepperC_Moving() {
	if (Stepper_Distance_Now_Step[2] < Stepper_Distance_Goal_Step[2]) {
		Stepper_Distance_Now_Step[2]++;
		digitalWrite(STEPPER_C_PIN_STEP, HIGH);

		if (Stepper_Distance_Now_Step[2] >= Stepper_Distance_Goal_Step[2] - Stepper_Distance_Acceleration_Step[2])
			Stepper_Delay_Period[2] = Stepper_Delay_Period[2] * (1 + Stepper_Multiplier[2] * Stepper_Delay_Period[2] * Stepper_Delay_Period[2]);
		else if (Stepper_Distance_Now_Step[2] < Stepper_Distance_Acceleration_Step[2])
			Stepper_Delay_Period[2] = Stepper_Delay_Period[2] * (1 - Stepper_Multiplier[2] * Stepper_Delay_Period[2] * Stepper_Delay_Period[2]);

		digitalWrite(STEPPER_C_PIN_STEP, LOW);
		STEPPER_C_TIMER.setPeriod(Stepper_Delay_Period[2]).start();
	}
	else {
		STEPPER_C_TIMER.stop();
		IsMoving_C = false;
		Stepper_Distance_Now_Step[2] = 0;
	}
}
