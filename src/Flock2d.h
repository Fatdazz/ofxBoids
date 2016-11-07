#pragma once
#include "ofMain.h"
#include "Boid2d.h"
#include "GroupBoids2d.h"
#define SegWidth 10
#define SegHeight 10


class Flock2d {
public:
    vector <GroupBoid2d *>          groupBoid;
    vector <Boid2d *>               totalBoid;
    vector <Boid2d *>               mapBoid[SegWidth][SegHeight];

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
    }
    
    void clearGroups(){
        while (groupBoid.size()>0) {
            delete groupBoid[0]; // il faut virŽ les Boid du group !!! ahahahahh
            groupBoid.erase(groupBoid.begin());
        }
    }
	
	/// modif a faire pour ligne
	
    
    void addBoid(){
        Boid2d * b = new Boid2d(this);
        totalBoid.push_back(b);
        
    }
    
    void addBoid(ofVec2f _position,float _sepa, float _distSepa, float _cohe, float _distCohe, float _alig, float _distAlig, float _maxForce, float _maxSpeed){
        Boid2d * b = new Boid2d(this);
        b->setLoc(_position);
        b->setValSepa(_sepa, _distSepa);
        b->setValCohe(_cohe, _distCohe);
        b->setValAlig(_alig, _distAlig);
        b->setMaxForce(_maxForce);
        b->setMaxSpeed(_maxSpeed);
        totalBoid.push_back(b);
    }
    void destroyBoidsGroups(){
    /// a faire ou pas
    }
    int getNumGroups(){

    }
    int getNumBoids(){
        return totalBoid.size();
    }
    
    void update(vector<Boid2d *> *vectorThis, vector<Boid2d *> *otherBoids ){
        for (int i=0; i< vectorThis->size(); i++) {
            vectorThis->at(i)->updateNew(dt, otherBoids);
        }
    }
    
    void updateSimple(){
        update(&totalBoid, &totalBoid);
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
///////////////////////////////// Attractions //////////////////////////////


private:

};