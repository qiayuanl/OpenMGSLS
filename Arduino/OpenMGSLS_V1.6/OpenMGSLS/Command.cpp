// 
// 
// 

#include "Command.h"

String GCode_String;
char Serial_Char;
int KeyStart_int;
int KeyEnd_int;
float GCode_Arry_Command[6];//X,Y,Z,A,B,C

bool NeedMove_bool_Command[5];//XY,Z,A,B,C
bool NeedOpen_Laser;
bool Comment_Command;

struct
{
	String S;
	float F;
}KeyVal_struct;


void Command_Init()
{
	Serial.begin(SPEED_SERIAL);
}

void Command_Get()
{
	/**
	* Loop while serial characters are incoming and the queue is not full
	*/
	while (Serial.available() > 0)
	{
		Serial_Char = Serial.read();
		if (Serial_Char == ';')
			Comment_Command = true;
		if (Comment_Command == false)
			GCode_String += Serial_Char;
		delayMicroseconds(DELAY_SERIAL);
	}

	if (GCode_String.length() > 0)
	{
		if (Command_Key('G')) {
			switch ((int)KeyVal_struct.F)
			{
			case 1:
				if (Command_Key('Z')) {
					GCode_Arry_Command[2] = KeyVal_struct.F;
					NeedMove_bool_Command[1] = true;
				}
				if (Command_Key('X')) {
					GCode_Arry_Command[0] = KeyVal_struct.F;
					NeedMove_bool_Command[0] = true;
				}
				if (Command_Key('Y')) {
					GCode_Arry_Command[1] = KeyVal_struct.F;
					NeedMove_bool_Command[0] = true;
				}
				else if (Command_Key('A')) {
					GCode_Arry_Command[3] = KeyVal_struct.F;
					NeedMove_bool_Command[2] = true;
				}
				else if (Command_Key('B')) {
					GCode_Arry_Command[4] = KeyVal_struct.F;
					NeedMove_bool_Command[3] = true;
				}
				else if (Command_Key('C')) {
					GCode_Arry_Command[5] = KeyVal_struct.F;
					NeedMove_bool_Command[4] = true;
				}
				break;
			}
			if (Command_Key('E')) {
				NeedOpen_Laser = true;
			}
		}
		else if (Command_Key('M')) {
			switch ((int)KeyVal_struct.F)
			{
			case 105:
				Serial.println("start");
				break;
			}
		}
	}
	Serial.println("ok");
	Comment_Command = false;
	GCode_String = "";
	KeyStart_int = 0;
	KeyEnd_int = 0;
}

inline bool Command_Key(char key) 
{
	KeyStart_int = GCode_String.indexOf(key, KeyStart_int);
	if (KeyStart_int >= 0) {   //when no found keyword ,the indexOf function return -1
		KeyEnd_int = GCode_String.indexOf(' ', KeyEnd_int + 1);

		if (KeyEnd_int >= 0) {
			KeyVal_struct.S = GCode_String.substring(KeyStart_int + 1, KeyEnd_int);
		}
		else {
			KeyEnd_int = GCode_String.indexOf('*', KeyEnd_int + 1);
			if (KeyEnd_int >= 0)
			{
				KeyVal_struct.S = GCode_String.substring(KeyStart_int + 1, KeyEnd_int);
			}
			else {
				KeyVal_struct.S = GCode_String.substring(KeyStart_int + 1);
			}
		}

		KeyVal_struct.F = KeyVal_struct.S.toFloat();
		return true;
	}
	else {
		KeyStart_int = 0; //when KeyStart_int == 0 ,the fun : String.indexOf(key, KeyStart_int) have not do anything
		return false;
	}

}
