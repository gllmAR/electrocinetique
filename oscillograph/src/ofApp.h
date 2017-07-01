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
    double sampleRate;
    
    ofEasyCam cam;
    ofParameter<bool> cam_set_ortho = 0;
    ofParameter<bool> cam_set_reset = 0;

    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    vector <float> recLeft;
    vector <float> recRight;
    
    int 	bufferCounter;
    int 	drawCounter;
    

    
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<ofColor> line_color;
    ofParameter<float> shapeScale =.5;
    ofParameter<int> line_width = 1;
    ofParameter<bool> set_fullscreen = 0;
    bool set_fullscreen_old = 0;
    
    bool gui_draw = 0;
    int app_size_w=100;
    int app_size_h=100;
    
    ofVboMesh vbo_mesh;
    
    double timestamp;
    double vertex_remover;
    
    
};
