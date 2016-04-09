/*
* parametersGUI.cpp
*/

#include "parametersGUI.h"

void ParametersGUI::setup() {
    

    ofParameterGroup GuiPara;
    for (int i=0; i<NumGroup; i++) {
        //paraBoids.push_back(*new ParametresBoids);
        paraBoids.emplace_back();
        paraBoids[i].nameGroup("group-"+to_string(i+1));
        GuiPara.add(paraBoids[i].parametres);

    }
    GUI.setup(GuiPara);
    GUI.minimizeAll();
    
}

void ParametersGUI::update() {
    ofSetWindowTitle(to_string(ofGetFrameRate()));
	// Doit rester vide
}

void ParametersGUI::draw() {
    
    GUI.draw();


}