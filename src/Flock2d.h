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
 * 
 * @author      Andre Sier 
 * @modified    20130225
 * @version     0.0.7a
 * @url			http://s373.net/code/boids
 */


#pragma once

#include "ofMain.h"
#include "Boid2d.h"
#include "AttractionPoint2d.h"
#include "GroupBoids2d.h"

class Flock2d {
public:
	
	//vector <Boid2d *>				boids;
	vector <AttractionPoint2d *>	attractionPoints;
    vector< AttractionLine2d *>     attractionLines;
    vector <GroupBoid2d *>          groupBoid;


	// bounds
	float minX, minY, maxX, maxY, boundsWidth, boundsHeight;
	int boundmode;
	
	// new
	float dt;
	float attraction, attractiondeviation;

	Flock2d(){
		//clear();
        minX = maxX = maxY = boundsWidth = boundsHeight = 0;
		boundmode = 0;
		dt = 1.0f;
		attraction = attractiondeviation = 0.0f;
	}

    void clear(){
        clearGroups();
        clearAttrPts();
    
    
    }
    
    void clearGroups(){
        while (groupBoid.size()>0) {
            delete groupBoid[0];
            groupBoid.erase(groupBoid.begin());
        }
    }
	
	/// modif a faire pour ligne
	void clearAttrPts(){
		while(attractionPoints.size()>0){
			delete attractionPoints[0];
			attractionPoints.erase(attractionPoints.begin());
		}
		
	}
    void addGoup(){
        GroupBoid2d * g = new GroupBoid2d();
        groupBoid.push_back(g);
    }
    
    void addBoid(int _numGroup){
        GroupBoid2d * g = groupBoid.at(_numGroup);
        Boid2d * b = new Boid2d();
        g->boids.push_back(b);
    }
    
    void changeValeurBoidsGroup(int _numGroup ){
        GroupBoid2d * g = groupBoid.at(_numGroup);
        for (int i=0; i<g->boids.size(); i++) {
            
        }
    }
    void addBoidGroup(int _numGroup, ofVec2f _position,float _sepa, float _distSepa, float _cohe, float _distCohe, float _alig, float _distAlig, float _maxForce, float _maxSpeed){
        GroupBoid2d * g = groupBoid.at(_numGroup);
        Boid2d * b = new Boid2d(this);
        b->setLoc(_position);
        b->setValSepa(_sepa, _distSepa);
        b->setValCohe(_cohe, _distCohe);
        b->setValAlig(_alig, _distAlig);
        b->setMaxForce(_maxForce);
        b->setMaxSpeed(_maxSpeed);
        b->setGroup(_numGroup);
        g->boids.push_back(b);
    }
    
    void initGoup(int num, ofVec2f _position, float dev, float _sepa, float _alig, float _cohe, float _distSepa, float _distAlig, float _distCohe, float _maxSpeed, float _maxForce, float _attraction, float _attractiondeviation, int _group){
        
        GroupBoid2d * b = new GroupBoid2d(); // this
        b->init(num, _position, dev, _sepa, _alig, _cohe, _distSepa, _distAlig, _distCohe, _maxSpeed,_maxForce, _attraction, _attractiondeviation, _group);
        
        
        groupBoid.push_back(b);
        updateRegle();
    
    }
    
    int getNumGroups(){
        return groupBoid.size();
    }
    
    int getNumBoids(){
        int groupsSize = groupBoid.size();
        int boids = 0;
        for (int i=0; i<groupsSize; i++) {
            boids += groupBoid[i]->getNumBoids();
        }
    }
    
    void update() {
        int groupsSize = groupBoid.size();
        for (int i = 0; i < groupsSize; i++) {
            groupBoid[i]->update(dt);
        }
    }
    
///////////////////////////////// Bounds //////////////////////////////////
    Flock2d * setBounds(float minx, float miny, float maxx, float maxy) {
        minX = minx;
        minY = miny;
        maxX = maxx;
        maxY = maxy;
        boundsWidth = maxX - minX;
        boundsHeight = maxY - minY;
        
        return this;
    }
    
