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



class AttractionLine2d {
public:
    float a[2],b[2],u[2];
    float force, sensorDist, lengthZone;
    int group;
    
    
    AttractionLine2d() {
        a[0] = a[1] = b[0] = b[1] = u[0] = u[1] = force = sensorDist =  0.0f;
        group=0;
    }
    
    void VecteurU(){
        u[0] = b[0] - a[0];
        u[1] = b[1] - a[1];
        
    }
    
    AttractionLine2d(float _a[2], float _b[2], float _force, float _sensorDist, float _lengthZone, int _group){
        a[0] = _a[0];
        a[1] = _a[1];
        b[0] = _b[0];
        b[1] = _b[1];
        force = _force;
        sensorDist = _sensorDist;
        lengthZone = _lengthZone;
        VecteurU();
        group = _group;
        
    }
    

    


    
    
    
};








class AttractionPoint2d {
public:
	
	float x, y, force, sensorDist;

	float halfDist;
	
	AttractionPoint2d() {
		x = y = force = sensorDist = halfDist = 0.0f;
	}

	AttractionPoint2d(float _x, float _y, float _f, float _sensor) {
		x = _x;
		y = _y;
		force = _f;
		sensorDist = _sensor;
		halfDist = sensorDist / 2.0f;
	}
	
	void draw(){
		ofRect(x-halfDist, y-halfDist, sensorDist, sensorDist);
		ofRect(x,y,3,3);
	}
	
	
};
