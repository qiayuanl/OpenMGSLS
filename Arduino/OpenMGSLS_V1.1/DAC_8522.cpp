// 
//  
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

#include "DAC_8522.h"
#include "config.h"
#include <SPI.h>
//start SPI
void DAC8552_SetUp() {
	SPI.begin();
	SPI.beginTransaction(SPISettings(SPI_Speed, MSBFIRST, SPI_MODE1));
}

//write the DA val 
void DAC8552_Write(unsigned int Axis,char Command, unsigned int Data) {
	digitalWrite(SS_X_Pin,HIGH);
	digitalWrite(SS_Y_Pin,HIGH);
	digitalWrite(Axis, HIGH);
	digitalWrite(Axis, LOW);
	SPI.transfer(Command);
	SPI.transfer16(Data);
	digitalWrite(Axis, HIGH);
}

