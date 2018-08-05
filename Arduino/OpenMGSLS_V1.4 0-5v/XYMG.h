// XYMG.h

#ifndef _XYMG_h
#define _XYMG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "config.h"
#include "DueTimer.h"
#include "Planter.h"
#include <SPI.h>
extern bool IsMoving;
;

void XYMG_Init();
void XYMG_Move();
inline void XYMG_Write(unsigned short x, unsigned short y);
void XYMG_StartMove();

#endif

