//
//  SoundStreamSettings.hpp
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//
// sert a configurer le soundstream et sauvegarder
// logique de parser le system (une config par system)



#ifndef ofxSoundSettingsGui_hpp
#define ofxSoundSettingsGui_hpp

#include "ofMain.h"
#include "ofxGui.h"


g
class ofxSoundSettingsGui
{
public:
    void setup();
    void init();
    void update();
    void draw();
    void exit();
    void audioIn(ofSoundBuffer & input);
    void audioOut(ofSoundBuffer & output);
    
    ofSoundStream soundStream;

    
    ofxGuiGroup soundStreamGuiGroup;
    ofParameter <int> buffer_size;
    ofParameter <int> sample_rate;
    
    vector <vector <float>> in;
    vector <float> left;
     vector <float> right;
    vector <float> out1;
    vector <float> out2;
    vector <float> volHistory;
    int 	bufferCounter;

    


};


#endif /* SoundStreamSettings_hpp */
