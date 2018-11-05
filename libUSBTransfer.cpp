#include <stdio.h>
#include <iostream>
#include <vector>
#include <libusb-1.0/libusb.h>

using namespace std;

int initalizeLibUsb(){
	int r = libusb_init(NULL);
	if (r != 0) {
		return -1;
	}
}

libusb_device* selectDevice(){
	int counter = 0;
	libusb_device **listOfDevices;
	libusb_device **newListOfDevices;
	libusb_device* target;
	cout << "libusb initalized" << endl;
	ssize_t numOfDevices = libusb_get_device_list(NULL, &listOfDevices);
	cout << "Plug in USB device" << endl;
	while (counter < 10000000){
		ssize_t newNumOfDevices = libusb_get_device_list(NULL, &newListOfDevices);
		if (newNumOfDevices != numOfDevices) {
			for (size_t i = 0; i < numOfDevices; ++i)
			{
				libusb_device *device = listOfDevices[i];
				for(size_t j = 0; j < newNumOfDevices; ++j)
				{
					if (device == newListOfDevices[j]){
						return device;
					}
				}
				
				
				cout << device << endl;
			}
		}
		++counter;
	}
	cout << "No device detected" << endl;
	return NULL;
}

int getOperation(){
	int action;
	bool valid = false;
	while (!(valid)) {
		cout << "USB device succsessfully connected!" << endl;
		cout << "Please Select Action:" << endl;
		cout << "	0. IR mouse OUTPUT" << endl;
		cout << "	1. IR mouse INPUT" << endl;
		cout << "	2. IR keyboard OUTPUT" << endl;
		cout << "	3. IR keyboard INPUT" << endl;
		cin >> action;
		
		for(size_t i = 0; i < 4; i++)
		{
			if (action == i){
				valid = true;
			}
		}
		if (valid == false){
			cout << "Enter a valid input";
		}
		
	}
	return action;

}

int main(){
	int usb = initalizeLibUsb();
	if (usb == -1) {
		cout << "libusb failed to initalize" << endl;
		return -1;
	}
	libusb_device *device = selectDevice();
	cout << "Device Located: " << device << endl;
	libusb_device_handle *handle;
	libusb_open(device, &handle);
	int operation = getOperation();
	
	switch (operation)
	{
		case 0:
			/* code */
			break;
		case 1:
			/* code */
			break;
		case 2:
			/* code */
			break;
		case 3:
			/* code */
			break;
		default:
			break;
	}

	libusb_close(handle);
	libusb_exit(NULL);
	return 0;
}