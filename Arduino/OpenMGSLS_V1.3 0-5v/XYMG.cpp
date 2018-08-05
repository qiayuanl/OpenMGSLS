// 
// 
// 

#include "XYMG.h"
XYMGClass::XYMGClass(int p,int s ,int c):Pin_XY=p,Speed_SPI(s),Cycle_Linerpolarion(c)
{
}

void XYMGClass::init()
{
	pinMode(Pin_XY, OUTPUT);
	digitalWrite(Pin_XY, HIGH);
	SPI.begin();
	SPI.beginTransaction(SPISettings(Speed_SPI, MSBFIRST, SPI_MODE1));
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

void XYMGClass::Write(unsigned short x, unsigned short y)//write the DAVal to DAC8552
{
	Serial.print(x);
	Serial.print("  ");
	Serial.println(y);  
	digitalWrite(Pin_XY, LOW);
	SPI.transfer(0x30);
	SPI.transfer16(x);
	digitalWrite(Pin_XY, HIGH);
	digitalWrite(Pin_XY, LOW);
	SPI.transfer(0x34);
	SPI.transfer16(y);
	digitalWrite(Pin_XY, HIGH);
}


void XYMGClass::Move(unsigned short * x, unsigned short * y,int t)
//move according to the array DA data
{
	if (t != 0) {
		Arry_X = x;
		Arry_Y = y;
		T = 0;
		IsMoving = true;
		Timer5.attachInterrupt(Move_XY).setFrequency(Cycle_Linerpolarion).start();
	}
	else {
		Write(x[0], y[0]);
	}

}

void XYMGClass::Move_XY()
{
	
	if (Times_Now == T) {
		Timer5.stop();
		XYMG.IsMoving = false;
		Times = 0;
	}
	else {
		Write(Arry_X[Times_Now], Arry_Y[Times_Now]);
		Times_Now++;
	}
	
}



