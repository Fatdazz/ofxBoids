/*
 *  Boid2d.h
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 s373.net/x. All rights reserved.
 *
 */

/**
 * Boids
 * Simulation of autonomous agent behaviors in 2D, 3D.
 * Based on code by Craig Reynolds, Daniel Shiffman. 
 * Besides Cohesion, Separation, Alignment, adds multiple 
 * force points creating interesting targets in the simulation.
 * http://s373.net/code/boids
 *
 * Copyright (C) 2007-2013 Andre Sier http://s373.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 */

#pragma once
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <ofMain.h>
//#include "opencv2/opencv.hpp"


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
    float maxTurnAlex, maxSpeedAlex, maxForceAlex;
    float attractionAlex,attractiondeviationAlex;
    
    
    float separateNoGroup, distSeparationNoGroup;
    float alignNoGroup, distAlignNoGroup;
    
    float attr;
    
    Flock2d * flockPtr;
    GroupBoid2d * groupPtr;
///////////////////////////////////////////////////////////////////
    
 
	Boid2d() {
		//x = y = vx = vy = ax = ay = 0.0f;
        position = velocite = acceleration = ofVec2f(0, 0);
		life = 1;
		flockPtr = NULL;
        groupPtr = NULL;
		attr = 0.0f;
        
        // new vabiable alex
        
        separateGroup= 20.0f;
        alignGroup = 12.0f;
        cohesionGroup = 3.0f;
        distSeparationGroup = 10.0f;
        distAlignGroup = 20.0f;
        distCohesionGroup= 25.0f;
        maxSpeedAlex = 2.f;
        maxForceAlex = 10.0f;
        attractionAlex = 100.5f;
        attractiondeviationAlex =0.0f;
        group=0;
        
	}
    
    
	
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
        this->setGroup(_group);
        this->setLead(false);
        this->setValSepa(_sepa, _distSepa);
        this->setValCohe(_cohe, _distCohe);
        this->setValAlig(_alig, _distAlig);
        maxSpeedAlex = _maxSpeed;
        maxForceAlex = _maxForce;
        this->setValAttraction(_attraction, _attractiondeviation);
        this->setValAlignNoGroup(20, 20);
        this->setValSepaNoGroup(20,20);
        return this;
    }
    
    Boid2d * setLead( bool _lead){
        lead=_lead;
        return this;
    }
    
    Boid2d * setGroup(int _group){
        group=_group;
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
        maxSpeedAlex=_maxSpeed;
        return this;
    }
    
    Boid2d * setMaxForce(float _maxForce){
        maxForceAlex=_maxForce;
        return this;
    }
    
    Boid2d * setValAttraction(float _attraction, float _attractiondeviation){
        attractionAlex=_attraction;
        attractiondeviationAlex=_attractiondeviation;
        return this;
    }
    
    Boid2d * setValSepaNoGroup(float _sepaNoGroup, float _distSeparateNoGroup){
        separateNoGroup=_sepaNoGroup;
        distAlignNoGroup=_distSeparateNoGroup;
        return this;
    }
    
    Boid2d * setValAlignNoGroup(float _alignNoGroup, float _distAlignNoGroup){
        alignNoGroup=_alignNoGroup;
        distAlignNoGroup=_distAlignNoGroup;
        return this;
    }
    
    
////// fin set Valeurs alex



    void bounds();
    
    void boudsColision();
	
	/*
	 * main funcs
	 */
			
    void update(const float amount);
    
	float* flock(const float amount, float *vec) ;
	
	
	float* steer(float* target, float amount);// , float *steervec);
	
	float* cohesion( float *vec);	
	float* align( float *vec) ;		
	float* separate( float *vec) ;

	
    float* flockfull(const float amount, float *vec);
    
private:
    
    float* foncSep(const float dx, const float dy, const float invD, Boid2d *other, float *sep);
    float* foncCohe(const float d, const float variable,Boid2d *other, float *coh);
    float* foncAlig(Boid2d *other, float *ali);
    
};
