#include "cwiiuse.h"



void *wiithreadfunc(void *arg)
{
	Cwiiuse::getInstance();

}

Cwiiuse::Cwiiuse()
{

}

Cwiiuse::~Cwiiuse()
{

}

Cwiiuse * Cwiiuse::getInstance()
{
	return modCwiiuse;
}

int Cwiiuse::init()
{
	/*
	*	Initialize an array of wiimote objects.
	*
	*	The parameter is the number of wiimotes I want to create.
	*/
	wiimotes = wiiuse_init(MAX_WIIMOTES);

	/*
	*	Find wiimote devices
	*
	*	Now we need to find some wiimotes.
	*	Give the function the wiimote array we created, and tell it there
	*	are MAX_WIIMOTES wiimotes we are interested in.
	*
	*	Set the timeout to be 5 seconds.
	*
	*	This will return the number of actual wiimotes that are in discovery mode.
	*/
	found = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);
	if (!found) {
		printf("No wiimotes found.\n");
		return 0;
	}

	/*
	*	Connect to the wiimotes
	*
	*	Now that we found some wiimotes, connect to them.
	*	Give the function the wiimote array and the number
	*	of wiimote devices we found.
	*
	*	This will return the number of established connections to the found wiimotes.
	*/
	connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
	if (connected) {
		printf("Connected to %i wiimotes (of %i found).\n", connected, found);
	}
	else {
		printf("Failed to connect to any wiimote.\n");
		return 0;
	}

	/*
	*	Now set the LEDs and rumble for a second so it's easy
	*	to tell which wiimotes are connected (just like the wii does).
	*/
	wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
	wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);
	wiiuse_set_leds(wiimotes[2], WIIMOTE_LED_3);
	wiiuse_set_leds(wiimotes[3], WIIMOTE_LED_4);
	wiiuse_rumble(wiimotes[0], 1);
	wiiuse_rumble(wiimotes[1], 1);

#ifndef WIIUSE_WIN32
	usleep(200000);
#else
	Sleep(200);
#endif

	wiiuse_rumble(wiimotes[0], 0);
	wiiuse_rumble(wiimotes[1], 0);

	printf("\nControls:\n");
	printf("\tB toggles rumble.\n");
	printf("\t+ to start Wiimote accelerometer reporting, - to stop\n");
	printf("\tUP to start IR camera (sensor bar mode), DOWN to stop.\n");
	printf("\t1 to start Motion+ reporting, 2 to stop.\n");
	printf("\n\n");
}

int Cwiiuse::start()
{

	int err;
	err = pthread_create(&wii_thread, NULL, wiithreadfunc, NULL); //创建线程
	if (err!=0)
	{
		printf("create wii_thread error\n ");
		return -1;
	}
	printf("wii_thread created!");
	return 0;
}