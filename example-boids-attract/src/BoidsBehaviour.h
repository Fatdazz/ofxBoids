#pragma once

class BoidsBehaviour
{
public:
	float separate;
	float align;
	float cohesion;
	float distSeparation;
	float distAlign;
	float distCohesion;
	float maxSpeed;
	float maxForce;
	float attraction;
	float attractiondeviation;

	BoidsBehaviour(float separatePreset, float alignPreset, float cohesionPreset, float distSeparationPreset, float distAlignPreset, float distCohesionPreset, float maxSpeedPreset, float maxForcePreset, float attractionPreset, float attractiondeviationPreset);
	~BoidsBehaviour();
};

