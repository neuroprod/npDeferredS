#pragma once
#include "npIncludes.h"

class npAnimeRotation
{
public :
	ofQuaternion quat;
	double time;
};
class npAnimeTranslation
{
public :
	ofVec3f pos;
	double time;
};



class npBoneAnimation
{
public:
	npBoneAnimation(void);
	~npBoneAnimation(void);
	vector<npAnimeTranslation> translations;
	vector<npAnimeRotation> rotations;
	float totalTime;

};

