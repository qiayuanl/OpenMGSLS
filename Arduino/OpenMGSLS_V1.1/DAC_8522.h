// DAC_8522.h

#ifndef _DAC_8522_h
#define _DAC_8522_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


void DAC8552_SetUp();
void DAC8552_Write(unsigned int Axis,char Command, unsigned int Data);

#endif

