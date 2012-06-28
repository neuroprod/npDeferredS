#pragma once
#include "npIncludes.h"
#include "npBoneAnimation.h"





class npBone
{
public:
	npBone(void);
	~npBone(void);

	bool isNodeBone;
	string name;
	int id;

	ofMatrix4x4 boneMatrix;

	ofMatrix4x4 nodeMatrix;

	ofMatrix4x4 finalMatrix;
	ofMatrix4x4 animeMatrix;
	npBone *parent;
	vector <npBone *>children ;

	vector<npBoneAnimation> animations;
};

