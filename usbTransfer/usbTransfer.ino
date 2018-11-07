#include <DigiCDC.h>

bool writeIRByte(char character)
{
	digitalWrite(5, HIGH);
	delay(10);
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
		delay(1);
	}
	char response;
	bool respStatus = readIRByte(response);
	if (respStatus)
	{
		if (response == character)
		{
			return true
		}
		else
		{
			return false
		}
	}
	else
	{
		return false
	}
}

bool readIRByte(char &character)
{
	digitalWrite(5, HIGH);
	delay(10);
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
		delay(1);
	}
}

void setup()
{
	SerialUSB.begin();
	pinMode(5, OUTPUT);
	pinMode(1, OUTPUT);
}

void loop()
{
	if (SerialUSB.available())
	{
		char input = SerialUSB.read();
		switch (input)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			if (SerialUSB.available())
			{
				input = SerialUSB.read();
				bool resp = writeIRByte(input);
				while (!(resp)){
					resp = writeIRByte(input);
				}
			}
			break;
		case 3:
			break;
		default:
			break;
		}
	}

	SerialUSB.refresh();
}