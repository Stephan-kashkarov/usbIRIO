#include <stdio.h>
#include <iostream>
#include <fstream>
#include "keyreader.h"

using namespace std;


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
	char a;
	cout << "When the Green LED Starts flashing press enter to start!" << endl;
	cin >> &a;
	ofstream arduino;
	arduino.open("/dev/ttyUSB0");
	KeyReader reader;
	char input;
	int operation = getOperation();
	arduino << operation;

	switch (operation)
	{
	case 0: // IR mouse OUTPUT
		cout << "feature not yet avalible" << endl;
		
		break;


	case 1: // IR mouse INPUT
		cout << "feature not yet avalible" << endl;
		// cout << "IR Mouse Enabled!" << endl;
		break;


	case 2: // IR keyboard OUTPUT

		char state = 1;
		while (true)
		{
			bool succsess = reader.readKey(state);
			cout << state << " " << endl;
			arduino << state;
		}
		break;


	case 3: // IR keyboard INPUT
		cout << "IR keyboard Enabled!" << endl;
		break;


	default:
		cout << "This is impossible" << endl;
		break;
	}

	return 0;
}