#include <stdio.h>
#include <iostream>
#include <fstream>
#include "keyreader.h"

using namespace std;

// gets user input
int getOperation()
{
	int action;
	bool valid = false;
	while (!(valid))
	{
		cout << "Please Select Action:" << endl;
		cout << "	0. IR mouse OUTPUT" << endl;
		cout << "	1. IR mouse INPUT" << endl;
		cout << "	2. IR keyboard OUTPUT" << endl;
		cout << "	3. IR keyboard INPUT" << endl;
		cin >> action;

		// validates action
		for (size_t i = 0; i < 4; i++)
		{
			if (action == i)
			{
				valid = true;
			}
		}
		if (valid == false)
		{
			cout << "Enter a valid input";
		}
	}
	return action;
}

int main()
{
	// initalises the interface with usb
	ofstream arduino;
	arduino.open("/dev/ttyUSB0");
	// makes key reader
	KeyReader reader;
	// variable init
	char input;

	// gets operation
	int operation = getOperation();
	// sends operation to arduino
	arduino << operation;


	// switches by operation
	switch (operation)
	{
		case 0: {// IR mouse OUTPUT
			cout << "feature not yet avalible" << endl;

			break;
		}
		case 1:{ // IR mouse INPUT
			cout << "feature not yet avalible" << endl;
			// cout << "IR Mouse Enabled!" << endl;
			break;
		}
		case 2: // IR keyboard OUTPUT
		{
			char state = 1; // grabs char
			while (true)
			{
				bool succsess = reader.readKey(state); // updates char with key reader
				cout << state << " " << endl; // prints key for debug
				arduino << state; // sends key to aruino
			}
			break;
		}
		case 3: // IR keyboard INPUT
		{
			cout << "IR keyboard Enabled!" << endl;
			break;
		}
		default:
		{
			cout << "This is impossible" << endl;
			break;
		}
	}

	return 0;
}