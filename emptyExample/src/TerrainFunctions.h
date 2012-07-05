#pragma once

#include "npIncludes.h"
#include "perlin.h"

class TerrainFunctions {
public:
	TerrainFunctions(){};
	~TerrainFunctions(){};

	void setup();

	float getHeightForPos(float  x, float z);

	ofVec3f getNormalforPos(float x, float z);
	ofVec3f getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3);


	Perlin *heightPerlin;

};