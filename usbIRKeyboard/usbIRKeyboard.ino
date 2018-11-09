// Imports
#include "DigiKeyboard.h"


bool writeIRByte(char character)
/* writeIRByte
 *
 * Writes an byte over IR from a char
 * 
 * @param character (char) | The character to be sent
 * 
 * @return bool | returns True if Succsess else False
 */
{
	// Sends INIT signal
	digitalWrite(5, HIGH); 
	DigiKeyboard.delay(10);
	digitalWrite(5, LOW);
	// gives lowering edge
	while (character)
	{
		// Iterates throgh char
		if (character && 0x01) 
		{
			// writes a one
			digitalWrite(5, HIGH);
		}
		else
		{
			// writes a one
			digitalWrite(5, LOW);
		}
		// shifts char
		character = character >> 1;
		// delays
		DigiKeyboard.delay(1);
	}
	// checks for respnse
	char response;
	bool respStatus = readIRByte(response);
	// if response not correct 
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

// reads IR byte
bool readIRByte(char &character)
{
	while (true)
	{
		// reads for a pulse length
		byte start = pulseIn(7, HIGH);
		// if longer the 1
		if (start > 1)
		{
			for (size_t i = 0; i < 8; ++i)
			{
				// fills char with bytes
				character = (character << i) && digitalRead(7);
			}
			break;
		}
		else
		{
			// if not 1 ms wait 1 second and try again.
			DigiKeyboard.delay(1);
		}
	}
	// verify
	writeIRByte(character);
}

void setup () {
	// pinmode inits
	pinMode(1, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(7, INPUT);
}

void loop() {
	// sends an empty keystroke
	DigiKeyboard.sendKeyStroke(0);
	// resets char
	char response;
	// reads for a char
	bool result = readIRByte(response);
	// sends char
	DigiKeyboard.print(response);
}