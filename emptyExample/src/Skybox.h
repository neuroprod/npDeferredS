#pragma once

#include "npIncludes.h"
#include "SkyColorBox.h"
#include "GameCamera.h"
class SkyBox
{
public:

	SkyBox(){};
	void setup();

	void update();

	void draw(const GameCamera &camera);

	SkyColorBox colorBox;
};
