//
//  npMeshRenderer.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npMeshRendererText_h
#define emptyExample_npMeshRendererText_h

#include "npIncludes.h"
#include "npMesh.h"
#include "npCamera.h"

class npMeshRendererText
{
public:
    npMeshRendererText(){};
    ~npMeshRendererText(){};
    
     
    
    void setup();
    
    
    void start(const npCamera &cam);
    void draw(const npMesh *mesh);
    void stop();
    
   

    GLint program;
	GLint uNormalMatrix;
    GLint uNormalWorldMatrix;
    GLint uPerspectiveMatrix;
    GLint uWorldMatrix;
    GLint uObjectMatrix;
    
    
    enum {
        ATTRIB_VERTEX,
        ATTRIB_NORMAL,
        ATTRIB_UV
    };
    
};

#endif
