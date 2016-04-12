

//  BoidsThread.hpp
//  BoidsApoil
//
//  Created by FatDazz_mac on 12/04/2016.
//
//
#pragma once
#include "ofMain.h"
#include "Flock2d.h"
#include "ofxGui.h"
#include "ParametersGUI.h"
#include "VariableGlobal.h"
class BoidsThread: public ofThread{
public:
    
    BoidsThread();
    ~BoidsThread();
    //setupBoid();
void BoidsDraw();
    
    
    
    shared_ptr<ParametersGUI> parametersGui;
    Flock2d  flockTest;
    
private:
    bool newFrame;
    void threadedFunction();
};
