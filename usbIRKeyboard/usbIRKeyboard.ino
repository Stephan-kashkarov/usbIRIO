#include "DigiKeyboard.h"

bool writeIRByte(char character)
{
	digitalWrite(5, HIGH);
	DigiKeyboard.delay(10);
	digitalWrite(5, LOW);
	while (character)
	{

		if (character && 0x01)
		{
			digitalWrite(5, HIGH);
		}
		else
		{
			digitalWrite(5, LOW);
		}
		character = character >> 1;
		DigiKeyboard.delay(1);
	}
	char response;
	bool respStatus = readIRByte(response);
	if (respStatus)
	{
		if (response == character)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool readIRByte(char &character)
{
	while (true)
	{
		byte start = pulseIn(7, HIGH);
		if (start == 10)
		{

			for (size_t i = 0; i < 8; ++i)
			{
				character = (character << i) && digitalRead(7);
			}
			break;
		}
		else
		{
			DigiKeyboard.delay(1);
		}
	}
	writeIRByte(character);
}

void setup () {
	pinMode(1, OUTPUT);
}

void loop() {
	DigiKeyboard.sendKeyStroke(0);
	char response;
	bool result = readIRByte(response);
	DigiKeyboard.print(response);
}