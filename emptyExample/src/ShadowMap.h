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
	void setup();
	void start( );





	void stop();


};