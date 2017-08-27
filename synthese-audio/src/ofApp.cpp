#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(34, 34, 34);
    
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.1f;
    bNoise 				= false;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);

    
    soundStream.printDeviceList();
    
    ofSoundStreamSettings settings;
    
    // if you want to set the device id to be different than the default:
    //
    //	auto devices = soundStream.getDeviceList();
    //	settings.setOutDevice(devices[3]);
    
    // you can also get devices for an specific api:
    //
    //	auto devices = soundStream.getDeviceList(ofSoundDevice::Api::PULSE);
    //	settings.setOutDevice(devices[0]);
    
    // or get the default device for an specific api:
    //
    // settings.api = ofSoundDevice::Api::PULSE;
    
    // or by name:
    //
    //	auto devices = soundStream.getMatchingDevices("default");
    //	if(!devices.empty()){
    //		settings.setOutDevice(devices[0]);
    //	}
    
#ifdef TARGET_LINUX
    // Latest linux versions default to the HDMI output
    // this usually fixes that. Also check the list of available
    // devices if sound doesn't work
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setOutDevice(devices[0]);
    }
#endif
    
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(225);
    
    ofNoFill();
    
    // draw the left channel:
    ofPushStyle();
    ofPushMatrix();
    
    ofSetLineWidth(1);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < lAudio.size(); i++){
        float x =  ofMap(lAudio[i], -1.0, 1.0, 0, 480, true);
        float y =  ofMap(rAudio[i], -1.0, 1.0, 0, 480, true);

        ofVertex(x, y);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
}
//--------------------------------------------------------------

void ofApp::audioOut(ofSoundBuffer & buffer){
    //pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
    // sin (n) seems to have trouble when n is very large, so we
    // keep phase in the range of 0-TWO_PI like this:
    while (phase > TWO_PI){
        phase -= TWO_PI;
    }
    
        phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
        for (int i = 0; i < buffer.getNumFrames(); i++){
            phase += phaseAdder;
            float sampleX = sin(phase);
            float sampleY = cos(phase);
            lAudio[i] = buffer[i*buffer.getNumChannels()    ] = sampleX * volume * leftScale;
            rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = sampleY * volume * rightScale;
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
    float height = (float)ofGetHeight();
    float heightPct = ((height-y) / height);
    targetFrequency = 2000.0f * heightPct;
    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    int width = ofGetWidth();
    pan = (float)x / (float)width;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
