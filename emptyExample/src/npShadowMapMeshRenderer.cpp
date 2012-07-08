#include "npShadowMapMeshRenderer.h"
#include "npProgramLoader.h"
void npShadowMapMeshRenderer::setup()
{
    npProgramLoader pl;
    program = pl.loadProgram ("ShadowShaderMesh");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
   glBindAttribLocation(program,ATTRIB_UV,"uv");
 
    pl.linkProgram();
    glUseProgram(program);
    
    uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
	uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uLightProjectionMatrix = glGetUniformLocation(program,"lightProjectionMatrix");
	

 

    glUseProgram(0);
}


void npShadowMapMeshRenderer::start(const npCamera &cam,int map)
{
    glUseProgram(program);
	if (map==1)
	{
    glUniformMatrix4fv(uLightProjectionMatrix , 1, 0,   cam.lightMatrix1.getPtr());
	}
	else
	{
	
	 glUniformMatrix4fv(uLightProjectionMatrix , 1, 0,   cam.lightMatrix2.getPtr());
	}
	
	glUniformMatrix4fv(uWorldMatrix , 1, 0,   cam.worldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
   glEnableVertexAttribArray(ATTRIB_UV);
    

}
void npShadowMapMeshRenderer::draw(const npMesh *mesh)
{
  glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,mesh->material.diffuseTexture);

    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
 
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) (sizeof(float) * 0));
     glVertexAttribPointer(ATTRIB_UV,2, GL_FLOAT, GL_FALSE, sizeof(float) * mesh->stride,(GLvoid*) (sizeof(float) *6));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);



	if (mesh->isMultiObject)
	{

		for(int i=0; i<mesh->objectMatrices.size();i++ ){

			glUniformMatrix4fv(uObjectMatrix, 1, 0, mesh->objectMatrices[i].getPtr());
			glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
		}
	
	
	}else
	{
	
		glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
		glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);
	}
  



}
void npShadowMapMeshRenderer::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
     glDisableVertexAttribArray(ATTRIB_UV);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
	   glUseProgram(0);

}
