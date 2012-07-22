#pragma once
#include "npIncludes.h"
class TerrainMaterial
{


public:
	TerrainMaterial()
	{
	isUsed = false;
	
	}

	GLint texture;
	bool isUsed;

};