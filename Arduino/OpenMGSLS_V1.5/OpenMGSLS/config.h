#pragma once
//Command
#define SPEED_SERIAL 256000//650000
#define DELAY_SERIAL 40//microsencords 
#define CMD_SIZE_MAX 96 
//XYMG

#define SPEED_SPI 50000000
#define BASE_VOLTAGE 4.9//
#define LASER_OFF_POWER 2//0-255  correspond 0-5W (when the laser max power is 5W)
#define LASER_ON_POWER 255

#define PIN_XY 5
#define PIN_LASER 11
//planter
#define SPEED_XY 500 //  mm per seconds
#define DIS_F_THETA 330//distance between F-Theta and plane
#define DIS_XYMOTOR 8
#define RAD_MG_MAX 0.1745329 //the Mirror galvanometer max rad  (20/180*pi)
#define CYCLE_LNTERPOLARION 2000// per seconds
   