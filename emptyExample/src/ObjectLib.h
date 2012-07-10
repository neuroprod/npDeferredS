#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "npMultiMesh.h"
#include "npAssimpLoader.h"


class ObjectLib
{

public:

	ObjectLib(){};
	void setup();
//	void getMultiMeshes(Chunk *chunk );
	npMesh *tree1_hr;
	npMesh *grass_hr;

	vector <npMesh *> objects;
	
	

};