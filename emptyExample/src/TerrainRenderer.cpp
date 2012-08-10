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
	
	{
		npProgramLoader pl;
		programDetail = pl.loadProgram ("DeferredShaderTerrainDetail");
		glBindAttribLocation(programDetail,ATTRIB_VERTEX,"position");
		glBindAttribLocation(programDetail,ATTRIB_NORMAL,"normal");
		glBindAttribLocation(programDetail,ATTRIB_UV,"uv");
		pl.linkProgram();
		glUseProgram(programDetail);

		//uVegMapTexture= glGetUniformLocation(program,"vegMapTexture");
		uObjectMatrixDetail = glGetUniformLocation(programDetail,"objectMatrix");
		uNormalMatrixDetail = glGetUniformLocation(programDetail,"normalMatrix");
		uWorldMatrixDetail = glGetUniformLocation(programDetail,"worldMatrix");
		uPerspectiveMatrixDetail = glGetUniformLocation(programDetail,"perspectiveMatrix");
		uNormalWorldMatrixDetail = glGetUniformLocation(programDetail,"normalWorldMatrix");
	
		glUniform1i(uVegMapTexture,0);
	}
	



	{
		npProgramLoader pl;
		program = pl.loadProgram ("DeferredShaderTerrain");
		glBindAttribLocation(program,ATTRIB_VERTEX,"position");
		glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
		glBindAttribLocation(program,ATTRIB_UV,"uv");
		pl.linkProgram();
		glUseProgram(program);

		//uVegMapTexture= glGetUniformLocation(program,"vegMapTexture");
		uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
		uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
		uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
		uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
		uNormalWorldMatrix = glGetUniformLocation(program,"normalWorldMatrix");
	
		glUniform1i(uVegMapTexture,0);
	}

    glUseProgram(0);
		
}


void TerrainRenderer::start( npCamera &cam)
{
	camera = &cam;

    glUseProgram(programDetail);
    glUniformMatrix4fv(uWorldMatrixDetail, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrixDetail, 1, 0,    cam.perspectiveMatrix.getPtr());
    glUniformMatrix4fv(uNormalWorldMatrixDetail, 1, 0,   cam.normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_UV);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D,vegMapTexture);

	currentDetailLevel=1;

}
void TerrainRenderer::draw(const npMesh *mesh, int detailLevel)
{
	
	if (detailLevel != 1 && currentDetailLevel==1 )
	{
		switchProgram();
	currentDetailLevel =2;
	}
	if (detailLevel==1)
	{
		glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
		glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) * 0));
		glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) *3 ));
		glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) * 8));
  
    
    
	
	
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
 
			glUniformMatrix4fv(uObjectMatrixDetail, 1, 0,  mesh->objectMatrix.getPtr());
			glUniformMatrix4fv(uNormalMatrixDetail, 1, 0,   mesh->normalMatrix.getPtr());
    
			glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
	
	
	}
	else
	{


		glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
		glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) * 0));
		glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) *3 ));
		glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10,(GLvoid*) (sizeof(float) * 6));
  
    
    
		if (detailLevel==3)
		{
		   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer2);
 
			glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
			glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    
			 glDrawElements(GL_TRIANGLES,mesh->numIndices2 , GL_UNSIGNED_INT, (void*)0);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
 
			glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
			glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    
			glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
		}

	}
}

void TerrainRenderer::switchProgram()
{
	glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  camera->worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   camera->perspectiveMatrix.getPtr());
    glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   camera->normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_UV);

    glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D,vegMapTexture);

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
