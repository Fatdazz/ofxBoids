#pragma once

#include "ofMain.h"
#include "ParametersGUI.h"
#include "Flock2d.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
	// Inputs
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
	//	Flocks
    Flock2d flock1;
	int nbSubFlocks;

	//	Panels
    ofxPanel flockPanel;

	//	Shared data
	shared_ptr<ParametersGUI> parametersGui;
    
};
