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
    
  ofVec2f position, velocite, acceleration;
  float separateGroup, alignGroup, cohesionGroup;
  float distSeparationGroup, distAlignGroup, distCohesionGroup;
  float maxTurn, maxSpeed, maxForce;
  float attraction, attractiondeviation;
    
    
  float separateNoGroup, distSeparationNoGroup;
  float alignNoGroup, distAlignNoGroup;
    
  float attr;

  shared_ptr<Flock2d> flockPtr;
  shared_ptr<GroupBoid2d> groupPtr;
  ///////////////////////////////////////////////////////////////////
    
 
  Boid2d() {
    //x = y = vx = vy = ax = ay = 0.0f;
    position = velocite = acceleration = ofVec2f(0, 0);
    life = 1;
    flockPtr = nullptr;
    groupPtr = nullptr;
    attr = 10.0f;
        
    // new vabiable alex        
    separateGroup = 20.0f;
    alignGroup = 12.0f;
    cohesionGroup = 3.0f;
    distSeparationGroup = 10.0f;
    distAlignGroup = 20.0f;
    distCohesionGroup= 25.0f;
    maxSpeed = 2.f;
    maxForce = 10.0f;
    attraction = 100.5f;
    attractiondeviation =0.0f;
    group = 0;
        
  }
    
    
	
  Boid2d(std::shared_ptr<Flock2d> flock, std::shared_ptr<GroupBoid2d> _group);
	
  void setFlock(shared_ptr<Flock2d> flock);
	

  ////// set Valeurs
  void setValTotal(ofVec2f _position,
		   float _sepa,
		   float _alig,
		   float _cohe,
		   float _distSepa,
		   float _distAlig,
		   float _distCohe,
		   float _maxSpeed,
		   float _maxForce,
		   float _attraction,
		   float _attractiondeviation,
		   int _group) {
    setLoc(_position);
    setGroup(_group);
    setLead(false);
    setValSepa(_sepa, _distSepa);
    setValCohe(_cohe, _distCohe);
    setValAlig(_alig, _distAlig);
    maxSpeed = _maxSpeed;
    maxForce = _maxForce;
    setValAttraction(_attraction, _attractiondeviation);
    setValAlignNoGroup(20, 20);
    setValSepaNoGroup(20,20);    
  }
    
  void setLead(bool _lead){
    lead = _lead;      
  }
    
  void setGroup(int _group){
    group = _group;    
  }
    
  void setLoc(ofVec2f _position) {
    position = _position;    
  }
    
  void setVel(ofVec2f _velocite) {
    velocite = _velocite;    
  }
    
  void setValSepa(float _sepa, float _distSepa){
    separateGroup = _sepa;
    distSeparationGroup = _distSepa;    
  }
    
  void setValAlig(float _alig, float _distAlig){
    alignGroup = _alig;
    distAlignGroup = _distAlig;    
  }
    
  void setValCohe(float _cohe, float _distCohe){
    cohesionGroup = _cohe;
    distCohesionGroup = _distCohe;    
  }
    
  void setMaxSpeed(float _maxSpeed){
    maxSpeed = _maxSpeed;    
  }
    
  void setMaxForce(float _maxForce){
    maxForce = _maxForce;    
  }
    
  void setValAttraction(float _attraction, float _attractiondeviation){
    attraction = _attraction;
    attractiondeviation = _attractiondeviation;    
  }
    
  void setValSepaNoGroup(float _sepaNoGroup, float _distSeparateNoGroup){
    separateNoGroup = _sepaNoGroup;
    distAlignNoGroup = _distSeparateNoGroup;    
  }
    
  void setValAlignNoGroup(float _alignNoGroup, float _distAlignNoGroup){
    alignNoGroup = _alignNoGroup;
    distAlignNoGroup = _distAlignNoGroup;    
  }
    
  ////// fin set Valeurs alex

  void bounds();
    
  void boundsColision();
	
  /*
   * main funcs
   */
			
  void update(float amount);
    
  void flock( float amount, float vec[2]);	
	
  void steer(float target[2], float amount);
	
  void cohesion(float vec[2]);	
  void align( float vec[2]) ;		
  void separate( float vec[2]) ;
	
  void flockfull( float amount, float vec[2]);

  
    private:
    
    float* foncSep( float dx,  float dy,  float invD, shared_ptr<Boid2d> other, float sep[2]);
    float* foncCohe( float d,  float variable, shared_ptr<Boid2d> other, float coh[2]);
    float* foncAlig(shared_ptr<Boid2d> other, float ali[2]);
  
};
