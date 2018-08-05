// 
// 
// 
#include "config.h"
#include "ComData.h"
#include "DAC_8522.h"
#include "Movement.h"

String ComData = "";
int Key_DataLocation[2] = {0,0};//value location of key word .(val's star and end)
int Key_Star = 0;
bool Move = false;
float Key_Val = 0;
float GCode_Point_Com[4] = { 0 };


//find the value location of key word .
bool Find_Key(char key) {
	Key_DataLocation[0] = 0;
	Key_DataLocation[1] = 0;
	int l = 0; //location
	int i = 0; //have key word or not

	for (l=Key_Star; l < ComData.length(); l++)
	{
		if (ComData[l] == key) {
			Key_DataLocation[0] = l + 1;
			i = 1;
		}

		else if (ComData[l] == 'NULL' && i == 1) {  //the vale between the key word and ' ' 
			Key_DataLocation[1] = l-1 ;
			Key_Star = l+1 ;//make sure the ' ' which after key word will not be read again
			l = ComData.length();  //
		}
		else if (l == ComData.length()-1 && i == 1) {  //the vale between the key word and end(end location is comdata's length -1)
			Key_DataLocation[1] = l ;
			Key_Star = 0;
		}
	}

	if (i == 1) {
		Key_Val = Get_KeyVal();
		return true;
	}
	else {
		return false;
	}
}
//get the key val
float Get_KeyVal() {
	String Sval = " ";
	for (int l = Key_DataLocation[0]; l <= Key_DataLocation[1];l++) {
		Sval += ComData[l];
	}
	return Sval.toFloat();
}
//get G_code point value. 
void Get_Key() {

	if ((Find_Key('G')) && ((int)(Key_Val) == 0 || (int)(Key_Val) == 1)) {
		if (Find_Key('X')) {
			GCode_Point_Com[0] = Key_Val;
	
		}

		if (Find_Key('Y')) {
			GCode_Point_Com[1] = Key_Val;

			}
		Move_XY();
	}
	//home
	if ((Find_Key('G')) && (int)(Key_Val) == 28) {
		DAC8552_Write(SS_X_Pin, 0x30, 0);
		DAC8552_Write(SS_X_Pin, 0x34, 0);
		DAC8552_Write(SS_Y_Pin, 0x30, 0);
		DAC8552_Write(SS_Y_Pin, 0x34, 0);
	}
	if ((Find_Key('M')) ) {
		switch ((int)(Key_Val))
		{
			case 105:
			Serial.println("start");
			break;
		}
	
	}

}

//get G_code form Serial.
void Get_Comdata() {

	while (Serial.available() > 0)
	{
		ComData += char(Serial.read());
		delayMicroseconds(Serial_Delay); 

	}
	if (ComData.length() > 0)
	{
		Serial.println("ok");

		Get_Key();
		ComData = "";

	}
	
}

