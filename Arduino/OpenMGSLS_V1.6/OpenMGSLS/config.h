#pragma once
//Command
#define SPEED_SERIAL 57600
#define DELAY_SERIAL 200//microsencords 

//XYMG

#define SPEED_SPI 50000000
#define BASE_VOLTAGE 4.9//
#define LASER_OFF_POWER 2//0-255  correspond 0-5W (when the laser max power is 5W)
#define LASER_ON_POWER 255
#define PIN_XY 5
#define PIN_LASER 11
//Stepper
#define STEPPER_A_STEP_PER_UNIT 13.3333
#define STEPPER_A_ACCELERATION 300
#define STEPPER_A_TIMER Timer4
#define STEPPER_A_SPEED 200
#define STEPPER_A_PIN_STEP 44
#define STEPPER_A_PIN_DIR 42
#define STEPPER_A_NEGATE true

#define STEPPER_B_STEP_PER_UNIT 200
#define STEPPER_B_ACCELERATION 100
#define STEPPER_B_TIMER Timer6
#define STEPPER_B_SPEED 50
#define STEPPER_B_PIN_STEP 48
#define STEPPER_B_PIN_DIR 46
#define STEPPER_B_NEGATE false


#define STEPPER_C_STEP_PER_UNIT 200
#define STEPPER_C_ACCELERATION 100
#define STEPPER_C_TIMER Timer6
#define STEPPER_C_SPEED 50
#define STEPPER_C_PIN_STEP 52
#define STEPPER_C_PIN_DIR 50
#define STEPPER_C_NEGATE false


#define Stepper_A_DISTANCE_MAX 360
//planter
#define SPEED_XY 600 //  mm per seconds
#define DIS_F_THETA 260//distance between F-Theta and plane
#define DIS_XYMOTOR 8
#define RAD_MG_MAX 0.349065 //the Mirror galvanometer max rad  (20/180*pi)
#define CYCLE_LNTERPOLARION 1000// per seconds
   