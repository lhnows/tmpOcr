/*
 * webcam-demo.cpp
 *
 * A demo program of End-to-end Scene Text Detection and Recognition.
 *
 * Created on: Jul 31, 2014
 *     Author: Lluis Gomez i Bigorda <lgomez AT cvc.uab.es>
 */

#include "opencv2/text.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"

#include <iostream>

#include <librealsense/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<stdio.h>  
#include<pthread.h>  
#include<string.h>  
#include<sys/types.h>  
#include<unistd.h>  
using namespace std;
using namespace cv;
using namespace cv::text;
using namespace rs;

// realsense ocr recog code up:
// realsense ocr recog code up:
// realsense ocr recog code up:




#include <stdio.h>                      /* for printf */

#include "wiiuse.h"                     /* for wiimote_t, classic_ctrl_t, etc */

#ifndef WIIUSE_WIN32
#include <unistd.h>                     /* for usleep */
#endif

#define MAX_WIIMOTES				4


/**
 *	@brief Callback that handles an event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *
 *	This function is called automatically by the wiiuse library when an
 *	event occurs on the specified wiimote.
 */
void handle_event(struct wiimote_t* wm) {
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/* if a button is pressed, report it */
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A)) {
		printf("A pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		printf("DOWN pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT)) {
		printf("LEFT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT)) {
		printf("RIGHT pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) {
		printf("MINUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) {
		printf("PLUS pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME)) {
		printf("HOME pressed\n");
	}

	/*
	 *	Pressing minus will tell the wiimote we are no longer interested in movement.
	 *	This is useful because it saves battery power.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) {
		wiiuse_motion_sensing(wm, 0);
	}

	/*
	 *	Pressing plus will tell the wiimote we are interested in movement.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) {
		wiiuse_motion_sensing(wm, 1);
	}

	/*
	 *	Pressing B will toggle the rumble
	 *
	 *	if B is pressed but is not held, toggle the rumble
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		wiiuse_toggle_rumble(wm);
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		wiiuse_set_ir(wm, 1);
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		wiiuse_set_ir(wm, 0);
	}

	/*
	 * Motion+ support
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		if (WIIUSE_USING_EXP(wm)) {
			wiiuse_set_motion_plus(wm, 2);    // nunchuck pass-through
		}
		else {
			wiiuse_set_motion_plus(wm, 1);    // standalone
		}
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		wiiuse_set_motion_plus(wm, 0); // off
	}

	/* if the accelerometer is turned on then print angles */
	if (WIIUSE_USING_ACC(wm)) {
		printf("wiimote roll  = %f [%f]\n", wm->orient.roll, wm->orient.a_roll);
		printf("wiimote pitch = %f [%f]\n", wm->orient.pitch, wm->orient.a_pitch);
		printf("wiimote yaw   = %f\n", wm->orient.yaw);
	}

	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) {
		int i = 0;

		/* go through each of the 4 possible IR sources */
		for (; i < 4; ++i) {
			/* check if the source is visible */
			if (wm->ir.dot[i].visible) {
				printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
			}
		}

		printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
		printf("IR z distance: %f\n", wm->ir.z);
	}

	/* show events specific to supported expansions */
	if (wm->exp.type == EXP_NUNCHUK || wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
		/* nunchuk */
		struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;

		if (IS_PRESSED(nc, NUNCHUK_BUTTON_C)) {
			printf("Nunchuk: C pressed\n");
		}
		if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z)) {
			printf("Nunchuk: Z pressed\n");
		}

		printf("nunchuk roll  = %f\n", nc->orient.roll);
		printf("nunchuk pitch = %f\n", nc->orient.pitch);
		printf("nunchuk yaw   = %f\n", nc->orient.yaw);

		printf("nunchuk joystick angle:     %f\n", nc->js.ang);
		printf("nunchuk joystick magnitude: %f\n", nc->js.mag);

		printf("nunchuk joystick vals:      %f, %f\n", nc->js.x, nc->js.y);
		printf("nunchuk joystick calibration (min, center, max): x: %i, %i, %i  y: %i, %i, %i\n",
			nc->js.min.x,
			nc->js.center.x,
			nc->js.max.x,
			nc->js.min.y,
			nc->js.center.y,
			nc->js.max.y);
	}
	else if (wm->exp.type == EXP_CLASSIC) {
		/* classic controller */
		struct classic_ctrl_t* cc = (classic_ctrl_t*)&wm->exp.classic;

		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZL)) {
			printf("Classic: ZL pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_B)) {
			printf("Classic: B pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_Y)) {
			printf("Classic: Y pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_A)) {
			printf("Classic: A pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_X)) {
			printf("Classic: X pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZR)) {
			printf("Classic: ZR pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_LEFT)) {
			printf("Classic: LEFT pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_UP)) {
			printf("Classic: UP pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_RIGHT)) {
			printf("Classic: RIGHT pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_DOWN)) {
			printf("Classic: DOWN pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_L)) {
			printf("Classic: FULL L pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_MINUS)) {
			printf("Classic: MINUS pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_HOME)) {
			printf("Classic: HOME pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_PLUS)) {
			printf("Classic: PLUS pressed\n");
		}
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_R)) {
			printf("Classic: FULL R pressed\n");
		}

		printf("classic L button pressed:         %f\n", cc->l_shoulder);
		printf("classic R button pressed:         %f\n", cc->r_shoulder);
		printf("classic left joystick angle:      %f\n", cc->ljs.ang);
		printf("classic left joystick magnitude:  %f\n", cc->ljs.mag);
		printf("classic right joystick angle:     %f\n", cc->rjs.ang);
		printf("classic right joystick magnitude: %f\n", cc->rjs.mag);
	}
	else if (wm->exp.type == EXP_GUITAR_HERO_3) {
		/* guitar hero 3 guitar */
		struct guitar_hero_3_t* gh3 = (guitar_hero_3_t*)&wm->exp.gh3;

		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_UP)) {
			printf("Guitar: Strum Up pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_DOWN)) {
			printf("Guitar: Strum Down pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_YELLOW)) {
			printf("Guitar: Yellow pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_GREEN)) {
			printf("Guitar: Green pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_BLUE)) {
			printf("Guitar: Blue pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_RED)) {
			printf("Guitar: Red pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_ORANGE)) {
			printf("Guitar: Orange pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_PLUS)) {
			printf("Guitar: Plus pressed\n");
		}
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_MINUS)) {
			printf("Guitar: Minus pressed\n");
		}

		printf("Guitar whammy bar:          %f\n", gh3->whammy_bar);
		printf("Guitar joystick angle:      %f\n", gh3->js.ang);
		printf("Guitar joystick magnitude:  %f\n", gh3->js.mag);
	}
	else if (wm->exp.type == EXP_WII_BOARD) {
		/* wii balance board */
		struct wii_board_t* wb = (wii_board_t*)&wm->exp.wb;
		float total = wb->tl + wb->tr + wb->bl + wb->br;
		float x = ((wb->tr + wb->br) / total) * 2 - 1;
		float y = ((wb->tl + wb->tr) / total) * 2 - 1;
		printf("Weight: %f kg @ (%f, %f)\n", total, x, y);
		printf("Interpolated weight: TL:%f  TR:%f  BL:%f  BR:%f\n", wb->tl, wb->tr, wb->bl, wb->br);
		printf("Raw: TL:%d  TR:%d  BL:%d  BR:%d\n", wb->rtl, wb->rtr, wb->rbl, wb->rbr);
	}

	if (wm->exp.type == EXP_MOTION_PLUS ||
		wm->exp.type == EXP_MOTION_PLUS_NUNCHUK) {
		printf("Motion+ angular rates (deg/sec): pitch:%03.2f roll:%03.2f yaw:%03.2f\n",
			wm->exp.mp.angle_rate_gyro.pitch,
			wm->exp.mp.angle_rate_gyro.roll,
			wm->exp.mp.angle_rate_gyro.yaw);
	}
}

/**
 *	@brief Callback that handles a read event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *	@param data		Pointer to the filled data block.
 *	@param len		Length in bytes of the data block.
 *
 *	This function is called automatically by the wiiuse library when
 *	the wiimote has returned the full data requested by a previous
 *	call to wiiuse_read_data().
 *
 *	You can read data on the wiimote, such as Mii data, if
 *	you know the offset address and the length.
 *
 *	The \a data pointer was specified on the call to wiiuse_read_data().
 *	At the time of this function being called, it is not safe to deallocate
 *	this buffer.
 */
void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) {
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%x ", data[i]);
	}
	printf("\n\n");
}


/**
 *	@brief Callback that handles a controller status event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *	@param attachment		Is there an attachment? (1 for yes, 0 for no)
 *	@param speaker			Is the speaker enabled? (1 for yes, 0 for no)
 *	@param ir				Is the IR support enabled? (1 for yes, 0 for no)
 *	@param led				What LEDs are lit.
 *	@param battery_level	Battery level, between 0.0 (0%) and 1.0 (100%).
 *
 *	This occurs when either the controller status changed
 *	or the controller status was requested explicitly by
 *	wiiuse_status().
 *
 *	One reason the status can change is if the nunchuk was
 *	inserted or removed from the expansion port.
 */
void handle_ctrl_status(struct wiimote_t* wm) {
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}


/**
 *	@brief Callback that handles a disconnection event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *
 *	This can happen if the POWER button is pressed, or
 *	if the connection is interrupted.
 */
void handle_disconnect(wiimote* wm) {
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}


void test(struct wiimote_t* wm, byte* data, unsigned short len) {
	printf("test: %i [%x %x %x %x]\n", len, data[0], data[1], data[2], data[3]);
}

short any_wiimote_connected(wiimote** wm, int wiimotes) {
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}



//add by liuhao
wiimote** wiimotes;
int found, connected;



/**
 *	@brief main()
 *
 *	Connect to up to two wiimotes and print any events
 *	that occur on either device.
 */
int mainwii(int argc, char** argv) {
	wiimote** wiimotes;
	int found, connected;

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

	/*
	 *	Maybe I'm interested in the battery power of the 0th
	 *	wiimote.  This should be WIIMOTE_ID_1 but to be sure
	 *	you can get the wiimote associated with WIIMOTE_ID_1
	 *	using the wiiuse_get_by_id() function.
	 *
	 *	A status request will return other things too, like
	 *	if any expansions are plugged into the wiimote or
	 *	what LEDs are lit.
	 */
	 /* wiiuse_status(wiimotes[0]); */

	 /*
	  *	This is the main loop
	  *
	  *	wiiuse_poll() needs to be called with the wiimote array
	  *	and the number of wiimote structures in that array
	  *	(it doesn't matter if some of those wiimotes are not used
	  *	or are not connected).
	  *
	  *	This function will set the event flag for each wiimote
	  *	when the wiimote has things to report.
	  */
	while (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
		if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
			/*
			 *	This happens if something happened on any wiimote.
			 *	So go through each one and check if anything happened.
			 */
			int i = 0;
			for (; i < MAX_WIIMOTES; ++i) {
				switch (wiimotes[i]->event) {
				case WIIUSE_EVENT:
					/* a generic event occurred */
					handle_event(wiimotes[i]);
					break;

				case WIIUSE_STATUS:
					/* a status event occurred */
					handle_ctrl_status(wiimotes[i]);
					break;

				case WIIUSE_DISCONNECT:
				case WIIUSE_UNEXPECTED_DISCONNECT:
					/* the wiimote disconnected */
					handle_disconnect(wiimotes[i]);
					break;

				case WIIUSE_READ_DATA:
					/*
					 *	Data we requested to read was returned.
					 *	Take a look at wiimotes[i]->read_req
					 *	for the data.
					 */
					break;

				case WIIUSE_NUNCHUK_INSERTED:
					/*
					 *	a nunchuk was inserted
					 *	This is a good place to set any nunchuk specific
					 *	threshold values.  By default they are the same
					 *	as the wiimote.
					 */
					 /* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
					 /* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
					printf("Nunchuk inserted.\n");
					break;

				case WIIUSE_CLASSIC_CTRL_INSERTED:
					printf("Classic controller inserted.\n");
					break;

				case WIIUSE_WII_BOARD_CTRL_INSERTED:
					printf("Balance board controller inserted.\n");
					break;

				case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
					/* some expansion was inserted */
					handle_ctrl_status(wiimotes[i]);
					printf("Guitar Hero 3 controller inserted.\n");
					break;

				case WIIUSE_MOTION_PLUS_ACTIVATED:
					printf("Motion+ was activated\n");
					break;

				case WIIUSE_NUNCHUK_REMOVED:
				case WIIUSE_CLASSIC_CTRL_REMOVED:
				case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
				case WIIUSE_WII_BOARD_CTRL_REMOVED:
				case WIIUSE_MOTION_PLUS_REMOVED:
					/* some expansion was removed */
					handle_ctrl_status(wiimotes[i]);
					printf("An expansion was removed.\n");
					break;

				default:
					break;
				}
			}
		}
	}

	/*
	 *	Disconnect the wiimotes
	 */
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);

	return 0;
}



// realsense ocr recog code blow:
// realsense ocr recog code blow:
// realsense ocr recog code blow:
// realsense ocr recog code blow:
// realsense ocr recog code blow:

// Window size and frame rate
int const INPUT_WIDTH = 320;
int const INPUT_HEIGHT = 240;
int const FRAMERATE = 60;

// Named windows
char* const WINDOW_DEPTH = "Depth Image";
char* const WINDOW_RGB = "RGB Image";


context      _rs_ctx;
device&      _rs_camera = *_rs_ctx.get_device(0);
intrinsics   _depth_intrin;
intrinsics  _color_intrin;
bool         _loop = true;


// Initialize the application state. Upon success will return the static app_state vars address

bool initialize_streaming()
{
	bool success = false;
	if (_rs_ctx.get_device_count() > 0)
	{
		_rs_camera.enable_stream(rs::stream::color, INPUT_WIDTH, INPUT_HEIGHT, rs::format::rgb8, FRAMERATE);
		_rs_camera.enable_stream(rs::stream::depth, INPUT_WIDTH, INPUT_HEIGHT, rs::format::z16, FRAMERATE);
		_rs_camera.start();

		success = true;
	}
	return success;
}




/////////////////////////////////////////////////////////////////////////////
// If the left mouse button was clicked on either image, stop streaming and close windows.
/////////////////////////////////////////////////////////////////////////////
int mouseRead = 0;

static void onMouse(int event, int x, int y, int, void* window_name)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		mouseRead = 1;
		//Mat img(300,300,CV_8UC3);
		//imshow("img",img);
	}
}


/////////////////////////////////////////////////////////////////////////////
// Create the depth and RGB windows, set their mouse callbacks.
// Required if we want to create a window and have the ability to use it in
// different functions
/////////////////////////////////////////////////////////////////////////////
void setup_windows()
{
	cv::namedWindow(WINDOW_DEPTH, 0);
	cv::namedWindow(WINDOW_RGB, 0);

	cv::setMouseCallback(WINDOW_DEPTH, onMouse, WINDOW_DEPTH);
	cv::setMouseCallback(WINDOW_RGB, onMouse, WINDOW_RGB);
}


/////////////////////////////////////////////////////////////////////////////
// Called every frame gets the data from streams and displays them using OpenCV.
/////////////////////////////////////////////////////////////////////////////
bool display_next_frame()
{

	_depth_intrin = _rs_camera.get_stream_intrinsics(rs::stream::depth);
	_color_intrin = _rs_camera.get_stream_intrinsics(rs::stream::color);


	// Create depth image
	cv::Mat depth16(_depth_intrin.height,
		_depth_intrin.width,
		CV_16U,
		(uchar *)_rs_camera.get_frame_data(rs::stream::depth));

	// Create color image
	cv::Mat rgb(_color_intrin.height,
		_color_intrin.width,
		CV_8UC3,
		(uchar *)_rs_camera.get_frame_data(rs::stream::color));

	// < 800
	cv::Mat depth8u = depth16;
	depth8u.convertTo(depth8u, CV_8UC1, 255.0 / 1000);

	imshow(WINDOW_DEPTH, depth8u);
	cvWaitKey(1);

	cv::cvtColor(rgb, rgb, cv::COLOR_BGR2RGB);
	imshow(WINDOW_RGB, rgb);
	cvWaitKey(1);

	return true;
}




//ERStat extraction is done in parallel for different channels
class Parallel_extractCSER : public cv::ParallelLoopBody
{
private:
	vector<Mat> &channels;
	vector< vector<ERStat> > &regions;
	vector< Ptr<ERFilter> > er_filter1;
	vector< Ptr<ERFilter> > er_filter2;

public:
	Parallel_extractCSER(vector<Mat> &_channels, vector< vector<ERStat> > &_regions,
		vector<Ptr<ERFilter> >_er_filter1, vector<Ptr<ERFilter> >_er_filter2)
		: channels(_channels), regions(_regions), er_filter1(_er_filter1), er_filter2(_er_filter2) {}

	virtual void operator()(const cv::Range &r) const
	{
		for (int c = r.start; c < r.end; c++)
		{
			er_filter1[c]->run(channels[c], regions[c]);
			er_filter2[c]->run(channels[c], regions[c]);
		}
	}
	Parallel_extractCSER & operator=(const Parallel_extractCSER &a);
};

//OCR recognition is done in parallel for different detections
template <class T>
class Parallel_OCR : public cv::ParallelLoopBody
{
private:
	vector<Mat> &detections;
	vector<string> &outputs;
	vector< vector<Rect> > &boxes;
	vector< vector<string> > &words;
	vector< vector<float> > &confidences;
	vector< Ptr<T> > &ocrs;

public:
	Parallel_OCR(vector<Mat> &_detections, vector<string> &_outputs, vector< vector<Rect> > &_boxes,
		vector< vector<string> > &_words, vector< vector<float> > &_confidences,
		vector< Ptr<T> > &_ocrs)
		: detections(_detections), outputs(_outputs), boxes(_boxes), words(_words),
		confidences(_confidences), ocrs(_ocrs)
	{}

	virtual void operator()(const cv::Range &r) const
	{
		for (int c = r.start; c < r.end; c++)
		{
			ocrs[c%ocrs.size()]->run(detections[c], outputs[c], &boxes[c], &words[c], &confidences[c], OCR_LEVEL_WORD);
		}
	}
	Parallel_OCR & operator=(const Parallel_OCR &a);
};


//Discard wrongly recognised strings
bool   isRepetitive(const string& s);
//Draw ER's in an image via floodFill
void   er_draw(vector<Mat> &channels, vector<vector<ERStat> > &regions, vector<Vec2i> group, Mat& segmentation);


int depthArr[50];
string textStrSrc[50];
int textDetected = 0;
string textStr[20];
int conuse = 1;
Mat readimg(100, 100, CV_8UC3);
void *funcSound(void *arg)
{
	printf("new  thread:");
	while (1)
	{
		string strSpe[50];
		//string onstrspe="espeak\n 12134 \n 566567";
		if (0 == conuse)
		{

			//waitKey(0);
			for (int i = 0; i < textDetected; i++)
			{
				strSpe[i] = "espeak " + textStrSrc[i];
			}

			wiiuse_rumble(wiimotes[0], 1);
			wiiuse_rumble(wiimotes[1], 1);
			usleep(200000);
			wiiuse_rumble(wiimotes[0], 0);
			wiiuse_rumble(wiimotes[1], 0);

			system("espeak ding");
			imshow("read img", readimg);

			for (int j = 0; j < 10; j++)
			{
				if (any_wiimote_connected(wiimotes, MAX_WIIMOTES)) {
					if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {

						for (int i = 0; i < MAX_WIIMOTES; ++i) {
							switch (wiimotes[i]->event) {
							case WIIUSE_EVENT:
								/* a generic event occurred */
								handle_event(wiimotes[i]);
								break;

							case WIIUSE_STATUS:
								/* a status event occurred */
								handle_ctrl_status(wiimotes[i]);
								break;

							case WIIUSE_DISCONNECT:
							case WIIUSE_UNEXPECTED_DISCONNECT:
								/* the wiimote disconnected */
								handle_disconnect(wiimotes[i]);
								break;

							case WIIUSE_READ_DATA:
								/*
								*	Data we requested to read was returned.
								*	Take a look at wiimotes[i]->read_req
								*	for the data.
								*/
								break;

							case WIIUSE_NUNCHUK_INSERTED:
								/*
								 *	a nunchuk was inserted
								*	This is a good place to set any nunchuk specific
								*	threshold values.  By default they are the same
								*	as the wiimote.
								*/
								/* wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f); */
								/* wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100); */
								printf("Nunchuk inserted.\n");
								break;

							case WIIUSE_CLASSIC_CTRL_INSERTED:
								printf("Classic controller inserted.\n");
								break;

							case WIIUSE_WII_BOARD_CTRL_INSERTED:
								printf("Balance board controller inserted.\n");
								break;

							case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
								/* some expansion was inserted */
								handle_ctrl_status(wiimotes[i]);
								printf("Guitar Hero 3 controller inserted.\n");
								break;

							case WIIUSE_MOTION_PLUS_ACTIVATED:
								printf("Motion+ was activated\n");
								break;

							case WIIUSE_NUNCHUK_REMOVED:
							case WIIUSE_CLASSIC_CTRL_REMOVED:
							case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
							case WIIUSE_WII_BOARD_CTRL_REMOVED:
							case WIIUSE_MOTION_PLUS_REMOVED:
								/* some expansion was removed */
								handle_ctrl_status(wiimotes[i]);
								printf("An expansion was removed.\n");
								break;

							default:
								break;
							}
						}
					}
				}
				usleep(300000);
			}

			//usleep(3000000);
//int kk = waitKey(3000);//
			if (mouseRead == 1)
			{
				for (int i = 0; i < textDetected; i++)
				{
					system(strSpe[i].c_str());
					usleep(500000);
				}
				mouseRead = 0;
				continue;
			}





		}

		//string str = "espeak ";
		//str = str +"hello";
		//system(str.c_str()); 
		//usleep(1000000);
	}
	return ((void *)0);
}

pthread_t main_tid;
//Perform text detection and recognition from webcam
int main(int argc, char* argv[])
{


	////// start wii :
	////// start wii :
	////// start wii :
	////// start wii :


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





	//////start ocr





	//create sound thread
	/*
		int err;
			err = pthread_create(&main_tid, NULL, funcSound, NULL); //创建线程
			if(err != 0){
				printf("create thread error: /n");
				return 1;
			}
	*/
	cout << endl << argv[0] << endl << endl;
	cout << "A demo program of End-to-end Scene Text Detection and Recognition using webcam." << endl << endl;
	cout << "  Usage:  " << argv[0] << " [camera_index]" << endl << endl;
	cout << "  Press 'r' to switch between MSER/CSER regions." << endl;
	cout << "  Press 'g' to switch between Horizontal and Arbitrary oriented grouping." << endl;
	cout << "  Press 'o' to switch between OCRTesseract/OCRHMMDecoder recognition." << endl;
	cout << "  Press 's' to scale down frame size to 320x240." << endl;
	cout << "  Press 'ESC' to exit." << endl << endl;

	namedWindow(WINDOW_RGB, WINDOW_NORMAL);
	bool downsize = false;
	int  REGION_TYPE = 0;
	int  GROUPING_ALGORITHM = 0;
	int  RECOGNITION = 0;
	char *region_types_str[2] = { const_cast<char *>("ERStats"), const_cast<char *>("MSER") };
	char *grouping_algorithms_str[2] = { const_cast<char *>("exhaustive_search"), const_cast<char *>("multioriented") };
	char *recognitions_str[2] = { const_cast<char *>("Tesseract"), const_cast<char *>("NM_chain_features + KNN") };

	Mat frame, grey, orig_grey, out_img;
	vector<Mat> channels;
	vector<vector<ERStat> > regions(2); //two channels

	// Create ERFilter objects with the 1st and 2nd stage default classifiers
	// since er algorithm is not reentrant we need one filter for channel
	vector< Ptr<ERFilter> > er_filters1;
	vector< Ptr<ERFilter> > er_filters2;
	for (int i = 0; i < 2; i++)
	{
		Ptr<ERFilter> er_filter1 = createERFilterNM1(loadClassifierNM1("../module/trained_classifierNM1.xml"), 8, 0.00015f, 0.13f, 0.2f, true, 0.1f);
		Ptr<ERFilter> er_filter2 = createERFilterNM2(loadClassifierNM2("../module/trained_classifierNM2.xml"), 0.5);
		er_filters1.push_back(er_filter1);
		er_filters2.push_back(er_filter2);
	}

	//double t_r = getTickCount();

	//Initialize OCR engine (we initialize 10 instances in order to work several recognitions in parallel)
	cout << "Initializing OCR engines ..." << endl;
	int num_ocrs = 10;
	vector< Ptr<OCRTesseract> > ocrs;
	for (int o = 0; o < num_ocrs; o++)
	{
		ocrs.push_back(OCRTesseract::create());
	}

	Mat transition_p;
	string filename = "../module/OCRHMM_transitions_table.xml";
	FileStorage fs(filename, FileStorage::READ);
	fs["transition_probabilities"] >> transition_p;
	fs.release();
	Mat emission_p = Mat::eye(62, 62, CV_64FC1);
	string voc = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	vector< Ptr<OCRHMMDecoder> > decoders;
	for (int o = 0; o < num_ocrs; o++)
	{
		decoders.push_back(OCRHMMDecoder::create(loadOCRHMMClassifierNM("../module/OCRHMM_knn_model_data.xml.gz"),
			voc, transition_p, emission_p));
	}
	cout << " Done!" << endl;

	//cout << "TIME_OCR_INITIALIZATION_ALT = "<< ((double)getTickCount() - t_r)*1000/getTickFrequency() << endl;

/*  open uvc camera
	int cam_idx = 0;
	if (argc > 1)
		cam_idx = atoi(argv[1]);

	VideoCapture cap(cam_idx);
	if(!cap.isOpened())
	{
		cout << "ERROR: Cannot open default camera (0)." << endl;
		return -1;
	}
*/


	try
	{
		rs::log_to_console(rs::log_severity::warn);

		if (!initialize_streaming())
		{
			printf("Unable to locate a camera");
			//std::cout << "Unable to locate a camera" << std::endl;
			rs::log_to_console(rs::log_severity::fatal);
			return EXIT_FAILURE;
		}

		setup_windows();





		// Loop until someone left clicks on either of the images in either window.
		while (_loop)
		{
			if (_rs_camera.is_streaming())
				_rs_camera.wait_for_frames();

			_depth_intrin = _rs_camera.get_stream_intrinsics(rs::stream::depth);
			_color_intrin = _rs_camera.get_stream_intrinsics(rs::stream::color);

			//cv::Mat depth16( _depth_intrin.height,_depth_intrin.width,CV_16U,(uchar *)_rs_camera.get_frame_data( rs::stream::depth ) );

				   // Create depth image aligned
			cv::Mat depth16(_depth_intrin.height, _depth_intrin.width, CV_16U, (uchar *)_rs_camera.get_frame_data(rs::stream::depth_aligned_to_color));



			// Create color image
			cv::Mat rgb(_color_intrin.height,
				_color_intrin.width,
				CV_8UC3,
				(uchar *)_rs_camera.get_frame_data(rs::stream::color));

			// < 800
			cv::Mat depth8u = depth16;
			depth8u.convertTo(depth8u, CV_8UC1, 255.0 / 1000);

			imshow(WINDOW_DEPTH, depth8u);
			//cvWaitKey( 1 );

			cv::cvtColor(rgb, rgb, cv::COLOR_BGR2RGB);
			//imshow( WINDOW_RGB, rgb );
			//cvWaitKey( 1 );

			double t_all = (double)getTickCount();

			if (downsize)
				resize(rgb, frame, Size(320, 240));
			else
				resize(rgb, frame, Size(640, 480));


			//Text Detection

			cvtColor(frame, grey, COLOR_RGB2GRAY);
			grey.copyTo(orig_grey);
			// Extract channels to be processed individually
			channels.clear();
			channels.push_back(grey);
			channels.push_back(255 - grey);


			regions[0].clear();
			regions[1].clear();
			//double t_d = (double)getTickCount();

			switch (REGION_TYPE)
			{
			case 0:
			{
				parallel_for_(cv::Range(0, (int)channels.size()), Parallel_extractCSER(channels, regions, er_filters1, er_filters2));
				break;
			}
			case 1:
			{
				//Extract MSER
				vector<vector<Point> > contours;
				vector<Rect> bboxes;
				Ptr<MSER> mser = MSER::create(21, (int)(0.00002*grey.cols*grey.rows), (int)(0.05*grey.cols*grey.rows), 1, 0.7);
				mser->detectRegions(grey, contours, bboxes);

				//Convert the output of MSER to suitable input for the grouping/recognition algorithms
				if (contours.size() > 0)
					MSERsToERStats(grey, contours, regions);

				break;
			}
			case 2:
			{
				break;
			}
			}
			//cout << "TIME_REGION_DETECTION_ALT = " << ((double)getTickCount() - t_d)*1000/getTickFrequency() << endl;

			// Detect character groups
			//double t_g = getTickCount();
			vector< vector<Vec2i> > nm_region_groups;
			vector<Rect> nm_boxes;
			switch (GROUPING_ALGORITHM)
			{
			case 0:
			{
				erGrouping(frame, channels, regions, nm_region_groups, nm_boxes, ERGROUPING_ORIENTATION_HORIZ);
				break;
			}
			case 1:
			{
				erGrouping(frame, channels, regions, nm_region_groups, nm_boxes, ERGROUPING_ORIENTATION_ANY, "../module/trained_classifier_erGrouping.xml", 0.5);
				break;
			}
			}
			//cout << "TIME_GROUPING_ALT = " << ((double)getTickCount() - t_g)*1000/getTickFrequency() << endl;




			//Text Recognition (OCR)


			frame.copyTo(out_img);
			int scale = downsize ? 2 : 1;
			float scale_img = (float)((600.f / frame.rows) / scale);
			float scale_font = (float)(2 - scale_img) / 1.4f;
			vector<string> words_detection;
			float min_confidence1 = 0.f, min_confidence2 = 0.f;

			if (RECOGNITION == 0)
			{
				min_confidence1 = 51.f; min_confidence2 = 60.f;
			}

			vector<Mat> detections;

			//t_r = getTickCount();

			for (int i = 0; i < (int)nm_boxes.size(); i++)
			{
				rectangle(out_img, nm_boxes[i].tl(), nm_boxes[i].br(), Scalar(255, 255, 0), 3);


				Mat group_img = Mat::zeros(frame.rows + 2, frame.cols + 2, CV_8UC1);
				er_draw(channels, regions, nm_region_groups[i], group_img);
				group_img(nm_boxes[i]).copyTo(group_img);
				copyMakeBorder(group_img, group_img, 15, 15, 15, 15, BORDER_CONSTANT, Scalar(0));
				detections.push_back(group_img);
			}
			vector<string> outputs((int)detections.size());
			vector< vector<Rect> > boxes((int)detections.size());
			vector< vector<string> > words((int)detections.size());
			vector< vector<float> > confidences((int)detections.size());

			// parallel process detections in batches of ocrs.size() (== num_ocrs)
			for (int i = 0; i < (int)detections.size(); i = i + (int)num_ocrs)
			{
				Range r;
				if (i + (int)num_ocrs <= (int)detections.size())
					r = Range(i, i + (int)num_ocrs);
				else
					r = Range(i, (int)detections.size());

				switch (RECOGNITION)
				{
				case 0:
					parallel_for_(r, Parallel_OCR<OCRTesseract>(detections, outputs, boxes, words, confidences, ocrs));
					break;
				case 1:
					parallel_for_(r, Parallel_OCR<OCRHMMDecoder>(detections, outputs, boxes, words, confidences, decoders));
					break;
				}
			}

			conuse = 1;
			for (int i = 0; i < 50; i++)
			{
				depthArr[i] = 0;
				textStrSrc[i] = "";
			}

			int index = 0;
			for (int i = 0; i < (int)detections.size(); i++)
			{

				outputs[i].erase(remove(outputs[i].begin(), outputs[i].end(), '\n'), outputs[i].end());
				//cout << "OCR output = \"" << outputs[i] << "\" lenght = " << outputs[i].size() << endl;
				if (outputs[i].size() < 3)
					continue;

				for (int j = 0; j < (int)boxes[i].size(); j++)
				{
					boxes[i][j].x += nm_boxes[i].x - 15;
					boxes[i][j].y += nm_boxes[i].y - 15;

					//cout << "  word = " << words[j] << "\t confidence = " << confidences[j] << endl;
					if ((words[i][j].size() < 2) || (confidences[i][j] < min_confidence1) ||
						((words[i][j].size() == 2) && (words[i][j][0] == words[i][j][1])) ||
						((words[i][j].size() < 4) && (confidences[i][j] < min_confidence2)) ||
						isRepetitive(words[i][j]))
						continue;
					words_detection.push_back(words[i][j]);
					rectangle(out_img, boxes[i][j].tl(), boxes[i][j].br(), Scalar(255, 0, 0), 3);
					Size word_size = getTextSize(words[i][j], FONT_HERSHEY_SIMPLEX, (double)scale_font, (int)(3 * scale_font), NULL);
					rectangle(out_img, boxes[i][j].tl() - Point(3, word_size.height + 3), boxes[i][j].tl() + Point(word_size.width, 0), Scalar(255, 0, 255), -1);
					putText(out_img, words[i][j], boxes[i][j].tl() - Point(1, 1), FONT_HERSHEY_SIMPLEX, scale_font, Scalar(255, 255, 255), (int)(3 * scale_font));

					depthArr[index] = depth16.at<unsigned short>((boxes[i][j].tl().y + boxes[i][j].br().y) / 4, (boxes[i][j].tl().x + boxes[i][j].br().x) / 4);
					textStrSrc[index] = words[i][j];
					index++;
				}

			}

			for (int i = 0; i < index; i++)
			{
				for (int j = i + 1; j < index; j++)
				{
					if (depthArr[i] > depthArr[j])
					{
						int tmpdepth;
						tmpdepth = depthArr[i], depthArr[i] = depthArr[j], depthArr[j] = tmpdepth;

						string tmpstr;
						tmpstr = textStrSrc[i], textStrSrc[i] = textStrSrc[j], textStrSrc[j] = tmpstr;

					}

				}
			}





			textDetected = index;
			if (textDetected > 0)
				conuse = 0;
			//cout << "TIME_OCR_ALT = " << ((double)getTickCount() - t_r)*1000/getTickFrequency() << endl;







			t_all = ((double)getTickCount() - t_all) * 1000 / getTickFrequency();
			char buff[100];
			sprintf(buff, "%2.1f Fps. @ %dx%d", (float)(1000 / t_all), out_img.cols, out_img.rows);
			string fps_info = buff;
			rectangle(out_img, Point(out_img.rows - (160 / scale), out_img.rows - (70 / scale)), Point(out_img.cols, out_img.rows), Scalar(255, 255, 255), -1);
			putText(out_img, fps_info, Point(10, out_img.rows - (10 / scale)), FONT_HERSHEY_DUPLEX, scale_font, Scalar(255, 0, 0));
			putText(out_img, region_types_str[REGION_TYPE], Point(out_img.rows - (150 / scale), out_img.rows - (50 / scale)), FONT_HERSHEY_DUPLEX, scale_font, Scalar(255, 0, 0));
			putText(out_img, grouping_algorithms_str[GROUPING_ALGORITHM], Point(out_img.rows - (150 / scale), out_img.rows - (30 / scale)), FONT_HERSHEY_DUPLEX, scale_font, Scalar(255, 0, 0));
			putText(out_img, recognitions_str[RECOGNITION], Point(out_img.rows - (150 / scale), out_img.rows - (10 / scale)), FONT_HERSHEY_DUPLEX, scale_font, Scalar(255, 0, 0));

			out_img.copyTo(readimg);
			imshow(WINDOW_RGB, out_img);
			//imwrite("recognition_alt.jpg", out_img);
			int key = waitKey(10);
			if (key == 27) //wait for key
			{
				cout << "esc key pressed" << endl;
				break;
			}
			else
			{
				switch (key)
				{
				case 103: //g
					GROUPING_ALGORITHM = (GROUPING_ALGORITHM + 1) % 2;
					cout << "Grouping switched to " << grouping_algorithms_str[GROUPING_ALGORITHM] << endl;
					break;
				case 111: //o
					RECOGNITION = (RECOGNITION + 1) % 2;
					cout << "OCR switched to " << recognitions_str[RECOGNITION] << endl;
					break;
				case 114: //r
					REGION_TYPE = (REGION_TYPE + 1) % 2;
					cout << "Regions switched to " << region_types_str[REGION_TYPE] << endl;
					break;
				case 115: //s
					downsize = !downsize;
					break;
				default:
					break;

				}
			}


			string strSpe[50];
			string strDist[50];
			if (0 == conuse)
			{

				//waitKey(0);
				for (int i = 0; i < textDetected; i++)
				{
					strSpe[i] = "espeak " + textStrSrc[i];
				}
				system("espeak attention");
				//imshow("read img",readimg);
				for (int i = 0; i < 10; i++)
				{
					//usleep(300000);
					waitKey(100);
					if (mouseRead == 1)
						break;
				}
				//usleep(3000000);
		//int kk = waitKey(3000);//
				if (mouseRead == 1)
				{
					for (int i = 0; i < textDetected; i++)
					{
						char speakdist[30];
						sprintf(speakdist, "espeak %.1f", (float)depthArr[i] / 1000);
						system(speakdist);
						system("espeak meters");
						system(strSpe[i].c_str());
						waitKey(300);
						//usleep(500000);
					}

				}
				mouseRead = 0;

			}

		}


		_rs_camera.stop();
		cv::destroyAllWindows();


		return EXIT_SUCCESS;

	}
	catch (const rs::error & e)
	{
		// std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (const std::exception & e)
	{
		// std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}

bool isRepetitive(const string& s)
{
	int count = 0;
	int count2 = 0;
	int count3 = 0;
	int first = (int)s[0];
	int last = (int)s[(int)s.size() - 1];
	for (int i = 0; i < (int)s.size(); i++)
	{
		if ((s[i] == 'i') ||
			(s[i] == 'l') ||
			(s[i] == 'I'))
			count++;
		if ((int)s[i] == first)
			count2++;
		if ((int)s[i] == last)
			count3++;
	}
	if ((count > ((int)s.size() + 1) / 2) || (count2 == (int)s.size()) || (count3 > ((int)s.size() * 2) / 3))
	{
		return true;
	}


	return false;
}


void er_draw(vector<Mat> &channels, vector<vector<ERStat> > &regions, vector<Vec2i> group, Mat& segmentation)
{
	for (int r = 0; r < (int)group.size(); r++)
	{
		ERStat er = regions[group[r][0]][group[r][1]];
		if (er.parent != NULL) // deprecate the root region
		{
			int newMaskVal = 255;
			int flags = 4 + (newMaskVal << 8) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;
			floodFill(channels[group[r][0]], segmentation, Point(er.pixel%channels[group[r][0]].cols, er.pixel / channels[group[r][0]].cols),
				Scalar(255), 0, Scalar(er.level), Scalar(0), flags);
		}
	}
}
