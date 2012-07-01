//
//  npMeshRenderer.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "npMeshRendererText.h"
#include "npProgramLoader.h"
void npMeshRendererText::setup()
{
    npProgramLoader pl;
    program = pl.loadProgram ("DeferredShaderDifText");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
	 glBindAttribLocation(program,ATTRIB_TANGENT,"tangent");
    glBindAttribLocation(program,ATTRIB_UV,"uv");
 
    pl.linkProgram();
    glUseProgram(program);
    
     uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
   uNormalWorldMatrix = glGetUniformLocation(program,"normalWorldMatrix");

    uTextureNormal= glGetUniformLocation(program,"textureNormal");
	uTextureDiffuse= glGetUniformLocation(program,"textureDiffuse");
	 glUniform1i(uTextureDiffuse,0);
   glUniform1i(  uTextureNormal,1);

    glUseProgram(0);
}


void npMeshRendererText::start(const npCamera &cam)
{
    glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam.perspectiveMatrix.getPtr());
     glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam.normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
		  glEnableVertexAttribArray(ATTRIB_TANGENT);
    glEnableVertexAttribArray(ATTRIB_UV);
    

}
void npMeshRendererText::draw(const npMesh *mesh)
{
	    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mesh->material.normalTexture);
	    glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->material.diffuseTexture);


    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,(GLvoid*) (sizeof(float) *3 ));
	    glVertexAttribPointer(ATTRIB_TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11,(GLvoid*) (sizeof(float) *6 ));
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11,(GLvoid*) (sizeof(float) * 9));
    
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
	if (mesh->isMultiObject)
	{

		for(int i=0; i<mesh->objectMatrices.size();i++ ){

			glUniformMatrix4fv(uObjectMatrix, 1, 0, mesh->objectMatrices[i].getPtr());
			glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrices[i].getPtr());
    
			glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
		}
	
	
	}else
	{
	
	  glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
    glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
	}
  



}
void npMeshRendererText::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
	  glDisableVertexAttribArray(ATTRIB_TANGENT);
    glDisableVertexAttribArray(ATTRIB_UV);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
	   glUseProgram(0);

}
