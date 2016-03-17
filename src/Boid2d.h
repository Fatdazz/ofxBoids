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

class Flock2d;
class GroupBoid2d;

class Boid2d {
public:
	int life;
    bool lead;
    int group;
    
	int position[2], velocite[2], acceleration[2];
    float separateGroup, alignGroup, cohesionGroup;
    float distSeparationGroup, distAlignGroup, distCohesionGroup;
    float maxTurnAlex, maxSpeedAlex, maxForceAlex;
    float attractionAlex,attractiondeviationAlex;
    
    
    float separateNoGroup, distSeparationNoGroup;
    float alignNoGroup, distAlignNoGroup;
    
    float attr;
    
    Flock2d * flockPtr;
    GroupBoid2d * groupPtr; 
 
	Boid2d() {
        position[0] = velocite[0] = acceleration[0] = 0;
		position[1] = velocite[1] = acceleration[1] = 0;

		life = 1;
		flockPtr = nullptr;
        groupPtr = nullptr;
		attr = 0.0f;
        
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
    
    Boid2d(Flock2d * flock, GroupBoid2d * _group);
	
	void setFlock(Flock2d * flock);
	
	void setValTotal(int x, int y,
                    float _sepa,float _alig, float _cohe,
                    float _distSepa,float _distAlig, float _distCohe,
                    float _maxSpeed, float _maxForce,
                    float _attraction, float _attractiondeviation,
                    int _group) {

        this->setLoc(x, y);
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
    }
    
    void setLead( bool _lead){
        lead=_lead;
    }
    
    void setGroup(int _group){
        group=_group;
    }
    
	void setLoc(int x, int y) {
		position[0] = x;
		position[1] = y;
    }
    
    void setVel(int velX, int velY) {
        velocite[0] = velX;
		velocite[1] = velY;
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
        maxSpeedAlex=_maxSpeed;
    }
    
    void setMaxForce(float _maxForce){
        maxForceAlex=_maxForce;
    }
    
    void setValAttraction(float _attraction, float _attractiondeviation){
        attractionAlex=_attraction;
        attractiondeviationAlex=_attractiondeviation;
    }
    
    void setValSepaNoGroup(float _sepaNoGroup, float _distSeparateNoGroup){
        separateNoGroup=_sepaNoGroup;
        distAlignNoGroup=_distSeparateNoGroup;
    }
    
    void setValAlignNoGroup(float _alignNoGroup, float _distAlignNoGroup){
        alignNoGroup=_alignNoGroup;
        distAlignNoGroup=_distAlignNoGroup;
    }
    
    void bounds();
    
    void boundsColision();

    void update(const float amount);
	
	
	float* steer(float* target, float amount);

    float* flockfull(const float amount, float *vec);
    
private:
    
    void separate(const float dx, const float dy, const float invD, Boid2d& other, float *sep);
    void cohesion(const float d, const float variable,Boid2d& other, float *coh);
    void align(Boid2d& other, float *ali);
    
};
