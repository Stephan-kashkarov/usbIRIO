#include <stdio.h>
#include <iostream>
#include <string.h>
#include <usb.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

struct usb_device *getUSBDevice(struct usb_bus *bus_buffer)
{
	while (bus_buffer != NULL)
	{
		struct usb_device *dev = bus_buffer->devices;
		while (dev != NULL)
		{
			cout << "Checking USB device." << endl
				 << "Vendor ID:" << hex << dev->descriptor.idVendor << " Product ID: " << hex << dev->descriptor.idProduct << endl;
			if ((dev->descriptor.idVendor == 0x16d0) && (dev->descriptor.idProduct == 0x753))
			{
				cout << "USB device succsessfully connected:" << dev << endl;
				return dev;
			}
			dev = dev->next;
		}
		bus_buffer = bus_buffer->next;
	}
}

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

char getKeyboardInput() {
	struct input_event ev;

	while (1)
	{
		read((int)"/dev/input/event0", &ev, sizeof(struct input_event));

		if (ev.type == 1)
			printf("key %i state %i\n", ev.code, ev.value);
	}
}

int main()
{
	// Initialize the USB library
	usb_init();

	// Enumerate the USB device tree
	usb_find_busses();
	usb_find_devices();
	char input;
	struct usb_bus *bus_buffer = usb_get_busses();
	struct usb_device *dev = getUSBDevice(bus_buffer);
	struct usb_dev_handle *handle = usb_open(dev);
	struct usb_interface_descriptor *interface = &(dev->config->interface[0].altsetting[0]);
	int operation = getOperation();
	int sendResult = usb_control_msg(handle, (0x01 << 5), 0x09, 0, operation, 0, 0, 1000);

	if (sendResult < 0)
	{
		usb_release_interface(handle, interface->bInterfaceNumber);
		usb_close(handle);
		cout << "Error while sending. error: " << sendResult << endl;
		return -1;
	}

	int recieveResult = usb_control_msg(handle, (0x01 << 5) | 0x80, 0x01, 0, 0, &input, 1, 1000);

	if (recieveResult < 0)
	{
		usb_release_interface(handle, interface->bInterfaceNumber);
		usb_close(handle);
		cout << "Error in recieved result. error: " << recieveResult << endl;
		return -1;
	}

	switch (operation)
	{
	case 0: // IR mouse OUTPUT

		char state = 1;
		while (state != 0)
		{
			state = getKeyboardInput();
			int sendResult = usb_control_msg(handle, (0x01 << 5), 0x09, 0, state, 0, 0, 1000);
		}
		break;


	case 1: // IR mouse INPUT

		cout << "IR Mouse Enabled!" << endl;
		break;


	case 2: // IR keyboard OUTPUT

		char state = 1;
		while (state != 0)
		{
			state = mousePos();
			int sendResult = usb_control_msg(handle, (0x01 << 5), 0x09, 0, state, 0, 0, 1000);
		}
		break;


	case 3: // IR keyboard INPUT

		cout << "IR keyboard Enabled!" << endl;
		break;
	default:
		cout << "This is impossible" << endl;
		break;
	}
	usb_release_interface(handle, interface->bInterfaceNumber);
	usb_close(handle);

	return 0;
}