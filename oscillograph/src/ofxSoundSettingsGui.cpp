//
//  ofxSoundSettingsGui.
//  oscillograph
//
//  Created by Guillaume Arseneault on 17-08-07.
//
//

#include "ofxSoundSettingsGui.hpp"

void ofxSoundSettingsGui::setup()
{
    soundStreamGuiGroup.setup();
    soundStreamGuiGroup.setName("sound_settings");
    soundStreamGuiGroup.add(buffer_size.set("buffer_size",256,64,4096));
    soundStreamGuiGroup.add(sample_rate.set("sample_rate",44100,8000,192000));
    
    soundStream.printDeviceList();
    ofSoundStreamSettings settings;
    
   
#ifdef TARGET_LINUX_ARM
    auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[0]);
    
    
#else
    auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[3]);
    settings.setOutDevice(devices[3]);
#endif
    
    settings.setInListener(this);
    settings.setOutListener(this);
    settings.sampleRate = sample_rate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 2;
    settings.bufferSize = buffer_size;
    soundStream.setup(settings);
    
    // ici un init vector de channels
        left.assign(buffer_size, 0.0);
        right.assign(buffer_size, 0.0);
        out1.assign(buffer_size, 0.0);
        out2.assign(buffer_size, 0.0);

}


void ofxSoundSettingsGui::init()
{
    // mettre tout ce qui est de l ordre des settings dans ce segments et l appeler a partir du setup
    // lorsque que les settings on change
    
}

// voir si channel out ce comporte de la meme facon

void ofxSoundSettingsGui::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // au lieu d avoir left right mieux de travailler en un vecteur de channel input
    // samples are "interleaved"
    int numCounted = 0;
    
    for (int i = 0; i < input.getNumFrames(); i++){
        left[i]	 = input[i*2]*0.5;
        right[i] = input[i*2+1]*0.5;
        
        numCounted+=2;
    }
    
    bufferCounter++;
     
}

void ofxSoundSettingsGui::audioOut(ofSoundBuffer & output){
    
    // pas besoins d'out pour maintenant
//    float curVol = 0.0;
//    
//    // au lieu d avoir left right mieux de travailler en un vecteur de channel input
//    // samples are "interleaved"
//    int numCounted = 0;
//    
//    for (int i = 0; i < output.getNumFrames(); i++){
//        out1[i] = output[i*output.getNumChannels()    ] = left[i];
//        out2[i] = output[i*output.getNumChannels()  +1] = right[i];
//        
//        numCounted+=2;
//    }
    

    
}

void ofxSoundSettingsGui::update()
{
    // regarder si les param ont change et reinit le cas echeant
    //ofSoundUpdate();
}

void ofxSoundSettingsGui::draw()
{
    //probablement mettre un if drawGui
    soundStreamGuiGroup.draw();
}

// soundSettingsGui.getBufferSize

