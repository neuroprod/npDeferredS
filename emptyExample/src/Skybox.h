#pragma once

#include "npIncludes.h"
#include "SkyColorBox.h"
#include "SkyBoxElements.h"
#include "GameCamera.h"
#include "npDirectionalLight.h"
class SkyBox
{
public:

	SkyBox(){};
	void setup();

	void update();

	void draw(const GameCamera &camera,const float &time);

	SkyColorBox colorBox;
	SkyBoxElements elementBox;
	npDirectionalLight *light;
	

};
