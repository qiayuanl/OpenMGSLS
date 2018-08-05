// 
// 
// 


#include "ComData.h"

ComDataClass::ComDataClass(int d):Delay(d)
{
}

void ComDataClass::Get() {

	while (Serial.available() > 0)
	{
		GCode += char(Serial.read());
		delayMicroseconds(Delay);
	}
	
	if (GCode.length() > 0)
	{

		if (Key('N')) {
		}
		if (Key('G')) {
			switch ((int)KeyVal.F)
			{
			case 1:
				if (Key('X')) {
					GCode_Point[0]= KeyVal.F;
				}
				if (Key('Y')) {
					GCode_Point[1]= KeyVal.F;
				}
				break;
			case 0:
				if (Key('X')) {
					GCode_Point[0]= KeyVal.F;
				}
				if (Key('Y')) {
					GCode_Point[1]= KeyVal.F;
				}
				break;
			}
			NeedMove_XY = true;
		}

		else if (Key('M')) {
			switch ((int)KeyVal.F)
			{
			case 105:
				Serial.println("start");
				break;
			}
		}
		GCode = "";
		KeyStart = 0;
		KeyEnd = 0;
		Serial.println("ok");
	}
}

bool ComDataClass::Key(char key) {

	KeyStart = GCode.indexOf(key, KeyStart);
	if (KeyStart >= 0) {   //when no found keyword ,the indexOf function return -1
		KeyEnd = GCode.indexOf(' ', KeyEnd + 1);

		if (KeyEnd >= 0) {
			KeyVal.S = GCode.substring(KeyStart + 1, KeyEnd);
		}
		else {
			KeyEnd= GCode.indexOf('*', KeyEnd + 1);
			if (KeyEnd >= 0)
			{
				KeyVal.S = GCode.substring(KeyStart + 1, KeyEnd);
			}
			else {
				KeyVal.S = GCode.substring(KeyStart + 1);
			}
		}

		KeyVal.F = KeyVal.S.toFloat();
		return true;
	}
	else {
		KeyStart = 0; //when KeyStart == 0 ,the fun : String.indexOf(key, KeyStart) have not do anything
		return false;
	}

}


