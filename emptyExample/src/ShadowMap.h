#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "GameCamera.h"
#include "npDepthFBO.h"
#include "npDirectionalLight.h"
class ShadowMap
{
public:
    ShadowMap(){};
    ~ShadowMap(){};

	npDepthFBO fbo1;
	GLuint shadowTexture1;

	npDepthFBO fbo2;
	GLuint shadowTexture2;
	void setup();
	void start1( );
	void stop1();

	void start2( );
	void stop2();

};