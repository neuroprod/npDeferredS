//
//  npPointLightRenderer.h
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npPointLightRenderer_h
#define emptyExample_npPointLightRenderer_h


#include "npIncludes.h"
#include "npPointLight.h"
#include "npCamera.h"
class npPointLightRenderer
{
    
public:
    npPointLightRenderer(){}
    void setup(int w,int h );
  
    void draw( const vector<npPointLight *> &pLights,const npCamera &cam);
    
 

    GLuint fbo;	
    GLuint depthBuffer;
    
    GLuint depthTexture;
    GLuint normalTexture;
    GLuint pointLightTexture;

    GLint program;
    GLint uNormalMatrix;
    GLint uPerspectiveMatrix;
     GLint uPerspectiveInvMatrix;
	  GLint uNormalWorldMatrix;
    GLint uWorldMatrix;
    GLint uObjectMatrix;
     GLint uCenter;
    
    int width;
    int height;
    
    enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_COLOR,
    };
    GLint uNormalTexture;
    GLint uDepthTexture;

};


#endif
