#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "npBone.h"
class npBoneMesh:public npMesh
{
public:
	npBoneMesh(void);
	~npBoneMesh(void);

	void prepBones();
	void setMatrixes();
	void update();


	vector < npBone *> bones;
	npBone * rootBone;
	string name;
	

	float* matrixes;
	float time;
};

