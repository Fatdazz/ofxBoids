#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableAlphaBlending();
    
    // make attrPts
    /*
    for(int i=0; i<10; i++) {
        float x = ofRandom(ofGetWidth());
        float y = ofRandom(ofGetHeight());
        float force = ofRandom(-250,250);
        float dist = ofRandom(100,200);
        flock.addAttractionPoint(x,y,force,dist);
    }
    */
    // num, center x, center y, dev
    
    //flock.addAttractionPoint(ofGetWidth()/4, ofGetHeight()/4, 1000, 50);
    //flock.addAttractionPoint(3* ofGetWidth()/4, ofGetHeight()/4, 1000, 50);
    //flock.addAttractionPoint(ofGetWidth()/4, 3* ofGetHeight()/4, 1000, 50);
    //flock.addAttractionPoint(3* ofGetWidth()/4, 3*ofGetHeight()/4, -100, 50);

    //flock.setup(100, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4 );
    flock.initA(100,
                ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4,
                10.0f, 12.0f, 10.0f,
                5.0f, 20.0f, 50.0f,
                2.5f, 1.5f,
                100.0f, 0.0f,
                0);
    flock.initA(100,
               ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4,
               20.0f, 12.0f, 3.0f,
               10.0f, 20.0f, 25.0f,
               2.0f, 1.5f,
               100.0f, 0.0f,
               1);
    
    
    flock.setBounds(0,0,ofGetWidth(), ofGetHeight());
    flock.setBoundmode(1);
    
    gui.setup("panel");
    gui.add(separate.set("separate", 20.0, 0, 100));
    gui.add(align.set("align", 12, 0, 100));
    gui.add(cohesion.set("cohesion", 3, 0, 100));
   
    gui.add(distSeparation.set("distSeparation", 10, 0, 100));
    gui.add(distAlign.set("distAlign", 20, 0, 100));
    gui.add(distCohesion.set("distCohesion", 25, 0, 100));
   
    gui.add(maxSpeed.set("maxSpeed", 2, 0, 8));
    gui.add(maxForce.set("maxForce", 10, 0, 100));
    
    gui.add(attraction.set("attraction", 100, 0, 500));
    gui.add(attractiondeviation.set("attractiondeviation", 3, 0, 100));

    
  
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    flock.setSeparate(separate);
    flock.setAlign(align);
    flock.setCohesion(cohesion);
    
    flock.setDistSeparation(distSeparation);
    flock.setDistAlign(distAlign);
    flock.setDistCohesion(distCohesion);
    
    flock.setMaxSpeed(maxSpeed);
    flock.setMaxForce(maxForce);
    
    flock.setAttraction(attraction);
    flock.setAttractionDev(attractiondeviation);
    
    flock.update();
    

    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    gui.draw();
    //view attrpoints
    ofColor attrColor(100,255,0);
    ofColor repelColor(255,128,0);
    
    for(int i=0; i<flock.attractionPoints.size(); i++){
        AttractionPoint2d * ap = flock.attractionPoints[i];
        ofSetColor( ap->force > 0 ? attrColor : repelColor, ofMap(ABS(ap->force), 0, 250, 10, 200));
        ofRect(ap->x -ap->sensorDist/2, ap->y -ap->sensorDist/2, ap->sensorDist, ap->sensorDist);
        ofRect(ap->x-2, ap->y-2, 5, 5);
    }
    
    
    ofSetColor(0);
    for(int i=0; i<flock.boids.size(); i++){
        Boid2d * b = flock.boids[i];
        if (b->group==1) {
            ofSetColor(255, 0, 0);
        }
        
        ofRect(b->x, b->y, 5,5);
        float lm = 10.f;
        ofLine(b->x, b->y, b->x + b->vx*lm, b->y + b->vy*lm);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='a') {
        for (int i=0; i<flock.boids.size(); i++) {
            Boid2d * lulu=flock.boids[i];
            if (lulu->group==0) {
                
                lulu->separateGroup=separate;
                lulu->alignGroup=align;
                lulu->cohesionGroup=cohesion;
                
                lulu->distAlignGroup=distAlign;
                lulu->distCohesionGroup=distCohesion;
                lulu->distSeparationGroup=distSeparation;
                
                lulu->maxForceAlex=maxForce;
                lulu->maxSpeedAlex=maxSpeed;
                
                lulu->attractionAlex=attraction;
                lulu->attractiondeviationAlex=attractiondeviation;
            }
        }
    }
    
    if (key=='b') {
        for (int i=0; i<flock.boids.size(); i++) {
            Boid2d * lulu=flock.boids[i];
            if (lulu->group==1) {
                
                lulu->separateGroup=separate;
                lulu->alignGroup=align;
                lulu->cohesionGroup=cohesion;
                
                lulu->distAlignGroup=distAlign;
                lulu->distCohesionGroup=distCohesion;
                lulu->distSeparationGroup=distSeparation;
                
                lulu->maxForceAlex=maxForce;
                lulu->maxSpeedAlex=maxSpeed;
                
                lulu->attractionAlex=attraction;
                lulu->attractiondeviationAlex=attractiondeviation;
            }
        }
    }

    
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
