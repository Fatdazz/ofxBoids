#include "BoidsBehaviour.h"



BoidsBehaviour::BoidsBehaviour(float separatePreset, float alignPreset, float cohesionPreset, float distSeparationPreset, float distAlignPreset, float distCohesionPreset, float maxSpeedPreset, float maxForcePreset, float attractionPreset, float attractiondeviationPreset)
{
	separate = separatePreset;
	align = alignPreset;
	cohesion = cohesionPreset;
	distSeparation = distSeparationPreset;
	distAlign = distAlignPreset;
	distCohesion = distCohesionPreset;
	maxSpeed = maxSpeedPreset;
	maxForce = maxForcePreset;
	attraction = attractionPreset;
	attractiondeviation = attractiondeviationPreset;
}


BoidsBehaviour::~BoidsBehaviour()
{
}
