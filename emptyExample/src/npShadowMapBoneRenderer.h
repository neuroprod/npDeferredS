#pragma once


#include "npIncludes.h"
#include "npBoneMesh.h"
#include "npCamera.h"

class npShadowMapBoneRenderer
{
public:
	 npShadowMapBoneRenderer(void);
	~ npShadowMapBoneRenderer(void);

	 void setup();
    
    
    void start(const npCamera &cam);
    void draw(const npBoneMesh *mesh);
    void stop();
    
   

    GLint program;

    GLint uBoneMatrixList;
	GLint uLightProjectionMatrix;
	GLint uWorldMatrix;
	GLint uObjectMatrix;

    enum {
        ATTRIB_VERTEX,
		ATTRIB_IDS,
		ATTRIB_WEIGHTS};
};

