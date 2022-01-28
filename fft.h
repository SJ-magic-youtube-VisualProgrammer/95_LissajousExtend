/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <ofMain.h>
#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class FFT : public ofThread{
private:
	/****************************************
	****************************************/
	enum{
		THREAD_SLEEP_MS = 1,
	};
	enum ANALYZE_CH{
		ANALYZE_CH__STEREO,
		ANALYZE_CH__L,
		ANALYZE_CH__R,
	};
	
	/****************************************
	****************************************/
	int t_LastUpdate = 0;
	
	/********************
	********************/
	vector <float> vol_l;
	vector <float> vol_r;
	
	/********************
	********************/
	const double _PI = 3.14159265398979;
	int N;
	
	vector <double> sintbl;
	vector <int> bitrev;
	vector <double> fft_window;
	vector <double> tukey_window;
	vector <double> fft_x;
	vector <double> fft_y;
	vector <double> Gain;
	vector <double> Gain_smoothed;
	vector <double> Gain_smoothed_2;
	vector <double> phase_rad;
	vector <double> phase_deg;
	vector <double> phase_rad_madeFromGain;
	vector <double> artSin_x1;
	vector <double> artSin_y1;
	vector <double> artSin_x2;
	vector <double> artSin_y2;
	vector <double> artSin_x3;
	vector <double> artSin_y3;
	
	float acf; // Amplitude Correction Factor
	
	ANALYZE_CH AnalyzeCh = ANALYZE_CH__STEREO;
	
	/****************************************
	****************************************/
	bool Is_Factorial_of_2(double val);
	// int fft(double x[], double y[], int IsReverse = 0);
	int fft(vector <double>& x, vector <double>& y, int IsReverse = 0);
	void make_bitrev(void);
	void make_sintbl(void);
	void make_Hanning_window();
	void make_tukey_window();
	
	void copy_vol_to_analyzeArray();
	void multiply_HanningWindow(vector <double>& _x);
	void multiply_TukeyWindow(vector <double>& _x);
	void cal_Gain();
	void cal_Gain_smoothed(vector <double>& _Gain_smoothed, double k);
	void cal_Gain_LPF(vector <double>& _Gain_smoothed, double a);
	void cal_Phase();
	void cal_phase_MadeFromGain();
	void cal_artSin_xy(vector <double>& artSin_x, vector <double>& artSin_y, int Band_min, int Band_max, int sgn);
	void cal_SumOf_artSin();
	
public:
	/****************************************
	****************************************/
	FFT();
	~FFT();
	
	void setup();
	void update();
	
	void threadedFunction();
	
	void SetVol(ofSoundBuffer & buffer);
	void GetVol(ofSoundBuffer & buffer, bool b_EnableAudioOut);
	
	double get_GainSmoothed(int id) const;
	double get_GainSmoothed2(int id) const;
	double get_artSin(int id) const;
	int get_sizeof_GainArray() const;
	int get_sizeof_artSinArray() const;
	double get_phase_rad_madeFromGain(int id) const;
};



