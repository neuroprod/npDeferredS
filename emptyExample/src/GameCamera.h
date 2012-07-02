#pragma once


#include "npIncludes.h"
#include "npCamera.h"
#include "MainCharacter.h"
class GameCamera:public npCamera
{

public:
	GameCamera(){};
	void update();
	void setup();
	MainCharacter * mainCharacter;

	ofVec3f lookAtPos ;
	ofVec3f camPos;


	ofVec3f lightDir;

	ofMatrix4x4 lightPerspectivedMatrix1;
	ofMatrix4x4 lightWorldMatrix1;


};