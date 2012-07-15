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

	void draw(const GameCamera &camera);
	GLint program ;
	GLuint cube_vertices;
	GLuint cube_indices;

	GLint   uPerspectiveMatrix;

	int  numIndices;
	npMaterial skyMaterial;
};