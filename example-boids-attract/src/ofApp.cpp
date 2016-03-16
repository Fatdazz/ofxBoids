#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    flockTest.setBounds(0, 0, ofGetWidth(), ofGetHeight());
    flockTest.setBoundmode(1);
    for (int i=0; i<NumGroup; i++) {
        flockTest.addGoup();
        
        int lulu= ofRandom(30, 100);
        for (int j=0; j<100; j++) {
            flockTest.addBoidGroup(i,
                                   ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())),
                                   20 ,
                                   10 ,
                                   10 ,
                                   35,
                                   12,
                                   20,
                                   1000,
                                   2);
        }
    }
    
    parametersGui->paraBoids[0].color.set(ofColor(255, 0, 0));
    parametersGui->paraBoids[1].color.set(ofColor(0, 255, 0));
    parametersGui->paraBoids[2].color.set(ofColor(0, 0, 255));

}

//--------------------------------------------------------------
void ofApp::update(){
    flockTest.update();
    for (int i=0; i<NumGroup; i++) {
        flockTest.setValeursBoidsGroup(i,
                                       parametersGui->paraBoids[i].sepa,
                                       parametersGui->paraBoids[i].distsepa,
                                       parametersGui->paraBoids[i].cohe,
                                       parametersGui->paraBoids[i].disCohe,
                                       parametersGui->paraBoids[i].ali,
                                       parametersGui->paraBoids[i].disAli,
                                       parametersGui->paraBoids[i].maxForce,
                                       parametersGui->paraBoids[i].maxSpeed);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    for (int i=0; i<NumGroup; i++) {
        GroupBoid2d *g =flockTest.groupBoid.at(i);
        ofSetColor(parametersGui->paraBoids[i].color);
        for (int j=0; j<g->boids.size(); j++) {

            Boid2d *b = g->boids.at(j);
            
            if (j==0) {
                
            }
            ofRect(b->position.x, b->position.y, 5,5);
            float lm = 10.f;
            ofLine(b->position.x, b->position.y, b->position.x + b->velocite.x*lm, b->position.y + b->velocite.y*lm);
        }
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
