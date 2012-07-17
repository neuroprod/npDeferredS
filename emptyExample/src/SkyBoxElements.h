#pragma once

#include "npIncludes.h"
#include "GameCamera.h"
#include "npMaterial.h"
#include "npDirectionalLight.h"
#include "SkyBoxStars.h"

class  SkyBoxElements
{
public:

	SkyBoxElements(){};
	void setup();

	void update();

	void draw(const GameCamera &camera,const float &time);
	GLint program ;
	
	GLint   uPerspectiveMatrix;
	GLint  uObjectMatrix;

	npMaterial sunMaterial;
	GLfloat * sunVertices;


	
	SkyBoxStars stars;
	npMaterial starsMaterial;



	npDirectionalLight *light;
};
