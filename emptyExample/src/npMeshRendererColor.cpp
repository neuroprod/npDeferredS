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
   uNormalWorldMatrix = glGetUniformLocation(program,"normalWorldMatrix");
    glUseProgram(0);
}


void npMeshRendererColor::start(const npCamera &cam)
{
    glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam.perspectiveMatrix.getPtr());
     glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam.normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_COLOR);

	
    

}
void npMeshRendererColor::drawTriangle(const ofVec3f &p0,const ofVec3f &p1,const ofVec3f &p2)
{
	ofMatrix4x4 objectMatrix;
	objectMatrix.makeIdentityMatrix();
	glUniformMatrix4fv(uObjectMatrix, 1, 0,  objectMatrix.getPtr());
    glUniformMatrix4fv(uNormalMatrix, 1, 0,  objectMatrix.getPtr());
    
	glDisable(GL_CULL_FACE);
	float *pointer =new float[9*3];
	//cout <<p0 <<" --  "<< p1<<" -- " <<p2 <<endl;
	float f =1;
	pointer[0] = p0.x*f; 
	pointer[1] = p0.y+0.1; 
	pointer[2] = p0.z*f; 

	pointer[3] = 0; 
	pointer[4] = 1; 
	pointer[5] =0; 

	pointer[6] = 1; 
	pointer[7] = 0; 
	pointer[8] = 0; 



	pointer[9] = p1.x*f; 
	pointer[10] = p1.y+0.1; 
	pointer[11] = p1.z*f; 

	pointer[12] = 0; 
	pointer[13] = 1; 
	pointer[14] =0; 

	pointer[15] = 0; 
	pointer[16] = 1; 
	pointer[17] = 0; 


	pointer[18] = p2.x*f; 
	pointer[19] = p2.y+0.1; 
	pointer[20] = p2.z*f; 
   
	pointer[21] = 0; 
	pointer[22] = 1; 
	pointer[23] =0; 

	pointer[24] = 1; 
	pointer[25] = 1; 
	pointer[26] = 1; 

	float *p =pointer; 

    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), p);
    p +=3;
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), p);
    p +=3;
	glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, 0, 9*sizeof(GLfloat), p);

    glDrawArrays(GL_TRIANGLES, 0, 3);

	delete [] pointer;

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
void  npMeshRendererColor::draw(const npMultiPointLight &mpl)
{


		 glBindBuffer(GL_ARRAY_BUFFER,mpl.pLight->drawSphere.vertexBuffer);
    
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) *3 ));
    glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 6));
  
    
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mpl.pLight->drawSphere.indexBuffer);

	for(int i=0;i<   mpl.objectMatrices.size();i++){
    glUniformMatrix4fv(uObjectMatrix, 1, 0,  mpl.objectMatrices[i].getPtr());
	glUniformMatrix4fv(uNormalMatrix, 1, 0,   mpl.objectMatrices[i].getPtr());
    
	glDrawElements(GL_TRIANGLES,mpl.pLight->drawSphere.numIndices , GL_UNSIGNED_INT, (void*)0);
	}


}
void npMeshRendererColor::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
     glDisableVertexAttribArray(ATTRIB_COLOR);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

}
