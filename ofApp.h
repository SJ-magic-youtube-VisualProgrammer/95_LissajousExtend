/************************************************************
■参考
	of_v0.11.2_osx_release/examples/sound/audioInputExample
	of_v0.11.2_osx_release/examples/sound/audioOutputExample


■Audio I/F
input:cable
	モノラル。
	
	walkmanからinputする時は、LR(白赤)に分けて入れる。
	ちなみに、「標準ステレオ」をinputしたつもりで動作させると、
	「低音スカスカなんだけど」って感じになった。
	
input:Level
	walkmanから入れる場合、cable上のLevelはLine Level。
	input感度は、minimum〜設定していく。
	
■primitive study
	■DTM初心者のためのオーディオインターフェイス選び 2016
		http://www.dtmstation.com/archives/51971048.html
	
	■オーディオ信号レベル
		http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1413957214
			マイク 1.6mV
			エレキギター 200mV
			ライン 1,230mV（1,000mV）
			ヘッドフォン、スピーカー 2,400-2.830mV
			
	■４つのオーディオ信号レベル【音楽・動画などの制作・配信に必須】
		https://masafumiiwasaki.com/blog/audio-signal-level-4types/
		
	■バランスとアンバランス【オーディオ機器のケーブル接続】
		https://masafumiiwasaki.com/blog/balance-unbalance/#toc6
	

■【今さら聞けない用語シリーズ】
	■初心者向け【今さら聞けない用語シリーズ】初めてのオーディオ・インターフェース選び
		http://info.shimamura.co.jp/digital/knowledge/2014/06/21591
		
	■【今さら聞けない用語シリーズ】3分でわかる！インピーダンスって何でしょう？ ロー出しハイ受け？
		http://info.shimamura.co.jp/digital/knowledge/2014/01/16805
n		
	■【今さら聞けない用語シリーズ】3分でわかる！オーディオ・ケーブルの種類とバランス・アンバランスの違い
		http://info.shimamura.co.jp/digital/knowledge/2014/01/16501
		
	■【今さら聞けない用語シリーズ】音と周波数
		http://info.shimamura.co.jp/digital/knowledge/2014/03/19260
		
	■【今さら聞けない用語シリーズ】3分でわかる！コンデンサーマイクとダイナミックマイクの違い おすすめマイク
		http://info.shimamura.co.jp/digital/knowledge/2014/04/23017
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <ofMain.h>

#include "sj_common.h"
#include "fft.h"
#include "DrawFFT.h"
#include "DrawLissajous.h"


/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		MAIN_WINDOW_W = 1920,
		MAIN_WINDOW_H = 1080,
	};
	
	/****************************************
	****************************************/
	FFT fft_thread;
	
	ofSoundStream *soundStream;
	bool b_EnableAudioOut;
	int soundStream_Input_DeviceId;
	int soundStream_Output_DeviceId;
	
	ofFbo fbo;
	
	DRAW_FFT DrawFFT;
	DRAW_LISSAJOU DrawLissajous;
	
	/****************************************
	****************************************/
	void Sound__Start();
	void Sound__Stop();
	void Sound__Reset();
	void setup_Gui();
	
public:
	/****************************************
	****************************************/
	
	/****************************************
	****************************************/
	ofApp(int _soundStream_Input_DeviceId, int _soundStream_Output_DeviceId);
	~ofApp();
	
	void setup_sound();
	void setup();
	void update();
	void draw();
	
	void exit();
	
	void audioIn(ofSoundBuffer & buffer);
	void audioOut(ofSoundBuffer & buffer);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
