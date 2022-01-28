/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <ofMain.h>
#include "fft.h"
#include <ofxVboSet.h>
#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class LISSAJOUS{
private:
	float A, B;
	
	float a = 1;
	float b = 1;
	
	float theta_b = 0;
	
	float theta_start = 0;
	
	void init(){
		// theta_start = ofRandom(2 * 3.14);
		theta_start = toRad(90);
	}
	
public:
	LISSAJOUS() : A(500), B(500) { init(); }
	
	void set(float _A, float _a, float _B, float _b, float _theta_b){
		A = _A;
		B = _B;
		
		a = Gui_Global->Lissajous_a_b__alpha * _a + (1 - Gui_Global->Lissajous_a_b__alpha)  * a;
		b = Gui_Global->Lissajous_a_b__alpha * _b + (1 - Gui_Global->Lissajous_a_b__alpha)  * b;
		
		theta_b = Gui_Global->Lissajous_theta_b__alpha * _theta_b + (1 - Gui_Global->Lissajous_theta_b__alpha) * theta_b;
	}
	
	float get(float& x, float& y, float t){
		float dt = (float)ofGetElapsedTimeMillis() / 1000.0;
		
		float theta_rot = toRad(Gui_Global->Lissajous_theta_rot_speed) * dt;
		
		if(Gui_Global->b_EnableDistortion){
			x = A * cos(a * t + theta_start + theta_rot);
			y = B * sin(b * t + theta_start + theta_rot + theta_b);
		}else{
			x = A * cos(a * t + theta_start + theta_rot);
			y = B * sin(b * t + theta_start + theta_rot);
		}
	}
};

/**************************************************
**************************************************/
class DRAW_LISSAJOU{
private:
	/****************************************
	****************************************/
	enum{
		LISSAJOU_WINDOW_W = 180,
		LISSAJOU_WINDOW_H = 180,
		
		NUM_POINTS_LISSAJOUS = 640,
	};
	
	ofx__VBO_SET VboSet;
	
	const float t_step_Lissajous = 0.01;
	
	/********************
	********************/
	LISSAJOUS Lissajous;
	
	/****************************************
	****************************************/
	void Refresh_vboVerts(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale);
	void Refresh_vboColor();
	
public:
	DRAW_LISSAJOU();
	~DRAW_LISSAJOU();
	
	void setup(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale);
	void update(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale);
	void draw(ofFbo& fbo);
};

