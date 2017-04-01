#pragma once
#include <ofMain.h>



class Flock2d;
class GroupBoid2d;

class Boid2d {
public:
    ///////////////////////////////////////////////////////////////////
    //float x, y, vx, vy, ax, ay;
    int life;
    bool lead;
    int group;
    
    ofVec2f ref, position, velocite, acceleration;
    float separateGroup, alignGroup, cohesionGroup;
    float distSeparationGroup, distAlignGroup, distCohesionGroup;
    float maxTurnAlex, maxSpeed, maxForce;
    
    float attractionAlex,attractiondeviationAlex;
    float attr;
    
    Flock2d * flockPtr;
    GroupBoid2d * groupPtr;
    ///////////////////////////////////////////////////////////////////
    
    
    Boid2d() {
        //x = y = vx = vy = ax = ay = 0.0f;
        ref = position = velocite = acceleration = ofVec2f(0, 0);
        life = 1;
        flockPtr = NULL;
        groupPtr = NULL;
        attr = 10.0f;
        // new vabiable alex
        separateGroup= 20.0f;
        alignGroup = 12.0f;
        cohesionGroup = 3.0f;
        distSeparationGroup = 10.0f;
        distAlignGroup = 20.0f;
        distCohesionGroup= 25.0f;
        maxSpeed = 2.f;
        maxForce = 10.0f;
        attractionAlex = 100.5f;
        attractiondeviationAlex =0.0f;
        lead =true;
    }
    Boid2d(Flock2d * flock, GroupBoid2d * _group);
    Boid2d(Flock2d * flock);
    Boid2d * setFlock(Flock2d * flock);
    
    
    ////// set Valeurs
    Boid2d * setValTotal(ofVec2f _position,
                         float _sepa,float _alig, float _cohe,
                         float _distSepa,float _distAlig, float _distCohe,
                         float _maxSpeed, float _maxForce,
                         float _attraction, float _attractiondeviation,
                         int _group) {
        
        this->setLoc(_position);
        this->setLead(false);
        this->setValSepa(_sepa, _distSepa);
        this->setValCohe(_cohe, _distCohe);
        this->setValAlig(_alig, _distAlig);
        maxSpeed = _maxSpeed;
        maxForce = _maxForce;
        this->setValAttraction(_attraction, _attractiondeviation);
        return this;
    }
    
    Boid2d * setLead( bool _lead){
        lead=_lead;
        return this;
    }
    Boid2d * setLoc(ofVec2f _position) {
        position = _position;
        return this;
    }
    Boid2d * setVel(ofVec2f _velocite) {
        velocite=_velocite;
        return this;
    }
    Boid2d * setValSepa(float _sepa, float _distSepa){
        separateGroup = _sepa;
        distSeparationGroup = _distSepa;
        return this;
    }
    Boid2d * setValAlig(float _alig, float _distAlig){
        alignGroup = _alig;
        distAlignGroup = _distAlig;
        return this;
    }
    Boid2d * setValCohe(float _cohe, float _distCohe){
        cohesionGroup = _cohe;
        distCohesionGroup = _distCohe;
        return this;
    }
    Boid2d * setMaxSpeed(float _maxSpeed){
        maxSpeed=_maxSpeed;
        return this;
    }
    Boid2d * setMaxForce(float _maxForce){
        maxForce=_maxForce;
        return this;
    }
    Boid2d * setValAttraction(float _attraction, float _attractiondeviation){
        attractionAlex=_attraction;
        attractiondeviationAlex=_attractiondeviation;
        return this;
    }
    ////// fin set Valeurs alex
    void bounds();
    void boudsColision();
    
    /*
     * main funcs
     */


    ///// fonction Utile /////
       void update(vector<Boid2d*> *otherBoids,vector<vector<ofVec2f>> *fieldVector);
        
private:
    float* flockfullNew(float *vec, vector<Boid2d*> *otherBoids);
    float* steer(float* target, float amount);
    float* foncSep(const float dx, const float dy, const float invD, Boid2d *other, float *sep);
    float* foncCohe(const float d, const float variable,Boid2d *other, float *coh);
    float* foncAlig(Boid2d *other, float *ali);
    
};
