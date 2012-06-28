//
//  npMeshRenderer.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "npMeshRendererColor.h"
#include "npProgramLoader.h"
void npMeshRendererColor::setup()
{
    npProgramLoader pl;
    program = pl.loadProgram ("DeferredShaderColor");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
   
    glBindAttribLocation(program,ATTRIB_COLOR,"color");
    pl.linkProgram();
    glUseProgram(program);
    
    uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
  //  uNormalWorldMatrix = glGetUniformLocation(program,"normalWorldMatrix");
    glUseProgram(0);
}


void npMeshRendererColor::start(npCamera *cam)
{
    glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam->worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam->perspectiveMatrix.getPtr());
   //  glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam->normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    

}
void npMeshRendererColor::draw(const npMesh *mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) *3 ));
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 6));
  
    
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
 
    glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
    glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);



}
void npMeshRendererColor::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
     glDisableVertexAttribArray(ATTRIB_COLOR);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

}
