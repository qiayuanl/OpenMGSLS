// 
// 
// 

#include "XYMG.h"

bool IsMoving;
int Times_Now;

void XYMG_Init()
{
	pinMode(PIN_XY, OUTPUT);
	pinMode(PIN_LASER, OUTPUT);
	digitalWrite(PIN_XY, HIGH);
	SPI.begin();
	SPI.beginTransaction(SPISettings(SPEED_SPI, MSBFIRST, SPI_MODE1));
	XYMG_Write(32767 * 5 / BASE_VOLTAGE, 32767 * 5 / BASE_VOLTAGE);
	analogWrite(PIN_LASER, 2);
}

/*
DAC8552
http://www.ti.com/product/DAC8552
Vout = (Din/(2^n))*Vref
Din is straight binary
0 <= Din <= 65535
n = 16
=> Vout = (Din/65536)*Vref

|            COMMAND              |                      DATA							|
|D23 D22 D21 D20 D19 D18 D17 D16  |D15 D14 D13 D12 D11 D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0|
|  0   0   1   1   0   0   0   0  |=>WR Buffer A w/Data and Load DACs A and B  (0x30)
|  0   0   1   1   0   1   0   0  |=>WR Buffer B w/Data and Load DACs A and B  (0x34)

*/

inline void XYMG_Write(unsigned short x, unsigned short y)//write the DAVal to DAC8552
{
	digitalWrite(PIN_XY, LOW);
	SPI.transfer(0x30);
	SPI.transfer16(x);
	digitalWrite(PIN_XY, HIGH);
	digitalWrite(PIN_XY, LOW);
	SPI.transfer(0x34);
	SPI.transfer16(y);
	digitalWrite(PIN_XY, HIGH);
}

void XYMG_Move()
{
	if (Times_Now != Times_LinearLnterpolation_int_Planter) {
		XYMG_Write(DAValX_ushortPointer_Planter[Times_Now], DAValY_ushortPointer_Planter[Times_Now]);
		Times_Now++;
	}
	else {
		Timer5.stop();
		IsMoving = false;
		delete[] DAValX_ushortPointer_Planter;
		delete[] DAValY_ushortPointer_Planter;
	}
}

void XYMG_StartMove()
//move according to the array DA data
{
	Times_Now = 0;
	IsMoving = true;
	Timer5.attachInterrupt(XYMG_Move).setFrequency(CYCLE_LNTERPOLARION).start();
}