    int getBoundmode() {
        return boundmode;
    }
    
    
    Flock2d * setBoundmode(int boundmode) {
        this->boundmode = boundmode;
        return this;
    }
    
    
    
    bool hasAttractionPoints() {
        return attractionPoints.size() > 0;
    }
    
    bool hasAttractionLines() {
        return attractionLines.size() > 0;
    }
    
    

    
    
private:
    
    void updateRegle(){
        for (int i=0; i<groupBoid.size(); i++) {
            GroupBoid2d *g = groupBoid[i];
            if(g->getNumRegle()==groupBoid.size()){
                continue;
            }
            while (g->getNumRegle()<groupBoid.size()) {
                g->initVectorRegleDefault(g->getNumRegle()); // +1 ?
            }
        }
    
    }


    
    
/*
	
	Flock2d * setup(int num, float lx, float ly) {
		return setup(num, lx, ly, 1);
	}

	Flock2d * setup(int num, float lx, float ly, float dev) {
		//init(num, lx, ly, dev);
		return this;
	}
/////////////////////////////////////////////// initAlex
    void initA(int num,
               ofVec2f _position, float dev,
               float _sepa,float _alig, float _cohe,
               float _distSepa, float _distAlig, float _distCohe,
               float _maxSpeed, float _maxForce,
               float _attraction, float _attractiondeviation,
               int _group) {
        
        for (int i = 0; i < num; i++) {
            _position.x += ofRandom(-dev, dev);
            _position.y += ofRandom(-dev, dev);
            Boid2d * b = new Boid2d(this);
            // need to be scattered or else no work
            b->setValTotal(_position,
                          _sepa,
                          _alig,
                          _cohe,
                          _distSepa,
                          _distAlig,
                          _distCohe,
                          _maxSpeed,
                          _maxForce,
                          _attraction,
                          _attractiondeviation,
                          _group);
           
            boids.push_back(b);
        }
        
    }
//////////////////////////////////////////
    
///////// ici ///////
	void init(int num, float lx, float ly, float dev) {

		for (int i = 0; i < num; i++) {
			Boid2d * b = new Boid2d(this);
			// need to be scattered or else no work
			b->setLoc(lx + ofRandom(-dev, dev),
					ly + ofRandom(-dev, dev));
			// b.setLoc(lx, ly);
//			boids.add(b);
			boids.push_back(b);
		}

		defaultValues();

	}
/////// ici ////
	void defaultValues() {
		boundmode = 1;
		separate = 20.0f;
		align = 12.0f;
		cohesion = 3.0f;
		distSeparation = 10.0f;
		distAlign = 20.0f;
		distCohesion = 25.0f;
		// maxTurn, maxSpeed, maxForce;
		maxSpeed = 2.f;
		maxForce = 10.0f;
		attraction = 100.5f;
		attractiondeviation =0.0f;
		
		// minX = 0; minY = 0; maxX = 700; maxY, boundsWidth, boundsHeight;
		setBounds(0, 0, 700, 700);
	}

	// metodos

	Flock2d * add(float lx, float ly) {
		Boid2d * b = new Boid2d();//(this); // first constructor is zeroing nicely
		b->setFlock(this);
		
		//b->setLoc(lx, ly);
		
		b->attr = attraction + ofRandom(-attractiondeviation, attractiondeviation);
		
		boids.push_back(b);
		return this;
	}

	
	Flock2d * setDt(const float d){
		dt = d;
		return this;
	}
	
	
	
	Flock2d * setMaxTurn(float mt) {
		maxTurn = mt;
		return this;
	}

	Flock2d * setMaxSpeed(float ms) {
		maxSpeed = ms;
		return this;
	}

	Flock2d * setMaxForce(float mf) {
		maxForce = mf;
		return this;
	}
	Flock2d * setAttraction(float mf) {
		attraction = mf;
		doAttraction();
		return this;
	}
	Flock2d * setAttractionDev(float mf) {
		attractiondeviation = mf;
		doAttraction();
		return this;
	}
	
	void doAttraction(){
		for(int i=0; i<boids.size(); i++){
			boids[i]->attr = attraction + ofRandom(-attractiondeviation, attractiondeviation);
		}
	}
	
	
	float getMaxTurn() {
		return maxTurn;
	}

	float getMaxSpeed() {
		return maxSpeed;
	}

	float getMaxForce() {
		return maxForce;
	}

	float getSeparate() {
		return separate;
	}

	Flock2d * setSeparate(float forceSeparate) {
		this->separate = forceSeparate;
		return this;
	}

	Flock2d * setAlign(float forceAlign) {
		this->align = forceAlign;
		return this;
	}

	Flock2d * setCohesion(float forceCohesion) {
		this->cohesion = forceCohesion;
		return this;
	}

	float getAlign() {
		return align;
	}

	float getCohesion() {
		return cohesion;
	}

	
	float getSeparation() {
		return distSeparation;
	}

	
	float getDistAlign() {
		return distAlign;
	}

	
	float getDistCohesion() {
		return distCohesion;
	}

	
	Flock2d * setDistSeparation(float distSeparation) {
		this->distSeparation = distSeparation;
		return this;
	}

	Flock2d * setDistAlign(float d) {
		distAlign = d;
		return this;
	}


	Flock2d * setDistCohesion(float d) {
		distCohesion = d;
		return this;
	}


	Flock2d * setBounds(float minx, float miny, float maxx, float maxy) {
		minX = minx;
		minY = miny;
		maxX = maxx;
		maxY = maxy;
		boundsWidth = maxX - minX;
		boundsHeight = maxY - minY;

		return this;
	}


	int getBoundmode() {
		return boundmode;
	}


	Flock2d * setBoundmode(int boundmode) {
		this->boundmode = boundmode;
		return this;
	}

	void update() {
		int boidsSize = boids.size();
		for (int i = 0; i < boidsSize; i++) {
//			Boid2d *b = boids.get(i);
			boids[i]->update(dt);
		}
	}

	// public void interfere(Flock2d otherFlock, float amount) {
	//
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid2d b = boids.get(i);
	// b.update(amount);
	// }
	// }

	// public void set() {
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid2d b = boids.get(i);
	// b.setFlock(this);
	// }
	// }

	int size() {
		return boids.size();
	}

	Boid2d * get(int idx) {
		return boids.at(idx);
	}

	// / attraction points

	Flock2d * addAttractionPoint(float x, float y, float force,
			float sensorDist) {
		AttractionPoint2d * ap = new AttractionPoint2d(x, y, force, sensorDist);
		attractionPoints.push_back(ap);
		return this;
	}

	vector<AttractionPoint2d*>* getAttractionPoints() {
		return &attractionPoints;
	}



	void changeAttractionPoint(int id, float x, float y, float force,
			float sensorDist) {
//		try {
		
		AttractionPoint2d * ap = attractionPoints[id];//.get(id);
		if(ap!=NULL){
			ap->x = x;
			ap->y = y;
			ap->force = force;
			ap->sensorDist = sensorDist;
		} else {
			cout << " attraction point null at id: " << id << endl;
		}

	}
	
    void changeAttractionLine2d( int id, float _x){
        AttractionLine2d * al = attractionLines[id];
        
        
        
    }
	
	
	

	
	
	void removeFirstBoid(){
		if(boids.size()>0){
			delete boids[0];
			boids.erase(boids.begin());
		}
	}
	void removeLastBoid(){
		if(boids.size()>0){
			delete boids[boids.size()-1];
			boids.erase(boids.end()-1);
		}
	}
	
	
	void removeBoid(int idx){
		if(boids.size()>idx){
			delete boids[idx];
			boids.erase(boids.begin()+idx);
		}
	}
*/

	
};