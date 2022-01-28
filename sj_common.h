/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <stdio.h>

#include <ofMain.h>
#include <ofxGui.h>

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
enum{
	BUF_SIZE_S = 500,
	BUF_SIZE_M = 1000,
	BUF_SIZE_L = 6000,
	BUF_SIZE_LL = 100000,
	UDP_BUF_SIZE = 100000,
};

enum{
	AUDIO_BUF_SIZE = 512,
	
	AUDIO_OUT_CHS = 2,
	AUDIO_IN_CHS = 2,
	AUDIO_BUFFERS = 2,			// 使われてないっぽい
	AUDIO_SAMPLERATE = 44100,
};

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class GUI_GLOBAL{
private:
	/****************************************
	****************************************/
	
public:
	/****************************************
	****************************************/
	void setup(string GuiName, string FileName = "gui.xml", float x = 10, float y = 10);
	
	ofxGuiGroup Group_Audio;
		ofxToggle b_Audio_Start;
		ofxToggle b_Audio_Stop;
		ofxToggle b_Audio_Reset;
		
	ofxGuiGroup Group_FFT;
		ofxFloatSlider Gain;
		ofxFloatSlider k_smooth;
		ofxFloatSlider dt_smooth_2;
		ofxToggle b_Window;
		
	ofxGuiGroup Group_ArtSin;
		ofxFloatSlider ArtSin_Band_min;
		ofxFloatSlider ArtSin_Band_max;
		ofxFloatSlider ArtSin_PhaseMap_k;
		ofxToggle b_ArtSin_abs;
		ofxToggle b_Window_artSin;
		ofxFloatSlider ArtSin_window_alpha;
		ofxColorSlider col_ArtSin;
		ofxFloatSlider ArtSin_BarHeight;
		ofxFloatSlider ArtSin_thresh;
		ofxFloatSlider ArtSin_MaxAlpha;
		ofxToggle b_ArtSin_Button_Adjust_thresh;
		ofxColorSlider col_ArtSin_thresh;
	
	ofxGuiGroup Group_Lissajous;
		ofxVec2Slider Li_GraphSize;
		
		ofxFloatSlider Li_GainId_0;
		ofxFloatSlider Li_Gain_ofs;
		ofxFloatSlider Lissajous_Scale;
		
		ofxFloatSlider Lissajous_PointSize;
		ofxFloatSlider Lissajous_LineWidth;
		ofxFloatSlider Lissajous_theta_rot_speed;
		ofxColorSlider col_Lissajous;
		ofxToggle b_Lissajous_Line;
		ofxToggle b_EnableDistortion;
		ofxFloatSlider Lissajous_a_b__alpha;
		ofxFloatSlider Lissajous_theta_b__alpha;
		
	
	ofxPanel gui;
	
	bool b_Disp = false;
};

/************************************************************
************************************************************/
double LPF(double LastVal, double CurrentVal, double Alpha_dt, double dt);
double LPF(double LastVal, double CurrentVal, double Alpha);
double sj_max(double a, double b);

bool checkIf_ContentsExist(char* ret, char* buf);
void Align_StringOfData(string& s);
void print_separatoin();
void ClearFbo(ofFbo& fbo);

void Read_Lissajous_id_info_from_gui(int id[], int size);
float toRad(float val);
float toDeg(float val);

/************************************************************
************************************************************/
extern GUI_GLOBAL* Gui_Global;

extern FILE* fp_Log;

extern int GPIO_0;
extern int GPIO_1;


/************************************************************
************************************************************/

