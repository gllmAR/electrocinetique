//
//  murmure.hpp
//  murmurations
//
//  Created by Guillaume Arseneault on 17-07-02.
//
//

#pragma once
#include "ofMain.h"
#include "ofxGui.h"

enum particleMode{
    PARTICLE_MODE_ATTRACT = 0,
    PARTICLE_MODE_REPEL,
    PARTICLE_MODE_NEAREST_POINTS,
    PARTICLE_MODE_NOISE
};

class Murmure{
    
public:
    Murmure();
    
    void setMode(particleMode newMode);
    void setAttractPoints( vector <ofPoint> * attract );
    void setVelFactor(float factor);
    void setFrcFactor(float factor);
    void setDragFactor(float factor);
    
    void reset();
    void update();
    void draw();
    
    
    
    ofPoint pos;
    ofPoint vel;
    ofPoint frc;
    
    float drag;
    float uniqueVal;
    ofParameter<float> scale;
    
    
    bool draw_gui =0;
   
    int index =0;
    
    
    particleMode mode;
    
    vector <ofPoint> * attractPoints;
    
    
    ofParameter<float> velFactor = 1.0f;
    ofParameter<float> dragFactor = 1.0f;
    ofParameter<float> frcFactor = 4.0f;
//private:
//    void setup_gui();
//    ofxPanel gui;
//    ofParameter<float> unique_val_gui;
};

