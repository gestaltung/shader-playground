#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    //    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    WIDTH = ofGetScreenWidth();
    WIDTH = 1024;
    HEIGHT = ofGetScreenHeight();
    HEIGHT = 768;
    
    fbo.allocate(WIDTH, HEIGHT);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(mudiness.set( "distortion", 5, 1, 9 ));
    bHide = false;
    
    //    ofEnableNormalizedTexCoords();
    //    ofSetOrientation(OF_ORIENTATION_DEFAULT,false);
    ofDisableArbTex();
    
    noiseTex.load("noiseTex.png");
    
    cam.initGrabber(WIDTH, HEIGHT);
    shader.load("distortion.vert", "distortion.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    shader.begin();
    shader.setUniformTexture("srcTex", cam.getTexture(), 1);
    shader.setUniformTexture("noiseTex", noiseTex.getTexture(), 2);
    shader.setUniform2f("u_resolution", WIDTH, HEIGHT);
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    fbo.begin();
    cam.draw(0, 0);
    fbo.end();
    fbo.draw(0,0);
    
    shader.end();
    
    if( !bHide ){
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
        bHide = !bHide;
    }
    
    if (key=='l') {
        shader.load("distortion.vert", "distortion.frag");
    }
    
    if(key == 's') {
        gui.saveToFile("settings.xml");
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
