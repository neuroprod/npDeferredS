  
#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "npCamera.h"

class npShadowMapMeshRenderer
{
public:
    npShadowMapMeshRenderer(){};
    ~npShadowMapMeshRenderer(){};
    
     
    
    void setup();
    
    
    void start(const npCamera &cam);
    void draw(const npMesh *mesh);
    void stop();
    
   

    GLint program;
	GLint uLightProjectionMatrix;
	GLint uWorldMatrix;
	GLint uObjectMatrix;

    
    enum {
        ATTRIB_VERTEX,   ATTRIB_NORMAL,
    
    };
    
};

