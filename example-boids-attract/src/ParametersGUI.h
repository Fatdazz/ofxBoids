#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "VariableGlobal.h"


class ParametresBoids{
public:

    ofParameterGroup    parametres;
    
    ofParameterGroup    separates;
    ofParameter<float>  sepa;
    ofParameter<float>  distsepa;
    
    ofParameterGroup    cohesion;
    ofParameter<float>  cohe;
    ofParameter<float>  disCohe;
    
    ofParameterGroup    align;
    ofParameter<float>  ali;
    ofParameter<float>  disAli;
    
    ofParameterGroup    ForceSpeed;
    ofParameter<float>  maxForce;
    ofParameter<float>  maxSpeed;
    
    ofParameter<ofColor> color;
    
    ParametresBoids(){
        
        separates.setName("Sepa");
        separates.add(sepa.set("sepa",10,0,100));
        separates.add(distsepa.set("distSepa",10,0,100));
        
        cohesion.setName("Cohe");
        cohesion.add(cohe.set("cohe",10,0,100));
        cohesion.add(disCohe.set("distCohe",10,0,100));
        
        align.setName("alig");
        align.add(ali.set("ali",10,0,100));
        align.add(disAli.set("distAli",10,0,100));
        
        ForceSpeed.setName("Force & Speed");
        ForceSpeed.add(maxForce.set("Force",1000,0,5000));
        ForceSpeed.add(maxSpeed.set("Speed",2,0,10));
        
        parametres.add(color);
        parametres.add(separates);
        parametres.add(cohesion);
        parametres.add(align);
        parametres.add(ForceSpeed);
        
        color.set("color",ofColor(127),ofColor(0,0),ofColor(255));
        

    }
    
    void nameGroup(string _name){
        parametres.setName(_name);
    }
    
};

class ParametersGUI : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

    
    vector<ParametresBoids> paraBoids;
    
    //vector<ParametresBoids> GuiBoidsGroup;
	//vector<ofxPanel> GUI;
    ofxPanel           panel;
    ofxGuiGroup        GUI;
    
    
};