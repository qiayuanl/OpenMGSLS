/******************************************************************************
				  DAC8552模块

		功能：DAC8552双路输出电压

		硬件原理图：
              P0.0    -->   DAC8552_DIN
              P0.1    -->   DAC8552_SCLK
              P0.2    -->   DAC8552_SYNC

		Time：2012、10、1
		By：梦想电子工作室
		shop：mcu-dream.taobao.com

******************************************************************************/

#include <reg51.h>

#define uchar unsigned char
#define uint unsigned int

sbit DAC8552_DIN  = P0^0;			/***********************************需要修改*******************************************/
sbit DAC8552_SCLK = P0^1;		 	/***********************************需要修改*******************************************/
sbit DAC8552_SYNC = P0^2;		  	/***********************************需要修改*******************************************/

void Write_DAC8552(uchar Command, uint Data);
uint Voltage_Convert(float Vref, float voltage);

void main(void)
{
	Write_DAC8552(0x30, Voltage_Convert(5.0,2));    	//Write channel A buffer (0x30)
    Write_DAC8552(0x34, Voltage_Convert(5.0,3.5));    	//Write channel B buffer (0x34)	
}

///*******************************************
//		函数名称：Write_DAC8552
//		功    能：选择通道，设定输出电压
//		参    数：Command -> 通道A/B，0x30=A、0x34=B   
//          	  Data -> 输出电压
//		返回值  ：无
//********************************************/
void Write_DAC8552(uchar Command, uint Data)
{
	uchar i;

	DAC8552_SYNC = 1;
	DAC8552_SYNC = 0;

	for (i=0; i<8; i++)              //Write 8 bit command 
	{
		DAC8552_SCLK = 1;
		if (Command & 0x80)
		{
			DAC8552_DIN = 1;
		}
		else
		{
			DAC8552_DIN = 0;
		}
		DAC8552_SCLK = 0;
		Command <<= 1;
	}

	for (i=0; i<16; i++)             //write 16 bit data
	{
		DAC8552_SCLK = 1;
		if (Data & 0x8000)
		{
			DAC8552_DIN = 1;
		}
		else
		{
			DAC8552_DIN = 0;
		}
		DAC8552_SCLK = 0;
		Data <<= 1;
	}
	DAC8552_SYNC = 1;
}

///*******************************************
//		函数名称：Voltage_Convert
//		功    能：输入参考电压和需要输出的电压，得到DA数值
//		参    数：Vref -> 参考电压   
//          	  voltage -> 需要输出的电压
//		返回值  ：DA数值
//********************************************/
uint Voltage_Convert(float Vref, float voltage)
{
	uint _D_;
	_D_ = (uint)(65536 * voltage / Vref);
    
	return _D_;
}