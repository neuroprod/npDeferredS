#pragma once

#include "npIncludes.h"
#include "GameCamera.h"
#include "npMaterial.h"
class  SkyBoxElements
{
public:

	SkyBoxElements(){};
	void setup();

	void update();

	void draw(const GameCamera &camera);
	GLint program ;
	
	GLint   uPerspectiveMatrix;
	GLint  uObjectMatrix;

	npMaterial sunMaterial;
	GLfloat * sunVertices;
};
