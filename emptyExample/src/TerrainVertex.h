#pragma once

#include "npIncludes.h"


class TerrainVertex
{

public:
	TerrainVertex(){};

	ofVec3f position;
	ofVec3f normal;
	ofVec3f positionT;
	ofVec3f normalT;

	ofVec2f uv;
	ofVec3f color;
	float hil;
};

