#ifndef _CWIIUSE_H_
#define _CWIIUSE_H_



#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

#ifndef WIIUSE_WIN32
#include <unistd.h>                     /* for usleep */
#endif
#define MAX_WIIMOTES				4
 

//extern void (*wii_onPressEvent)(char key);
//extern void wii_onPressCall(char key);



class Cwiiuse {
public:
	Cwiiuse();
	~Cwiiuse();

public:
	wiimote** wiimotes;
	int found, connected;

	static Cwiiuse *getInstance();
	int init();
	int start();
	char action;
	char action1;
	char action2;
	char getAction();
	char getAction1();
	char getAction2();
	void setAction(char key);
	char getAction(int msec);
	char getAction1(int msec);
	char getAction2(int msec);
	void setRumble(int msec);
private:


};




#endif
