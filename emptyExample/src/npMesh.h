//
//  npMesh.h
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npMesh_h
#define emptyExample_npMesh_h

#include "npIncludes.h"
#include "npMaterial.h"
#include "npObject3D.h"
class npMesh :public npObject3D
{

public:
    
    npMesh():vertices(NULL),indices(NULL) ,stride(8){}
    virtual ~npMesh()
    {
        delete[] vertices;
        delete[] indices;
    
    }
	npMesh * getGLCopy();
    void createBuffers();
    void setMaterial (npMaterial  mat){material =mat;};
   
    npMaterial material;
    
    int stride;
    float * vertices;
    int numVertices;
    
    unsigned int * indices;
    int  numIndices;
  
    GLuint vertexBuffer;
    GLuint indexBuffer;
    
    
   
   
    
};


#endif
