#pragma once


#include "npIncludes.h"
#include "npPointLight.h"

class npMultiPointLight
{

public:
	npMultiPointLight(npPointLight *_pLight){ pLight =_pLight;};
	npPointLight *pLight;
	vector <ofMatrix4x4> objectMatrices;

	vector <ofVec3f>  objectCenters;

};