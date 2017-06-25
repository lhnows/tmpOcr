#include "ocrui.h"




OcrUI *modOcrUI =NULL;
OcrUI::OcrUI()
{
    isRumble =1;
    frameCount=0;
}

OcrUI::~OcrUI()
{

}

OcrUI * OcrUI::getInstance()
{
	if(modOcrUI ==NULL)
	{
		modOcrUI = new OcrUI();
		//modOcrUI->init();
	}
	return modOcrUI;
}

void OcrUI::setRumbleOrSound(int _isRumble)
{
    isRumble = _isRumble;
}

void OcrUI::recg_attention()
{
	if (1==isRumble)
		Cwiiuse::getInstance()->setRumble(200);
	else
		system("espeak attention");
}

void OcrUI::process(DtArray &_dta)
{
    if(0==_dta.count && mdta_arr.isClear==1) return;
    if(mdta_arr.isClear==1)
    {
        recg_attention();
        char key = Cwiiuse::getInstance()->getAction1(2000);
        if('A'!=key) return;
    }
    if(TEXT_FRAME == frameCount)
    {
        Cwiiuse::getInstance()->setRumble(1000);
        char key = Cwiiuse::getInstance()->getAction1(2000);
        if('A'==key)
        {
			readDtArr();
        }
        mdta_arr.reset();
        frameCount=0;
        return;
    }
    mdta_arr.add(_dta);
    frameCount++;

    //----
    if(0!=_dta.count)
    {
        mReadDtArr.set(_dta);
    }

}

void OcrUI::readDtArr()
{
    for (int i = 0; i < mReadDtArr.count; i++)
    {
        char speakdist[30];
        sprintf(speakdist, "espeak %.1f",mReadDtArr.dtdata[i].dist / 1000);
        string strSpe = "espeak " + mReadDtArr.dtdata[i].text;
		printf("%s\n",speakdist);
		printf("%s\n",strSpe.c_str());
        system(speakdist);
        system("espeak meters");
        system(strSpe.c_str());
        //waitKey(300);
        usleep(300000);
    }
}
