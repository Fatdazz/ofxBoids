#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BoidsBehaviour.h"

class ParametersGUI : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	int nbSubFlocks;

	//	Parametres partagés avec ofApp
	//	Bequilles à faire disparaitre quand ofBoids sera itérable par groupe
	//	Groupe 1
	ofParameter<float> separate1;
	ofParameter<float> align1;
	ofParameter<float> cohesion1;
	ofParameter<float> distSeparation1;
	ofParameter<float> distAlign1;
	ofParameter<float> distCohesion1;
	ofParameter<float> maxSpeed1;
	ofParameter<float> maxForce1;
	ofParameter<float> attraction1;
	ofParameter<float> attractionDeviation1;
	//	Groupe 2
	ofParameter<float> separate2;
	ofParameter<float> align2;
	ofParameter<float> cohesion2;
	ofParameter<float> distSeparation2;
	ofParameter<float> distAlign2;
	ofParameter<float> distCohesion2;
	ofParameter<float> maxSpeed2;
	ofParameter<float> maxForce2;
	ofParameter<float> attraction2;
	ofParameter<float> attractionDeviation2;

	// Version pour itération sur N groupe.
	vector<ofParameterGroup> boidsBehaviour;
	//
	ofParameter<float> separate;
	ofParameter<float> align;
	ofParameter<float> cohesion;
	ofParameter<float> distSeparation;
	ofParameter<float> distAlign;
	ofParameter<float> distCohesion;
	ofParameter<float> maxSpeed;
	ofParameter<float> maxForce;
	ofParameter<float> attraction;
	ofParameter<float> attractionDeviation;

	//	Version avec structure de donné behaviour	
	//ofParameter<vector<BoidsBehaviour>> groupBehaviours;

	//	Panels
	vector<ofxPanel> parametersPanels;

};