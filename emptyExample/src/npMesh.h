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
    
    npMesh():vertices(NULL),indices(NULL),indices2(NULL) ,stride(8),numVertices(-1), numIndices2(0)
	{
	vertexBuffer =0;
	indexBuffer =0;
		indexBuffer2 =0;
	}
    virtual ~npMesh()
    {
        delete[] vertices;
        delete[] indices;
		  delete[] indices2;

		//if (vertexBuffer!=0) glDeleteBuffers(1 ,&vertexBuffer);
	//	if (indexBuffer!=0) 	glDeleteBuffers(1 ,&indexBuffer);
	//	if (indexBuffer2!=0) 	glDeleteBuffers(1 ,&indexBuffer);
	
		//cout<<endl << "delete oldOpjects" << endl;

    
    }
	
    void createBuffers(GLenum type =GL_STATIC_DRAW);
    void setMaterial (npMaterial  mat){material =mat;};
   
    npMaterial material;
    
    int stride;
    float * vertices;
    int numVertices;
    
    unsigned int * indices;
    int  numIndices;

	 unsigned int * indices2;
    int  numIndices2;

  
    GLuint vertexBuffer;
    GLuint indexBuffer;
     GLuint indexBuffer2;
    
   
   
    
};


#endif
