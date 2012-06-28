//
//  npMesh.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "npMesh.h"


void npMesh::createBuffers()
{

    vertexBuffer;
    indexBuffer;
    
    glGenBuffers(1, &vertexBuffer);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices*stride* sizeof(float), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &indexBuffer);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
    
    
    
 



}