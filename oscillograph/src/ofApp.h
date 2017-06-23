#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
		
    void exit();
    
    
   void audioIn(ofSoundBuffer & input);
    ofSoundStream soundStream;

    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    


    //mutex audioMutex;
    ofSoundBuffer lastBuffer;
    double sampleRate;
    
    vector <float> recLeft;
    vector <float> recRight;
    
    int 	bufferCounter;
    int 	drawCounter;
    
//    float smoothedVol;
//    float scaledVol;
    
//    ofSoundStream soundStream;
    

    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<ofColor> line_color;
    ofParameter<float> shapeScale =.5;
    ofParameter<int> line_width = 1;
    
    bool gui_draw = 1;
    int app_size_w=100;
    int app_size_h=100;
    
    
};
