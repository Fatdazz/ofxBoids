#pragma once

#include "ofMain.h"

#include "Flock2d.h"
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Flock2d flock;
    
    
    
    /*
    separate = 20.0f;
    align = 12.0f;
    cohesion = 3.0f;
    distSeparation = 10.0f;
    distAlign = 20.0f;
    distCohesion = 25.0f;
    // maxTurn, maxSpeed, maxForce;
    maxSpeed = 2.f;
    maxForce = 10.0f;
    attraction = 100.5f;
    attractiondeviation =3.0f;
    */
    ofParameter<float> separate;
    ofParameter<float> align;
    ofParameter<float> cohesion;
    ofParameter<float> distSeparation;
    ofParameter<float> distAlign;
    ofParameter<float> distCohesion;
    ofParameter<float> maxSpeed;
    ofParameter<float> maxForce;
    ofParameter<float> attraction;
    ofParameter<float> attractiondeviation;
    ofxPanel gui;
    
    
};
