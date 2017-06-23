#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    sampleRate = 44100;
    ofSetFrameRate(60);
    
    soundStream.printDeviceList();

    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    

    
    bufferCounter	= 0;
//    drawCounter		= 0;
//    smoothedVol     = 0.0;
//    scaledVol		= 0.0;
//    
    
    ofSoundStreamSettings settings;

#ifdef TARGET_LINUX_ARM
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
#else
    auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[3]);
#endif
    
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    

    
    
    // gui setup
    parameters.setName("parameters");
    parameters.add(shapeScale.set("shapeScale",.5,0,1));
     parameters.add(line_width.set("line_width",1,1,10));
    parameters.add(line_color.set("color",ofColor(127),ofColor(0,0),ofColor(255)));


    
    gui.setup(parameters);
    

    
}



//--------------------------------------------------------------
void ofApp::update(){


//    //lets scale the vol up to a 0-1 range
//    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
//    
//    //lets record the volume into an array
//    volHistory.push_back( scaledVol );
//    
//    //if we are bigger the the size we want to record - lets drop the oldest value
//    if( volHistory.size() >= 400 ){
//        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (gui_draw)
    {
        gui.draw();
    }
    ofNoFill();
    
    // draw the OSCILO channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(app_size_w/2,
                app_size_h/2,
                0);
    

    
    ofSetColor(line_color);
    ofSetLineWidth(line_width);
    
    ofBeginShape();
    for (unsigned int i = 0; i < right.size(); i++){
        ofVertex(left[i]*app_size_w*shapeScale,
                 0 -right[i]*app_size_h*shapeScale);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
}
//--------------------------------------------------------------


void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < input.getNumFrames(); i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
//        curVol += left[i] * left[i];
//        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
//    //this is how we get the mean of rms :)
//    curVol /= (float)numCounted;
//    
//    // this is how we get the root of rms :)
//    curVol = sqrt( curVol );
    
//    smoothedVol *= 0.93;
//    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}
//--------------------------------------------------------------



//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){
        gui_draw=!gui_draw;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

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
    app_size_w = w;
    app_size_h = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::exit(){
    
    
}
