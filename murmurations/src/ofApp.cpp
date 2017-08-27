#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
     ofSetVerticalSync(true);
    setup_gui();
    
}

//--------------------------------------------------------------
void ofApp::setup_gui()
{
    settings_gui.setup("");
    settings_gui.setName("settings");
    settings_gui.add(murmure_nombre.set("murmure_nombre",4,1,100));
    
    
    //settings_gui.add(murmure_draw_gui_toggle.set("murmure_draw_gui_toggle", 0));
    murmure_gui.setup("");
    murmure_gui.setName("murmure");
    
    murmure_gui.add(murmure_gui_index.set("murmure_gui_index", 0,0, 100));


    
   // murmure_draw_gui_toggle.addListener(this, &ofApp::murmure_draw_gui);
   // murmure_draw_gui_toggle.addListener(this, &ofApp::murmure_draw_gui);
   // murmure_draw_gui_index.addListener(this, &ofApp::murmure_draw_gui);
    
}
//--------------------------------------------------------------

void ofApp::murmure_setup()
{
    murmure.assign(murmure_nombre, Murmure() );
    murmure_currentMode = PARTICLE_MODE_ATTRACT;
    
    currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
    
    murmure_reset();

}
//--------------------------------------------------------------

void ofApp::murmure_reset()
{
    murmure_attractPoints.clear();
    for(int i = 0; i < 4; i++)
        {
        murmure_attractPoints.push_back( ofPoint(
            ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) ) );
        }
    
    murmure_attractPointsWithMovement = murmure_attractPoints;
    
    for(unsigned int i = 0; i < murmure.size(); i++){
        murmure[i].setMode(murmure_currentMode);
        murmure[i].setAttractPoints(&murmure_attractPointsWithMovement);;
        murmure[i].index=i;
        murmure[i].reset();
        
    }

    murmure_nombre_old=murmure_nombre;
    
}
//--------------------------------------------------------------
void ofApp::update(){

    if (murmure_nombre!=murmure_nombre_old){murmure_setup();}
    
     for(unsigned int i = 0; i < murmure.size(); i++)
     {
         murmure[i].update();
     }
    
    for(unsigned int i = 0; i < murmure_attractPointsWithMovement.size(); i++)
    {
        murmure_attractPointsWithMovement[i].x = murmure_attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
        murmure_attractPointsWithMovement[i].y = murmure_attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
    }
//    murmure_draw_gui();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

    for(unsigned int i = 0; i < murmure.size(); i++){
        murmure[i].draw();
    }
    
    
    ofSetColor(190);
    if( murmure_currentMode == PARTICLE_MODE_NEAREST_POINTS ){
        for(unsigned int i = 0; i < murmure_attractPoints.size(); i++){
            ofNoFill();
            ofDrawCircle(murmure_attractPointsWithMovement[i], 10);
            ofFill();
            ofDrawCircle(murmure_attractPointsWithMovement[i], 4);
        }
    }
    
    settings_gui.draw();
    murmure_gui.draw();
}


//--------------------------------------------------------------
void ofApp::murmure_draw_gui()
{
    // si le chiffre d'instance selectionne est different de l ancien
    for (int i = 0; i < murmure.size(); i++)
    {
        murmure[i].draw_gui = 1;
    }
    
    if(murmure_draw_gui_toggle && murmure_draw_gui_index<murmure.size() )
    {
        murmure[murmure_draw_gui_index].draw_gui = 1;
       
        
    }
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if( key == '1'){
        murmure_currentMode = PARTICLE_MODE_ATTRACT;
        //currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
         murmure_reset();
    }
    if( key == '2'){
        murmure_currentMode = PARTICLE_MODE_REPEL;
       // currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
         murmure_reset();
    }
    if( key == '3'){
        murmure_currentMode = PARTICLE_MODE_NEAREST_POINTS;
       // currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
         murmure_reset();
    }
    if( key == '4'){
        murmure_currentMode = PARTICLE_MODE_NOISE;
       // currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
        murmure_reset();
    }
    
    if( key == ' ' ){
        murmure_reset();
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
