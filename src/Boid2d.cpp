/*
 *  Boid2d.cpp
 *
 *  Created by andrÃ© sier on 20130225.
 *  Copyright 2013 s373.net/x. All rights reserved.
 *
 */
#include "Boid2d.h"
#include "Flock2d.h"


Boid2d::Boid2d(Flock2d * flock) {
		Boid2d();
	this->flockPtr = flock;
	
}


Boid2d * Boid2d::setFlock(Flock2d * flock) {
	this->flockPtr = flock;
	return this;
}




void Boid2d::bounds() {
	switch (flockPtr->boundmode) {
		case 0: // CLAMP
			if (position.x < flockPtr->minX) {
				position.x = flockPtr->minX;
				velocite.x = -velocite.x;
			}
			if (position.x > flockPtr->maxX) {
				position.x = flockPtr->maxX;
				velocite.x = -velocite.x;
			}
			if (position.y < flockPtr->minY) {
				position.y = flockPtr->minY;
				velocite.y = -velocite.y;
			}
			if (position.y > flockPtr->maxY) {
				position.y = flockPtr->maxY;
				velocite.y = -velocite.y;
			}
			break;
		case 1: // WRAP
			if (position.x < flockPtr->minX) {
				position.x+= flockPtr->boundsWidth;
			}
			if (position.x > flockPtr->maxX) {
				position.x -= flockPtr->boundsWidth;
			}
			if (position.y < flockPtr->minY) {
				position.y += flockPtr->boundsHeight;
			}
			if (position.y > flockPtr->maxY) {
				position.y -= flockPtr->boundsHeight;
			}
			break;
	}
	
}


void Boid2d::boudsColision(){
    if (0==0) {
        
        //// ATENTION CODE FAUT !!!
        //// faire code de colission en !! 0==0
        
        this->position.x=-this->position.x;
        this->velocite.y=-this->velocite.y;
    
    }

}


float* Boid2d::steer(float* target, float amount){ //, float *steervec) {
	
//	float steer[] = {0.f, 0.f}; //new float[2];
//	float *dir =new float[2];
	float dir[2] = {0.f,0.f};
//	dir[0] = 0.0f;
//	dir[1] = 0.0f;
	
	
	dir[0] = target[0] - position.x;
	dir[1] = target[1] - position.y;
	float d = ABS(dir[0]) + ABS(dir[1]);
	
	if (d > 2) {
		float invDist = 1.f / d;
		dir[0] *= invDist;
		dir[1] *= invDist;
		// steer, desired - vel
		target[0] = dir[0] - velocite.x;
		target[1] = dir[1] - velocite.y;
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
    std::srand(std::time(0));
    // float vec[] = flock(amount);// flockfull(amount);
    //float * vec = flockfull(amount);
    
    // reset acc on begin 2 draw
    acceleration.x = 0;
    acceleration.y = 0;
    
    
    float *vec = new float[2];
    vec[0] = 0.0f;
    vec[1] = 0.0f;
    
    //	flock(amount, vec);
    flockfull(amount, vec);
    
    acceleration.x += vec[0];// *amount;
    acceleration.y += vec[1];// *amount;
    
    delete [] vec;
    
    // change this to allow flock flock interaction
    // accX = vec[0];
    // accY = vec[1];
    
    // limit force
    float distMaxForce = ABS(acceleration.x) + ABS(acceleration.y);
    if (distMaxForce > maxForceAlex) {
        distMaxForce = maxForceAlex / distMaxForce;
        acceleration *= distMaxForce;
    }
    
    //vx += ax + (rand()%200 -100)/100 * 1.5;
    //vy += ay + (rand()%200 -100)/100 * 1.5;


    velocite += acceleration;
    // limit speed
    
    
    float distMaxSpeed = ABS(velocite.x) + ABS(velocite.y);
    if (distMaxSpeed > maxSpeedAlex) {
        distMaxSpeed = maxSpeedAlex / distMaxSpeed;
        velocite *= distMaxSpeed;

    }
    
    position += velocite *amount;
    
    //x += ((rand()%200)-100)/100 * 5;
    //y += ((rand()%200)-100)/100 * 5;
    
    
    
    
    bounds();
    
    // reset acc on end
    //	ax = 0;
    //	ay = 0;
}


/////////// code alex flockfull /////////////////

float* Boid2d::flockfull(const float amount, float *vec) {
    //	float * vec = new float[2];
    
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
            Boid2d * other = group->boids.at(numBoids);
        
            
            float separatedist = other->distSeparationGroup;
            float aligndist = other->distAlignGroup;
            float cohesiondist = other->distCohesionGroup;
            
            float dx = other->position.x - position.x;
            float dy = other->position.y - position.y;
            float d = ABS(dx) + ABS(dy);
            if (d <= 1e-7)
                continue;
            
            invD = 1.f / d;
            
            if (other->group==this->group) {
                // sep
                if (d < separatedist) {
                    countsep++;
                    foncSep(dx, dy, invD, other,sep);
                }
                
                
                // coh
                if (d < cohesiondist) {
                    countcoh++;
                    if (other->lead) {
                        /// a modif
                        foncCohe(d, 20.0, other, coh);
                        cout << " I am a leader !!! "<< endl;
                    }
                    else{
                        foncCohe(d, 1.0 , other, coh);
                    }
                }
                
                // ali
                if (d < aligndist) {
                    countali++;
                    foncAlig(other, ali);
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
                
                float dx = point->x - position.x;
                float dy = point->y - position.y;
                float d = ABS(dx) + ABS(dy);
                if (d <= 1e-7)
                    continue;
                if (d > point->sensorDist)
                    continue;
                
                // inbounds, calc
                float invForce = point->force  / d  * attr;// newww   ////flockPtr->attraction     ; // neww
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
                AP[0] = position.x - line->a[0];
                AP[1] = position.y - line->a[1];
                float ti = ( line->u[0] * AP[0] + line->u[1] * AP[1])/( line->u[0] * line->u[0] + line->u[1] * line->u[1]);
                AP[0] = line->a[0] + ti * line->u[0];
                AP[1] = line->a[1] + ti * line->u[1];
                
                float dx = AP[0] - position.x;
                float dy = AP[1] - position.y;
                float d = ABS(dx) + ABS(dy);
                
                
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

        
        
float * Boid2d::foncSep(const float dx, const float dy, const float invD, Boid2d *other, float *sep){
    sep[0] -= dx * invD * other->separateGroup;
    sep[1] -= dy * invD * other->separateGroup;
    return sep;
}

float * Boid2d::foncCohe(const float d, const float variable,Boid2d *other, float *coh){
    coh[0] += other->position.x * other->cohesionGroup * d/variable;
    coh[1] += other->position.y * other->cohesionGroup * d/variable;
    return coh;
}

float * Boid2d::foncAlig(Boid2d *other, float *ali){
    ali[0] += other->velocite.x * other->alignGroup;
    ali[1] += other->velocite.y * other->alignGroup;
    return ali;
}

