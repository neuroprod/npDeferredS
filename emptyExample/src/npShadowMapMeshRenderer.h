  
#pragma once

#include "npIncludes.h"
#include "npMesh.h"
#include "npMultiMesh.h"
#include "npCamera.h"

class npShadowMapMeshRenderer
{
public:
    npShadowMapMeshRenderer(){};
    ~npShadowMapMeshRenderer(){};
    
     
    
    void setup();
    
    
    void start(const npCamera &cam,int map);
    void draw(const npMesh *mesh);
	void draw(const npMultiMesh &multiMesh);
    void stop();
    
   

    GLint program;
	GLint uLightProjectionMatrix;
	GLint uWorldMatrix;
	GLint uObjectMatrix;
		GLint uTexture;
    
    enum {
        ATTRIB_VERTEX,   ATTRIB_UV,
    
    };
    
};

