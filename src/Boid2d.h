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

class Flock2d;

class Boid2d {
public:
	
	float x, y, vx, vy, ax, ay;
	int life;
	
    // new vabiable alex
    float separateAlex, alignAlex, cohesionAlex;
    float distSeparationAlex, distAlignAlex, distCohesionAlex;
    float maxTurnAlex, maxSpeedAlex, maxForceAlex;
    float attractionAlex,attractiondeviationAlex;
    int group;
    // fin new variable alex
    
    float attr;
	
	Flock2d * flockPtr;
	
	// public Team team;
	// public int om;
	// public float forceSeparate, forceAlign, forceCohesion;
	// public float maxTurn, maxSpeed, maxForce;
	
	Boid2d() {
		x = y = vx = vy = ax = ay = 0.0f;
		life = 0;
		flockPtr = NULL;
		attr = 0.0f;
        
        // new vabiable alex
        
        separateAlex = 20.0f;
        alignAlex = 12.0f;
        cohesionAlex = 3.0f;
        distSeparationAlex = 10.0f;
        distAlignAlex = 20.0f;
        distCohesionAlex= 25.0f;
        maxSpeedAlex = 2.f;
        maxForceAlex = 10.0f;
        attractionAlex = 100.5f;
        attractiondeviationAlex =0.0f;
        group=0;
        // fin new variable alex
	}
	
	Boid2d(Flock2d * flock);
	
	Boid2d * setFlock(Flock2d * flock);
	
	Boid2d * setLoc(float lx, float ly) {
		x = lx;
		y = ly;
		return this;
	}
////// set Valeurs alex
    Boid2d * setValALex(float lx, float ly,
                        float lsepa,float lalig, float lcohe,
                        float ldistSepa,float ldistAlig, float ldistCohe,
                        float lmaxSpeed, float lmaxForce,
                        float lattraction, float lattractiondeviation,
                        int lgroup) {
        x = lx;
        y = ly;
        separateAlex = lsepa;
        alignAlex = lalig;
        cohesionAlex = lcohe;
        distSeparationAlex = ldistSepa;
        distAlignAlex = ldistAlig;
        distCohesionAlex= ldistCohe;
        maxSpeedAlex = lmaxSpeed;
        maxForceAlex = lmaxForce;
        attractionAlex = lattraction;
        attractiondeviationAlex = lattractiondeviation;
        group = lgroup;
        return this;
    }
////// fin set Valeurs alex


	Boid2d * setVel(float velx, float vely) {
		vx = velx;
		vy = vely;
		return this;
	}
	
	void bounds();
	
	/*
	 * main funcs
	 */
	
	void update(const float amount);		
    void updateAlex(const float amount);
    
	float* flock(const float amount, float *vec) ;
	
	
	float* steer(float* target, float amount);// , float *steervec);
	
	float* cohesion( float *vec);	
	float* align( float *vec) ;		
	float* separate( float *vec) ;
	
	
	
	
	/*
	 * integration of all forces in single eq now with attraction points builtin
	 */
	
	float* flockfull(const float amount, float *vec) ;
    float* flockfullAlex(const float amount, float *vec);
		
};
