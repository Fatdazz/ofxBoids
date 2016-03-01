/*
* parametersGUI.cpp
*/

#include "parametersGUI.h"

void ParametersGUI::setup() {
	
	nbSubFlocks = 2;	// à faire une shared data
	float topMargin = 50.0;
	float leftMargin = 50.0;
	//
	parametersPanels.resize(nbSubFlocks);
	boidsBehaviour.resize(nbSubFlocks);

	//	Bequilles à faire disparaitre quand ofBoids sera itérable par groupe
	//	Groupe 1
	/*
	separate1.setName("Behaviour of Boids from Group 0");
	align1.add(separate.set("separate", 20.0, 0, 100));
	cohesion1;
	distSeparation1;
	distAlign1;
	distCohesion1;
	maxSpeed1;
	maxForce1;
	attraction1;
	attractiondeviation1;
	//	Groupe 2
	separate2.setName("Behaviour of Boids from Group 1");
	align2;
	cohesion2;
	distSeparation2;
	distAlign2;
	distCohesion2;
	maxSpeed2;
	maxForce2;
	attraction2;
	attractiondeviation2;
	*/
	//	Parameter for each group
	for (int i = 0; i < nbSubFlocks; i++)
	{
		
		float offset = i * 300.0;
		//
		boidsBehaviour[i].setName("Behaviour of Boids from Group " + to_string(i));
		//
		if (i == 0) {
			boidsBehaviour[i].add(separate1.set("separate", 20.0, 0, 100));
			boidsBehaviour[i].add(align1.set("align", 12, 0, 100));
			boidsBehaviour[i].add(cohesion1.set("cohesion", 3, 0, 100));
			boidsBehaviour[i].add(distSeparation1.set("distSeparation", 10, 0, 100));
			boidsBehaviour[i].add(distAlign1.set("distAlign", 20, 0, 100));
			boidsBehaviour[i].add(distCohesion1.set("distCohesion", 25, 0, 100));
			boidsBehaviour[i].add(maxSpeed1.set("maxSpeed", 2, 0, 8));
			boidsBehaviour[i].add(maxForce1.set("maxForce", 10, 0, 100));
			boidsBehaviour[i].add(attraction1.set("attraction", 100, 0, 500));
			boidsBehaviour[i].add(attractionDeviation1.set("attractiondeviation", 3, 0, 100));
		}
		else if (i == 1) {
			boidsBehaviour[i].add(separate2.set("separate", 20.0, 0, 100));
			boidsBehaviour[i].add(align2.set("align", 12, 0, 100));
			boidsBehaviour[i].add(cohesion2.set("cohesion", 3, 0, 100));
			boidsBehaviour[i].add(distSeparation2.set("distSeparation", 10, 0, 100));
			boidsBehaviour[i].add(distAlign2.set("distAlign", 20, 0, 100));
			boidsBehaviour[i].add(distCohesion2.set("distCohesion", 25, 0, 100));
			boidsBehaviour[i].add(maxSpeed2.set("maxSpeed", 2, 0, 8));
			boidsBehaviour[i].add(maxForce2.set("maxForce", 10, 0, 100));
			boidsBehaviour[i].add(attraction2.set("attraction", 100, 0, 500));
			boidsBehaviour[i].add(attractionDeviation2.set("attractiondeviation", 3, 0, 100));
		}
		// C'est de toute beauté!!!
		parametersPanels[i].setup(boidsBehaviour[i]);
		parametersPanels[i].setPosition(leftMargin + offset, topMargin);


	}
	
}

void ParametersGUI::update() {
	// Doit rester vide
}

void ParametersGUI::draw() {

	for (int i = 0; i < nbSubFlocks; i++)
	{
		parametersPanels[i].draw();
	}
}