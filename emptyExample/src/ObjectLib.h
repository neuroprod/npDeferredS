#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "npAssimpLoader.h"

class ObjectLib
{

public:

	ObjectLib(){};
	void setup();
	npMesh *tree1_hr;


	vector <npMesh *> objects;
	vector <npMesh *> getGLClones();
	

};