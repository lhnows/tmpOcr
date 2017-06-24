#ifndef _CWIIUSE_H_
#define _CWIIUSE_H_



#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#define MAX_WIIMOTES				4
pthread_t wii_thread;

extern void (*wii_onPressEvent)(char key);
//extern void wii_onPressCall(char key);

Cwiiuse *modCwiiuse;

class Cwiiuse {
public:
	Cwiiuse();
	~Cwiiuse();

public:
	wiimote** wiimotes;
	int found, connected;

	Cwiiuse *getInstance();
	int init();
	int start();

	void getAction();
	void setAction();
	void setRumble(int msec);
private:





};


#endif