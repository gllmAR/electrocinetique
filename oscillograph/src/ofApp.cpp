#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);

    cam.setDistance(750);
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
	auto devices = soundStream.getDeviceList();
    settings.setInDevice(devices[0]);
        

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
    parameters.add(shapeScale.set("shapeScale",.85,0,2));
    parameters.add(line_width.set("line_width",1,1,10));
    parameters.add(line_color.set("color",ofColor(255),ofColor(0,0),ofColor(255)));
    parameters.add(cam_set_ortho.set("cam_set_ortho", 1));
    parameters.add(cam_set_reset.set("cam_set_reset", 1));
    parameters.add(set_fullscreen.set("fullscreen", 0));

    
    gui.setup(parameters);
    
    
    gui.loadFromFile("settings.xml");
    
    rhizome_init();
    
    sync.setup((ofParameterGroup&)gui.getParameter(),RHIZOME_OUTPORT,"localhost",RHIZOME_INPORT);
    
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    	sync.update();

    
    timestamp=ofGetElapsedTimeMillis();
    
    
    for (unsigned int i = 0; i < (left.size()+right.size())/2; i++)
    {
        ofVec3f coord (left[i]*app_size_w*shapeScale,
                    right[i]*app_size_w*shapeScale, timestamp);
        vbo_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        vbo_mesh.addVertex(coord);
        
    }
    
    int vertex_buffer = vbo_mesh.getNumVertices();
    
    if (vertex_buffer > 1024)
    {
        for (int i =0; i <512; i++)
        {
            vbo_mesh.removeVertex(i);
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (set_fullscreen_old != set_fullscreen)
    {
        ofSetFullscreen(set_fullscreen);
        set_fullscreen_old = set_fullscreen;
    };
    
    ofEnableDepthTest();
    if (cam_set_ortho){cam.enableOrtho();}else{cam.disableOrtho();};
    if (cam_set_reset){cam.reset(); cam_set_reset=0;};
    
    cam.setDistance(timestamp);
    cam.begin();
    ofNoFill();
    
    // draw the OSCILO channel:
    ofPushStyle();
    ofPushMatrix();

    
    ofSetColor(line_color);
    ofSetLineWidth(line_width);
    
    vbo_mesh.draw();
   
    
//    ofBeginShape();
//        for (unsigned int i = 0; i < right.size(); i++)
//        {
//            ofVertex(left[i]*app_size_w*shapeScale,
//                     0 -right[i]*app_size_h*shapeScale,
//                     i);
//       
//        }
//    ofEndShape(false);

    ofPopMatrix();
    ofPopStyle();
    
    cam.end();
    
    ofDisableDepthTest();
    
    if (gui_draw)
    {
        gui.draw();
    }
}
//--------------------------------------------------------------


void ofApp::audioIn(ofSoundBuffer & input){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    for (int i = 0; i < input.getNumFrames(); i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        numCounted+=2;
    }
    
    bufferCounter++;
    
}
//--------------------------------------------------------------



//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){
        gui_draw=!gui_draw;
    }
    
    if (key == 'f'){
        set_fullscreen=!set_fullscreen;
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

void ofApp::rhizome_init()
{
    sender.setup(HOST, RHIZOME_INPORT);
    ofxOscMessage m;
    m.setAddress("/sys/subscribe");
    m.addIntArg(RHIZOME_OUTPORT);
    m.addStringArg("/");
    sender.sendMessage(m, false);
}
