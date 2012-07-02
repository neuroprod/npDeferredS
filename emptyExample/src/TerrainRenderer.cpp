//
//  npMeshRenderer.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 23/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "TerrainRenderer.h"
#include "npProgramLoader.h"
#include "GLErrorCheck.h"


void TerrainRenderer::setup()
{
	
	npMaterial vegMap;
	vegMap.loadDiffuse("3DAssets/Vegetation.png" );
	vegMapTexture =vegMap.diffuseTexture;



	npMaterial GrassMat;
	GrassMat.loadDiffuse("3DAssets/grass1.png" );
	grassTexture =GrassMat.diffuseTexture;


	npMaterial dirtMap;
	 dirtMap.loadDiffuse("3DAssets/rock1.png" );
	dirtTexture = dirtMap.diffuseTexture;


	npMaterial forestMap;
	forestMap.loadDiffuse("3DAssets/forestFloor1.png" );
	 forestTexture =forestMap.diffuseTexture;



	/*  
	GLint uVegMapTexture;
	GLint uGrassTexture;
	GLint uDirtTexture;
	GLint uForestTexture;


    GLuint vegMapTexture;
	GLuint dirtTexture;
	GLuint grassTexture;
	GLuint forestTexture;
	*/


    npProgramLoader pl;
    program = pl.loadProgram ("DeferredShaderTerrain");
	
    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
    glBindAttribLocation(program,ATTRIB_UV,"uv");
    pl.linkProgram();
    glUseProgram(program);
  
	 uVegMapTexture= glGetUniformLocation(program,"vegMapTexture");
	 uGrassTexture= glGetUniformLocation(program,"grassTexture");
	 uDirtTexture= glGetUniformLocation(program,"dirtTexture");
	 uForestTexture= glGetUniformLocation(program,"forestTexture");


    uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
   uNormalWorldMatrix = glGetUniformLocation(program,"normalWorldMatrix");

   glUniform1i(uVegMapTexture,0);
   glUniform1i( uGrassTexture,1);
   glUniform1i( uDirtTexture,2);
   glUniform1i( uForestTexture,3);

  

    glUseProgram(0);
		
}


void TerrainRenderer::start(const npCamera &cam)
{
	

    glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,    cam.perspectiveMatrix.getPtr());
     glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam.normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_UV);

	    glActiveTexture(GL_TEXTURE1);
	glBindTexture (GL_TEXTURE_2D,grassTexture);

	    glActiveTexture(GL_TEXTURE2);
	glBindTexture (GL_TEXTURE_2D,dirtTexture);

	    glActiveTexture(GL_TEXTURE3);
	glBindTexture (GL_TEXTURE_2D,forestTexture);

      glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D,vegMapTexture);

}
void TerrainRenderer::draw(const npMesh *mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,(GLvoid*) (sizeof(float) *3 ));
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,(GLvoid*) (sizeof(float) * 6));
  
    
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
 
    glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
    glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);



}
void TerrainRenderer::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
     glDisableVertexAttribArray(ATTRIB_UV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindTexture (GL_TEXTURE_2D,0);
}
