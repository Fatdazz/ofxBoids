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
