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
        flock1.addAttractionPoint(x,y,force,dist);
    }
    */

    // num, center x, center y, dev
    /*
    flock1.addAttractionPoint(ofGetWidth()/4, ofGetHeight()/4, 1000, 50);
    flock1.addAttractionPoint(3* ofGetWidth()/4, ofGetHeight()/4, 1000, 50);
    flock1.addAttractionPoint(ofGetWidth()/4, 3* ofGetHeight()/4, 1000, 50);
    flock1.addAttractionPoint(3* ofGetWidth()/4, 3*ofGetHeight()/4, -100, 50);
	*/
    //flock.setup(100, ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4 );

	//	Flocks 1
	nbSubFlocks = 2;
	//	Sub Flock # 0
    flock1.initA(100,
                ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4,
                10.0f, 12.0f, 10.0f,
                5.0f, 20.0f, 50.0f,
                2.5f, 1.5f,
                100.0f, 0.0f,
                0);
	//	Sub Flock # 1
    flock1.initA(100,
               ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/4,
               20.0f, 12.0f, 3.0f,
               10.0f, 20.0f, 25.0f,
               2.0f, 1.5f,
               100.0f, 0.0f,
               1);
    
    
	//	Size of flock area of life
    flock1.setBounds(0,0,ofGetWidth(), ofGetHeight());
	//	Torus 2d space
    flock1.setBoundmode(1);
    
}

//--------------------------------------------------------------
void ofApp::update(){
	/*
	cout << "GUI separate1:"<<parametersGui->separate1 << endl ;
	cout << "GUI separate2:" << parametersGui->separate2 << endl;
	
	cout << "ofAPP separate1:" << flock1.boids[1]->separate << endl;
	cout << "ofAPP separate1:" << flock1.boids[51]->separate << endl;
	*/


	// Récuperation des parametres depuis GUI et Mise à jour du model
	for (int i = 0; i < flock1.boids.size(); i++)
	{
			if (flock1.boids[i]->group == 0) {

				flock1.boids[i]->setValAlig(parametersGui->align1, parametersGui->distAlign1);
				flock1.boids[i]->setValCohe(parametersGui->cohesion1, parametersGui->distCohesion1);
				flock1.boids[i]->setValSepa(parametersGui->separate1, parametersGui->distSeparation1);
				flock1.boids[i]->setMaxSpeed(parametersGui->maxSpeed1);
				flock1.boids[i]->setMaxForce(parametersGui->maxForce1);
				flock1.boids[i]->setValAttraction(parametersGui->attraction1, parametersGui->attractionDeviation1);

			}
			else if (flock1.boids[i]->group == 1) {

				flock1.boids[i]->setValAlig(parametersGui->align2, parametersGui->distAlign2);
				flock1.boids[i]->setValCohe(parametersGui->cohesion2, parametersGui->distCohesion2);
				flock1.boids[i]->setValSepa(parametersGui->separate2, parametersGui->distSeparation2);
				flock1.boids[i]->setMaxSpeed(parametersGui->maxSpeed2);
				flock1.boids[i]->setMaxForce(parametersGui->maxForce2);
				flock1.boids[i]->setValAttraction(parametersGui->attraction2, parametersGui->attractionDeviation2);
			
		}
	}

		//	ils faudrait itérer sur le groupe dans une double boucle pour le faire pour N groupe.
		/*
		flock1.setSeparate(parametersGui->boidsBehaviour[i].getFloat("separate"));
		flock1.setAlign(parametersGui->boidsBehaviour[i].getFloat("align"));
		flock1.setCohesion(parametersGui->boidsBehaviour[i].getFloat("cohesion"));

		flock1.setDistSeparation(parametersGui->boidsBehaviour[i].getFloat("distSeparation"));
		flock1.setDistAlign(parametersGui->boidsBehaviour[i].getFloat("distAlign"));
		flock1.setDistCohesion(parametersGui->boidsBehaviour[i].getFloat("distCohesion"));

		flock1.setMaxSpeed(parametersGui->boidsBehaviour[i].getFloat("maxSpeed"));
		flock1.setMaxForce(parametersGui->boidsBehaviour[i].getFloat("maxForce"));

		flock1.setAttraction(parametersGui->boidsBehaviour[i].getFloat("attraction"));
		flock1.setAttractionDev(parametersGui->boidsBehaviour[i].getFloat("attractiondeviation"));
		*/

		//	Applique les moddification de parametre et cacule les trajectoires
		flock1.update();
	}


//--------------------------------------------------------------
void ofApp::draw(){

	flockPanel.draw();
    //view attrpoints
    ofColor attrColor(100,255,0);
    ofColor repelColor(255,128,0);
    
    for(int i=0; i<flock1.attractionPoints.size(); i++){
        AttractionPoint2d * ap = flock1.attractionPoints[i];
        ofSetColor( ap->force > 0 ? attrColor : repelColor, ofMap(ABS(ap->force), 0, 250, 10, 200));
        ofRect(ap->x -ap->sensorDist/2, ap->y -ap->sensorDist/2, ap->sensorDist, ap->sensorDist);
        ofRect(ap->x-2, ap->y-2, 5, 5);
    }
    
    
    ofSetColor(0);
    for(int i=0; i<flock1.boids.size(); i++){
        Boid2d * b = flock1.boids[i];
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
	/*
    if (key=='a') {
        for (int i=0; i<flock1.boids.size(); i++) {
            Boid2d * lulu=flock1.boids[i];
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
        for (int i=0; i<flock1.boids.size(); i++) {
            Boid2d * lulu=flock1.boids[i];
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
	*/
    
    
    
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
