#pragma once

#include "npAssimpLoader.h"
#include "npIncludes.h"
#include "npBoneMesh.h"
#include "Terrain.h"
class MainCharacter
{

public :
	MainCharacter(){};
	void setup();
	void update( unsigned long timeStep);


	bool isMoving;
	float walkspeed;
	float rotSpeed;
	float walkDirRot;
	ofVec3f walkDir;
	ofVec3f charPos;


	npBoneMesh charMesh;
	npAssimpLoader aLoader;


	void setKey(int);
	int lastDown;
	bool leftIsDown;
	bool rightIsDown;

	Terrain * terain;

	enum
	{
	     FORWARD_DOWN,FORWARD_UP,
		 LEFT_DOWN,LEFT_UP,
		RIGHT_DOWN,RIGHT_UP,
	
	
	};

};