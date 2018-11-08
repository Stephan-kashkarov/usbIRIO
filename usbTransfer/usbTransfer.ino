#include <DigiCDC.h>

bool writeIRByte(char character)
{
	digitalWrite(5, HIGH);
	SerialUSB.delay(10);
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
		SerialUSB.delay(1);
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
		if (start > 1)
		{

			for (size_t i = 0; i < 8; ++i)
			{
				character = (character << i) && digitalRead(7);
			}
			break;
		}
		else
		{
			SerialUSB.delay(1);
		}
	}
	writeIRByte(character);
}

void setup()
{
	SerialUSB.begin();
	pinMode(1, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(7, INPUT);
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
					while (!(resp))
					{
						resp = writeIRByte(input);
					}
				}
				break;
			case 3:
				while (true)
				{	bool inp = readIRByte(input);
					if (inp){

					}
				}
				break;
			default:
				break;
		}
	}

	SerialUSB.refresh();
}