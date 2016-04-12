//
//  BoidsThread.cpp
//  BoidsApoil
//
//  Created by FatDazz_mac on 12/04/2016.
//
//
#pragma once

#include "BoidsThread.h"
#include "ofConstants.h"

BoidsThread::BoidsThread():newFrame(true){
    startThread();
    
    flockTest.setBounds(0, 0, 1920, 1080);
    flockTest.setBoundmode(1);
    for (int i=0; i<NumGroup; i++) {
        flockTest.addGoup();
        
        int lulu= ofRandom(30, 100);
        for (int j=0; j<300; j++) {
            
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
    
    flockTest.addAttractionPoint(ofGetWidth()/2, ofGetHeight()/2, -20, 100); // attraction Point
    
    flockTest.addAttrationLine(ofPoint(100,200), ofPoint(200,500), -200, 150, 0, 0);
    
    
    //flockTest.changeRegle(0, 1, 30, 30, -20, 30, -20, 10);
    
    for (int i=0; i<NumGroup; i++) {
        flockTest.groupBoid[i]->actAllRegle(i);
    }
    //parametersGui->paraBoids[0].color.set(ofColor(255, 0, 0));
    //parametersGui->paraBoids[1].color.set(ofColor(0, 255, 0));
    //parametersGui->paraBoids[2].color.set(ofColor(0, 0, 255));
}



BoidsThread::~BoidsThread(){
    
    //waitForThread(true);

}


void BoidsThread::BoidsDraw(){
    float a[2]={100,200};
    float b[2]={300,600};
    
    
    flockTest.attractionLines[0]->draw();
    for (int i=0; i<NumGroup; i++) {
        GroupBoid2d *g =flockTest.groupBoid.at(i);
        ofSetColor(parametersGui->paraBoids[i].color);
        for (int j=0; j<g->boids.size(); j++) {
            
            Boid2d  *b = g->boids.at(j);
            
            ofDrawRectangle(b->position.x, b->position.y, 5,5);
            float lm = 10.f;
            ofDrawLine(b->position.x, b->position.y, b->position.x + b->velocite.x*lm, b->position.y + b->velocite.y*lm);
        }
    }
    
    
    ofSetColor(255, 0, 0, 25);
    //flockTest.attractionPoints[0]->draw();
    //ofDrawLine(a[0], a[1], b[0], b[1]);

}

void BoidsThread::threadedFunction(){
    while (0==0) {
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
    
    
}
