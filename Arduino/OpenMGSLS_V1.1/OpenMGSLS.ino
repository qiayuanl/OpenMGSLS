/*
 Name:		OpenMGSLS.ino
 Created:	5/7/2016 2:07:20 PM
 Author:	liaoq
*/

// the setup function runs once when you press reset or power the board

#include <SPI.h>
#include "ComData.h"
#include "Movement.h"
#include "config.h"
#include "DAC_8522.h"

void setup() {
	Serial.begin(Serial_Speed);
	DAC8552_SetUp();
	Movement_setup();
	delay(1000);


}

// the loop function runs over and over again until power down or reset
void loop() {
	Get_Comdata();
}
