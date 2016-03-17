/*
 *  Boid2d.cpp
 *
 *  Created by andrÃ© sier on 20130225.
 *  Copyright 2013 s373.net/x. All rights reserved.
 *
 */
#include "Boid2d.h"
#include "Flock2d.h"
//#include "ofMain.h"

Boid2d::Boid2d(Flock2d * _flock, GroupBoid2d * _group) : Boid2d() {
	flockPtr = _flock;
    groupPtr = _group;
}

void Boid2d::setFlock(Flock2d * flock) {
	flockPtr = flock;
}

void Boid2d::bounds() {
	switch (flockPtr->boundmode) {
		case 0: // CLAMP
			if (position[0] < flockPtr->minX) {
				position[0] = flockPtr->minX;
				position[0] = -velocite[0];
			}
			if (position[0] > flockPtr->maxX) {
				position[0] = flockPtr->maxX;
				position[0] = -velocite[0] ;
			}
			if (position[1] < flockPtr->minY) {
				position[1] = flockPtr->minY;
				velocite[1] = -velocite[1];
			}
			if (position[1] > flockPtr->maxY) {
				position[1] = flockPtr->maxY;
				position[1] = -position[1];
			}
			break;
		case 1: // WRAP
			if (position[0] < flockPtr->minX) {
				position[0] += flockPtr->boundsWidth;
			}
			if (position[0] > flockPtr->maxX) {
				position[0] -= flockPtr->boundsWidth;
			}
			if (position[1] < flockPtr->minY) {
				position[1] += flockPtr->boundsHeight;
			}
			if (position[1] > flockPtr->maxY) {
				position[1] -= flockPtr->boundsHeight;
			}
			break;
	}
	
}


void Boid2d::boundsColision(){
    if (0==0) {
        
        //// ATENTION CODE FAUT !!!
        //// faire code de colission en !! 0==0
        
        position[0] = - position[0];
        velocite[1] = - velocite[1];
    
    }

}


float* Boid2d::steer(float* target, float amount){ //, float *steervec) {
	
//	float steer[] = {0.f, 0.f}; //new float[2];
//	float *dir =new float[2];
	float dir[2] = {0.f,0.f};
//	dir[0] = 0.0f;
//	dir[1] = 0.0f;
	
	
	dir[0] = target[0] - position[0];
	dir[1] = target[1] - position[1];
	float d = ABS(dir[0]) + ABS(dir[1]);
	
	if (d > 2) {
		float invDist = 1.f / d;
		dir[0] *= invDist;
		dir[1] *= invDist;
		// steer, desired - vel
		target[0] = dir[0] - velocite[0];
		target[1] = dir[1] - velocite[1];
		float steerLen = ABS(target[0]) + ABS(target[1]);
		if (steerLen > 0) {
			float invSteerLen = amount / steerLen;// 1f / steerLen;
			target[0] *= invSteerLen;
			target[1] *= invSteerLen;
		}
	}
	
//	delete [] dir;
	
	return target;
	
}


//////////////////// code Alex update /////////////////

void Boid2d:: update(const float amount) {
    
    // float vec[] = flock(amount);// flockfull(amount);
    //float * vec = flockfull(amount);
    
    // reset acc on begin 2 draw
    acceleration[0] = 0;
    acceleration[1] = 0;
    
    
    float *vec = new float[2];
    vec[0] = 0.0f;
    vec[1] = 0.0f;
    
    //	flock(amount, vec);
    flockfull(amount, vec);
    
    acceleration[0] += vec[0];// *amount;
    acceleration[1] += vec[1];// *amount;
    
    delete [] vec;
    
    // change this to allow flock flock interaction
    // accX = vec[0];
    // accY = vec[1];
    
    // limit force
    float distMaxForce = abs(acceleration[0]) + abs(acceleration[1]);
    if (distMaxForce > maxForceAlex) {
        distMaxForce = maxForceAlex / distMaxForce;
        acceleration[0] *= distMaxForce;
		acceleration[1] *= distMaxForce;
    }
    
    //vx += ax + (rand()%200 -100)/100 * 1.5;
    //vy += ay + (rand()%200 -100)/100 * 1.5;


    velocite[0] += acceleration[0];
	velocite[1] += acceleration[1];
    
    
    float distMaxSpeed = abs(velocite[0]) + abs(velocite[1]);
    if (distMaxSpeed > maxSpeedAlex) {
        distMaxSpeed = maxSpeedAlex / distMaxSpeed;
        velocite[0] *= distMaxSpeed;
		velocite[1] *= distMaxSpeed;

    }
    
    position[0] += velocite[0] * amount;
	position[1] += velocite[1] * amount;
    
    //x += ((rand()%200)-100)/100 * 5;
    //y += ((rand()%200)-100)/100 * 5;
    
    bounds();
}


