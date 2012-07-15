#pragma once


#include "npIncludes.h"
#include "npCamera.h"
#include "MainCharacter.h"
#include "TerrainFunctions.h"
class GameCamera:public npCamera
{

public:
	GameCamera(){};

	void setMouse(bool mouseIsDown,float moveX,float moveY);

	void update(unsigned long timeStep);
	void setup();
	MainCharacter * mainCharacter;

	ofVec3f lookAtPos ;
	ofVec3f camPos;

	ofVec3f camDir;

	ofVec3f lightDir;

	ofMatrix4x4 lightPerspectivedMatrix1;
	ofMatrix4x4 lightWorldMatrix1;

	ofMatrix4x4 lightPerspectivedMatrix2;
	ofMatrix4x4 lightWorldMatrix2;

	ofMatrix4x4 lightPerspectivedMatrix3;
	ofMatrix4x4 lightWorldMatrix3;

	ofMatrix4x4 mouseMatrix;



	ofMatrix4x4 currentRotation;
	ofQuaternion currentQuaternation;
	float testtime;

	TerrainFunctions *terrainFunctions;

	ofMatrix4x4 skyBoxPerspectiveMatrix;
	ofMatrix4x4 skyBoxMatrix;
};