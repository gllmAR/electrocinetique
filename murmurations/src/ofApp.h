#pragma once

#include "ofMain.h"
#include "murmure.hpp"
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
    
    
    // Gui Stuff
    void setup_gui();
    ofxPanel settings_gui;
    ofxPanel murmure_gui;
    
    ofParameter<float> drag;
    ofParameter<float> friction;
    ofParameter<int> murmure_nombre = 32;
    ofParameter<float> playbackSpeedMin;
    ofParameter<float> playbackSpeedRange;
    ofParameter<float> volume;


    
    
        
    // particules stuffs
    void murmure_setup();
    void murmure_reset();
    void murmure_draw_gui();
    
    ofParameter<bool> murmure_draw_gui_toggle;
    ofParameter<int> murmure_draw_gui_index;
    ofParameter<int> murmure_gui_index;

    
    particleMode murmure_currentMode;
    string currentModeStr;
    
    vector <Murmure> murmure;
    
    vector <ofPoint> murmure_attractPoints;
    vector <ofPoint> murmure_attractPointsWithMovement;
    
    int murmure_nombre_old;
};
