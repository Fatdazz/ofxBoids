#pragma once


class AttractionPoint3d {
public:
	
	float x, y, z, force, sensorDist;
	
	float halfDist;
	
	AttractionPoint3d() {
		x = y = z = force = sensorDist = halfDist = 0.0f;
	}
	
	AttractionPoint3d(float _x, float _y, float _z, float _f, float _sensor) {
		x = _x;
		y = _y;
		z = _z;
		force = _f;
		sensorDist = _sensor;
		halfDist = sensorDist / 2.0f;
	}
	
	void draw(){ ////dont use please:)
		ofRect(x-halfDist, y-halfDist, sensorDist, sensorDist);
		ofRect(x,y,3,3);
	}
	
	
};
