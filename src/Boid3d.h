/*
 *  Boid3d.h
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

class Flock3d;

class Boid3d {
public:
	
	float x, y, z, vx, vy, vz,  ax, ay, az;
	int life;
	
	float attr;
	
	Flock3d * flockPtr;
	
	// public Team team;
	// public int om;
	// public float forceSeparate, forceAlign, forceCohesion;
	// public float maxTurn, maxSpeed, maxForce;
	
	Boid3d() {
		x = y = z = vz = az = vx = vy = ax = ay = 0.0f;
		life = 0;
		flockPtr = NULL;
		attr = 0.0f;
	}
	
	Boid3d(Flock3d * flock);
	
	Boid3d * setFlock(Flock3d * flock);
	
	Boid3d * setLoc(float lx, float ly, float lz) {
		x = lx;
		y = ly;
		z = lz;
		return this;
	}
	
	Boid3d * setVel(float velx, float vely, float velz) {
		vx = velx;
		vy = vely;
		vz = velz;
		return this;
	}
	
	void bounds();
	
	/*
	 * main funcs
	 */
	
	void update(const float amount);		
	
	float* flock(const float amount, float *vec) ;
	
	
	float* steer(float* target, float amount);//   , float *steervec);
	
	//	float* cohesion(vector<Boid3d*>* b, float *vec);
	//	
	//	float* align(vector<Boid3d*>* b, float *vec) ;	
	//	
	//	float* separate(vector<Boid3d*>* b, float *vec) ;
	
	float* cohesion( float *vec);	
	float* align( float *vec) ;		
	float* separate( float *vec) ;
	
	
	
	
	/*
	 * integration of all forces in single eq now with attraction points builtin
	 */
	
	float* flockfull(const float amount, float *vec) ;	
	
};
