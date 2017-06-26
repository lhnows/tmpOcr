#ifndef _OCRUI_H_
#define _OCRUI_H_

#include<stdio.h>  
#include<string.h>  
#include <iostream>
#include "cwiiuse.h"
using namespace std;

#define TEXT_LENGTH 50 // rec TEXT_LENGTH text in one frame
#define TEXT_FRAME 10 // search text from near TEXT_FRAME frames
struct DistText{
	float dist;
	string text;
	void reset()
	{
		dist =0;
		text="";
	}
	void set(DistText &_dt)
	{
		dist = _dt.dist;
		text = _dt.text;
	}
};

struct DtArray{
	DistText dtdata[TEXT_LENGTH];
	int count;
	DtArray()
	{
		reset();
	}
	void reset()
	{
		count =0;
		for(int i=0;i<TEXT_LENGTH;i++)
		{
			dtdata[i].reset();
		}
	}
	void set(DtArray &_dta)
	{
		count = _dta.count;
		for(int i=0;i<TEXT_LENGTH;i++)
		{
			dtdata[i].set(_dta.dtdata[i]);
		}
	}
};

struct DtA_Array{
	DtArray dta_data[TEXT_FRAME];
	int isClear;
	DtA_Array()
	{
		reset();
	}

	void reset()
	{
		isClear = 1;
		for(int i=0;i<TEXT_FRAME;i++)
		{
			dta_data[i].reset();
		}
	}
	void add(DtArray &_dta)
	{
		isClear = 0;
		for(int i=0;i<TEXT_FRAME-1;i++)
		{
			dta_data[i].set(dta_data[i+1]);
		}
		dta_data[TEXT_FRAME-1].set(_dta);
	}
};


class OcrUI {
public:
	OcrUI();
	~OcrUI();

public:
	static OcrUI *getInstance();
	void setRumbleOrSound(int _isRumble);
	void recg1_attention();
	void recg2_1_attention();
	void recg2_0_attention();
	void process(DtArray &_dta);
	DtA_Array mdta_arr;
	
	int frameCount;
	int textFrameCount;
private:
	int isRumble;
	DtArray mReadDtArr;
	void readDtArr();
};


#endif // !_OCRUI_
