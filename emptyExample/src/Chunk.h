#pragma once


#include "npIncludes.h"
#include "npMesh.h"

class Chunk
{
public:
	Chunk(){};
	~Chunk(){};

	void calculateDetail(const ofVec3f &camPos,const ofVec3f &lookDir);
	void setDetailLevel(int _detailLevel);
	ofVec3f center;


	int detailLevel;
	npMesh * terrainLowRes;
	npMesh * terrainHighRes;
};