//
//  GroupBoids2d.h
//  example-boids-attract
//
//  Created by FatDazz_mac on 02/03/2016.
//
//
#pragma once


//#ifndef GroupBoids2d_h
//#define GroupBoids2d_h
#include <ofMain.h>
#include "Boid2d.h"



//#endif /* GroupBoids2d_h */

class Regle{
public:
    int group;
    float dist, force;
    
    Regle() {
        group = 0;
        dist=force=0;
    }
    
void    initRegle(int _group, float _dist, float _force){
        group = _group;
        dist = _dist;
        force = _force;
    }
};

class GroupBoid2d {
public:
    
    vector<Boid2d *>    boids;
    
    
    
    void init(int num,
              ofVec2f _position, float dev,
              float _sepa,float _alig, float _cohe,
              float _distSepa, float _distAlig, float _distCohe,
              float _maxSpeed, float _maxForce,
              float _attraction, float _attractiondeviation,
              int _group) {
        
        for (int i = 0; i < num; i++) {
            _position.x += ofRandom(-dev, dev);
            _position.y += ofRandom(-dev, dev);
            Boid2d * b = new Boid2d () ;
            //Boid2d * b = new Boid2d(this);
            // need to be scattered or else no work
            b->setValTotal(_position,
                           _sepa,
                           _alig,
                           _cohe,
                           _distSepa,
                           _distAlig,
                           _distCohe,
                           _maxSpeed,
                           _maxForce,
                           _attraction,
                           _attractiondeviation,
                           _group);
            
            boids.push_back(b);
        }
    }
    
    void initVectorRegleDefault(int _group){
        Regle r ;
        r.initRegle(_group, 0.f, 0.f);
    }
    int getNumRegle(){
        return vectorRegle.size();
    }
    int getNumBoids(){
        return boids.size();
    }
    void update(const float amount){
        for(int i=0; i< boids.size() ; i++){
            boids[i]->update(amount);
        }
    }
    // Alig
    void setValsAligBoids(float _alig, float _distAlig){
        for (int i=0; i<boids.size(); i++) {
            setValsAligBoid(_alig, _distAlig, i);
        }
    }
    void setValsAligBoid(float _alig, float _distAlig, int _at){
            Boid2d *b = boids[_at];
            b->setValAlig(_alig, _distAlig);
    }
    // Sepa
    void setValsSepaBoids(float _sepa, float _distSepa){
        for (int i=0; i<boids.size(); i++) {
            setValsSepaBoid(_sepa, _distSepa, i);
        }
    }
    void setValsSepaBoid(float _sepa, float _distSepa, int _at){
            Boid2d *b = boids.at(_at);
            b->setValSepa(_sepa,_distSepa);
    }
    // Cohe
    void setValsCoheBoids(float _cohe, float _distCohe){
        for (int i=0; i<boids.size(); i++) {
            setValsCoheBoid(_cohe, _distCohe, i);
        }
    }
    void setValsCoheBoid(float _cohe, float _distCohe, int _at){
            Boid2d *b = boids.at(_at);
            b->setValCohe(_cohe,_distCohe);
    }
    // Speed
    void setMaxSpeedBoids(float _maxSpeed){
        for (int i=0; i<boids.size(); i++) {
            setMaxSpeedBoid(_maxSpeed, i);
        }
    }
    void setMaxSpeedBoid(float _maxSpeed, int _at){
            Boid2d *b = boids.at(_at);
            b->setMaxSpeed(_maxSpeed);
    }
    // Force
    void setMaxForceBoid(float _maxForce, int _at){
            Boid2d *b =boids.at(_at);
            b->setMaxForce(_maxForce);
    }
    void setMaxForceBoids(float _maxFore){
        for (int i=0; i<boids.size(); i++) {
            setMaxForceBoid(_maxFore, i);
        }
    }
    // Lead
    void setLead(bool _lead,int _at){
        Boid2d *b = boids.at(_at);
        b->setLead(_lead);
    }
    
    // val global
    void setValsGlobalBoids(float _alig, float _distAlig,float _sepa, float _distSepa,float _cohe, float _distCohe){
        for (int i=0; i<boids.size(); i++) {
            setValsAligBoids(_alig, _distAlig);
            setValsCoheBoids(_cohe, _distCohe);
            setValsSepaBoids(_sepa, _distSepa);
        }
    }
    


private:
    vector<Regle>   vectorRegle;
    bool            actRegle = false;
    
};