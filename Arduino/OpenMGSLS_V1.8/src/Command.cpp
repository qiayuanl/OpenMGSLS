//
//
//

#include "Command.h"

String GCodeBuff_StringArry_Command[GCODE_BUFF_SIZE];

char Serial_Char_Command;

int GCodeBuffGetCouter_int_Command;
int GCodeBuffProcessCouter_int_Commmand;
int GCodeBuffLen_int_Command;


int KeyStart_int_Command;
int KeyEnd_int_Command;


float GCodeVal_floatArry_Command[6];//X,Y,Z,A,B,C

bool NeedMove_boolArry_Command[6];//XY,E,Z,A,B,C
bool CommentMode_bool_Command;

struct
{
	String S;
	float F;
    long L;
}KeyVal_struct;

void Init_Command()
{
	MYSERIAL.begin(SPEED_SERIAL);
}


void Get_Command()
{
	/**
	* Loop while serial characters are incoming and the queue is not full
	*/
	while (MYSERIAL.available() > 0 && (GCodeBuffLen_int_Command < GCODE_BUFF_SIZE-1))
	{
		Serial_Char_Command = MYSERIAL.read();
		if (Serial_Char_Command == '\r' ||
			Serial_Char_Command == '\n' ||
			(Serial_Char_Command == ':' && CommentMode_bool_Command == false)) {
 			if (!GCodeBuff_StringArry_Command[GCodeBuffGetCouter_int_Command].length()) {
				CommentMode_bool_Command = false;
				return;
			}
			if (!CommentMode_bool_Command) {
				CommentMode_bool_Command = false;
				GCodeBuffGetCouter_int_Command = (GCodeBuffGetCouter_int_Command + 1) % GCODE_BUFF_SIZE;
				GCodeBuffLen_int_Command++;
			}
			GCodeBuff_StringArry_Command[GCodeBuffGetCouter_int_Command] = "";
		}
		else {
			if (Serial_Char_Command == ';') {
				CommentMode_bool_Command = true;
			}
			if (!CommentMode_bool_Command) {
				GCodeBuff_StringArry_Command[GCodeBuffGetCouter_int_Command] += Serial_Char_Command;
			}
		}
	}
	delay(15);
}
void Process_Command() {

	if (Command_Key('G')) {

		switch ((int)KeyVal_struct.F)
		{
		case 1:
			if (Command_Key('Z')) {
				GCodeVal_floatArry_Command[2] = KeyVal_struct.F;
				NeedMove_boolArry_Command[2] = true;
			}
			if (Command_Key('X')) {
				GCodeVal_floatArry_Command[0] = KeyVal_struct.F;
				NeedMove_boolArry_Command[0] = true;

			}
			if (Command_Key('Y')) {
				GCodeVal_floatArry_Command[1] = KeyVal_struct.F;
				NeedMove_boolArry_Command[0] = true;
			}
			else if (Command_Key('A')) {
				GCodeVal_floatArry_Command[3] = KeyVal_struct.F;
				NeedMove_boolArry_Command[3] = true;
			}
			else if (Command_Key('B')) {
				GCodeVal_floatArry_Command[4] = KeyVal_struct.F;
				NeedMove_boolArry_Command[4] = true;
			}
			else if (Command_Key('C')) {
				GCodeVal_floatArry_Command[5] = KeyVal_struct.F;
				NeedMove_boolArry_Command[5] = true;
			}
			break;
		case 90:
			MYSERIAL.println("start");
			break;
		}
		if (Command_Key('E')) {
			NeedMove_boolArry_Command[1] = true;
		}
	}
	else if (Command_Key('M')) {
		switch ((int)KeyVal_struct.F)
		{
		case 105:
			break;
		case 888:
		Start_Heating();
			break;
		case 889:
		Stop_Heating();
			break;
		}
	}
	GCodeBuffProcessCouter_int_Commmand = (GCodeBuffProcessCouter_int_Commmand + 1) % GCODE_BUFF_SIZE;
	GCodeBuffLen_int_Command--;
	MYSERIAL.println("ok");
}



inline bool Command_Key(char key)
{
	 KeyStart_int_Command = GCodeBuff_StringArry_Command[GCodeBuffProcessCouter_int_Commmand].indexOf(key);
	 if (KeyStart_int_Command >= 0) {   //when no found keyword ,the indexOf function return -1
		KeyEnd_int_Command = GCodeBuff_StringArry_Command[GCodeBuffProcessCouter_int_Commmand].substring(KeyStart_int_Command).indexOf(' ');
		if (KeyEnd_int_Command >= 0) {
			KeyVal_struct.S = GCodeBuff_StringArry_Command[GCodeBuffProcessCouter_int_Commmand].substring(KeyStart_int_Command + 1,KeyStart_int_Command + KeyEnd_int_Command);
		}

		else {
			KeyVal_struct.S = GCodeBuff_StringArry_Command[GCodeBuffProcessCouter_int_Commmand].substring(KeyStart_int_Command + 1);

		}
		KeyVal_struct.L = KeyVal_struct.S.toInt();
		KeyVal_struct.F = KeyVal_struct.S.toFloat();
		return true;
	}
	else {
		return false;
	}

}