float* Boid2d::flockfull(const float amount, float *vec) {
    
    float *sep = new float[2];
    float *ali = new float[2];
    float *coh = new float[2];
    float *attrForce = new float[2];
    
    sep[0] = 0.0f;
    sep[1] = 0.0f;
    ali[0] = 0.0f;
    ali[1] = 0.0f;
    coh[0] = 0.0f;
    coh[1] = 0.0f;
    attrForce[0] = 0.0f;
    attrForce[1] = 0.0f;
    
    
    
    //	float attrForce[] = {0.f, 0.f}; //new float[2];
    int countsep = 0, countali = 0, countcoh = 0;
    

    float invD = 0;
    
    // boolean hasAttractionPoints = flock.hasAttractionPoints();
    
    // main full loop track all forces boid other boids
    
    for (int numGroup=0; numGroup < flockPtr->getNumGroups(); numGroup++) {
        GroupBoid2d * group = flockPtr->groupBoid.at(numGroup);
    
        for (int numBoids=0; numBoids < group->boids.size() ; numBoids ++) {
            Boid2d other = group->boids.at(numBoids);
        
            
            float separatedist = other.distSeparationGroup;
            float aligndist = other.distAlignGroup;
            float cohesiondist = other.distCohesionGroup;
            
            float dx = other.position[0] - position[0];
            float dy = other.position[1] - position[1];
            float d = abs(dx) + abs(dy);
            if (d <= 1e-7)
                continue;
            
            invD = 1.f / d;
            
            if (other.group == groupPtr->id) {
                if (d < separatedist) {
                    countsep++;
                    separate(dx, dy, invD, other,sep);
                }
                
                if (d < cohesiondist) {
                    countcoh++;
                    if (other.lead) {
                        /// a modif
                        cohesion(d, 20.0, other, coh);
                        cout << " I am a leader !!! "<< endl;
                    }
                    else{
                        cohesion(d, 1.0 , other, coh);
                    }
                }
                
                // ali
                if (d < aligndist) {
                    countali++;
                    align(other, ali);
                }
            }
            
            /*      ///////// regle des autre groupe a faire !! :-)
             else if (other->group==!group){
             if (d < distSeparationNoGroup ) {
             countsep++;
             invD = 1.f / d;
             sep[0] -= dx * invD * separateNoGroup;
             sep[1] -= dy * invD * separateNoGroup;
             
             }
             if (d < distAlignNoGroup) {
             countali++;
             ali[0] -= other->velocite.x * alignNoGroup;
             ali[1] -= other->velocite.y * alignNoGroup;
             
             }
             }
             */
        }
    }
    
        if (countsep > 0) {
            const float invForSep = 1 / (float) countsep; // faire invForsep une moyenne
            sep[0] *= invForSep;
            sep[1] *= invForSep;
        }
        if (countali > 0) {
            // final float invForAli = 1f / (float) countali;
            const float invForAli = 1 / (float) countali;
            ali[0] *= invForAli;
            ali[1] *= invForAli;
        }
        if (countcoh > 0) {
            const float invForCoh = 1 / (float) countcoh;
            coh[0] *= invForCoh;
            coh[1] *= invForCoh;
            coh = steer(coh, 1);
        }
        
        // if using extra forces, place here
        
        // sep[0] *= flock.separate;
        // sep[1] *= flock.separate;
        //
        // ali[0] *= flock.align;
        // ali[1] *= flock.align;
        //
        // coh[0] *= flock.cohesion;
        // coh[1] *= flock.cohesion;
        
        
        
        // other forces
        if (flockPtr->hasAttractionPoints()) {
            for (int i = 0; i < flockPtr->attractionPoints.size(); i++) {
                AttractionPoint2d * point = flockPtr->attractionPoints.at(i);
                
                float dx = point->x - position[0];
                float dy = point->y - position[1];
                float d = ABS(dx) + ABS(dy);
                if (d <= 1e-7)
                    continue;
                if (d > point->sensorDist)
                    continue;
                
                // inbounds, calc
                float invForce = point->force  / d  * attr;// neww   ////flockPtr->attraction     ; // neww
                dx *= invForce;
                dy *= invForce;
                
                attrForce[0] += dx;
                attrForce[1] += dy;
            }
            
        }
        
        // attraction en linge a testŽ
        if (flockPtr->hasAttractionLines()) {
            for (int i=0; i<flockPtr->attractionLines.size(); i++) {
                AttractionLine2d * line =flockPtr->attractionLines.at(i);
                
                float AP[2];
                AP[0] = position[0] - line->a[0];
                AP[1] = position[1] - line->a[1];
                float ti = ( line->u[0] * AP[0] + line->u[1] * AP[1])/( line->u[0] * line->u[0] + line->u[1] * line->u[1]);
                AP[0] = line->a[0] + ti * line->u[0];
                AP[1] = line->a[1] + ti * line->u[1];
                
                float dx = AP[0] - position[0];
                float dy = AP[1] - position[1];
                float d = abs(dx) + abs(dy);
                
                
                if (d <= 1e-7)
                    continue;
                if (d > line->sensorDist)
                    continue;
                
                float invForce = line->force  / d  * attr;// newww   ////flockPtr->attraction     ; // neww
                dx *= invForce;
                dy *= invForce;
                
                attrForce[0] += dx;
                attrForce[1] += dy;
        }
    }
    

        

        
   ///////////////////////////////
    vec[0] = sep[0] + ali[0] + coh[0] + attrForce[0];
    vec[1] = sep[1] + ali[1] + coh[1] + attrForce[1];
    const float d = ABS(vec[0]) + ABS(vec[1]);
    if (d > 0) {
        float invDist = amount / d;
        vec[0] *= invDist;
        vec[1] *= invDist;
    }
    
    
    
    vec[0] *= amount;
    vec[1] *= amount;
    
    
    delete[] sep;
    delete[] ali;
    delete[] coh;	
    delete[] attrForce;
    
    
    return vec;
}

        
        
void Boid2d::separate(const float dx, const float dy, const float invD, Boid2d& other, float *sep){
    sep[0] -= dx * invD * other.separateGroup * ofRandom(-5, 15);
    sep[1] -= dy * invD * other.separateGroup * ofRandom(-5, 15);
}

void Boid2d::cohesion(const float d, const float variable,Boid2d& other, float *coh){
    coh[0] += other.position[0] * other.cohesionGroup * d/variable;
    coh[1] += other.position[1] * other.cohesionGroup * d/variable;
}

void Boid2d::align(Boid2d& other, float *ali){
    ali[0] += other.velocite[0] * other.alignGroup;
    ali[1] += other.velocite[1] * other.alignGroup;
}

