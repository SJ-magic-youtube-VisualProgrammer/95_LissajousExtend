/************************************************************
************************************************************/
#include "DrawLissajous.h"

/************************************************************
************************************************************/

/******************************
******************************/
DRAW_LISSAJOU::DRAW_LISSAJOU()
{
}

/******************************
******************************/
DRAW_LISSAJOU::~DRAW_LISSAJOU()
{
}

/******************************
******************************/
void DRAW_LISSAJOU::setup(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale)
{
	/********************
	********************/
	print_separatoin();
	printf("> setup : Draw Lissajou\n");
	fflush(stdout);
	
	/********************
	********************/
	VboSet.setup(NUM_POINTS_LISSAJOUS);
	Refresh_vboVerts(fft, GraphSize, id_0, id_1, id_2, id_3, scale);
	Refresh_vboColor();
	VboSet.update_vertex_color();
}

/******************************
1--2
|  |
0--3
******************************/
void DRAW_LISSAJOU::Refresh_vboVerts(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale)
{
	/********************
	********************/
	float a = fft.get_GainSmoothed2( id_1 ) * scale;
	float b = fft.get_GainSmoothed2( id_2 ) * scale;
	
	float Gain_0 = fft.get_GainSmoothed2( id_0 );
	float Gain_3 = fft.get_GainSmoothed2( id_3 );
	
	float theta;
	const float thresh = 1e-4;
	if( (Gain_0 < thresh) && (Gain_3 < thresh) )	theta = toRad(45);
	else											theta = atan2(Gain_0, Gain_3);
	
	float theta_b = toRad( ofMap(theta, 0, 3.1415/2, 90, -90, true) );
	
	/********************
	********************/
	Lissajous.set(GraphSize.x/2, a, GraphSize.y/2, b, theta_b);
	
	/********************
	********************/
	float t = 0;
	for(int i = 0; i < NUM_POINTS_LISSAJOUS; i++){
		float x, y;
		
		Lissajous.get(x, y, t);
		
		VboSet.set_vboVerts( i, x, y);
		
		t += t_step_Lissajous;
	}
}

/******************************
******************************/
void DRAW_LISSAJOU::Refresh_vboColor()
{
	VboSet.set_singleColor(Gui_Global->col_Lissajous);
}

/******************************
******************************/
void DRAW_LISSAJOU::update(const FFT& fft, glm::vec2 GraphSize, int id_0, int id_1, int id_2, int id_3, float scale)
{
	/********************
	********************/
	Refresh_vboVerts(fft, GraphSize, id_0, id_1, id_2, id_3, scale);
	VboSet.update_vertex();
	
	Refresh_vboColor();
	VboSet.update_color();
}

/******************************
******************************/
void DRAW_LISSAJOU::draw(ofFbo& fbo)
{
	fbo.begin();
	ofPushMatrix();
		/********************
		********************/
		ofTranslate(fbo.getWidth()/2, fbo.getHeight()/2);
		ofScale(1, -1, 1);
		
		/********************
		********************/
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		ofEnableSmoothing();
		
		/********************
		********************/
		ofSetColor(255);
		
		if(Gui_Global->b_Lissajous_Line){
			glLineWidth(Gui_Global->Lissajous_LineWidth);
			VboSet.draw(GL_LINE_STRIP);
		}else{
			glPointSize(Gui_Global->Lissajous_PointSize);
			VboSet.draw(GL_POINTS);
		}
	ofPopMatrix();
	fbo.end();
}
