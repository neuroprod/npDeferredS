#pragma once


#include "npIncludes.h"
#include "npCamera.h"
#include "MainCharacter.h"
#include "Terrain.h"
class GameCamera:public npCamera
{

public:
	GameCamera(){};

	void setMouse(bool mouseIsDown,float moveX,float moveY);

	void update();
	void setup();
	MainCharacter * mainCharacter;

	ofVec3f lookAtPos ;
	ofVec3f camPos;

	ofVec3f camDir;

	ofVec3f lightDir;

	ofMatrix4x4 lightPerspectivedMatrix1;
	ofMatrix4x4 lightWorldMatrix1;

	ofMatrix4x4 mouseMatrix;



	ofMatrix4x4 currentRotation;
	ofQuaternion currentQuaternation;


	Terrain *terrain;
};