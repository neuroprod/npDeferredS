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



};