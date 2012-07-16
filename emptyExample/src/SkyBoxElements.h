#pragma once

#include "npIncludes.h"
#include "GameCamera.h"
#include "npMaterial.h"
#include "npDirectionalLight.h"
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
	int count;
	npDirectionalLight *light;
};
