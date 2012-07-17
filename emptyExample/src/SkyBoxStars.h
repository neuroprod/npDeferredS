#pragma once
#include "npIncludes.h"
#include "npMesh.h"

class SkyBoxStars
{
public:
	SkyBoxStars(){};
	void setup();


	npMesh starMesh;
	float *vertices;
	int numStars;
};