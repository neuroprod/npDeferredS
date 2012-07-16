#pragma once

#include "npIncludes.h"
#include "GameCamera.h"
#include "npMaterial.h"
class SkyColorBox
{
public:

	SkyColorBox(){};
	void setup();

	void update();

	void draw(const GameCamera &camera,const float &time);
	GLint program ;
	GLuint cube_vertices;
	GLuint cube_indices;

	GLint   uPerspectiveMatrix;
	GLint   uTime;
	int  numIndices;
	npMaterial skyMaterial;
};