#include "npShadowMapBoneRenderer.h"
#include "npProgramLoader.h"

npShadowMapBoneRenderer::npShadowMapBoneRenderer(void)
{
}


npShadowMapBoneRenderer::~npShadowMapBoneRenderer(void)
{
}

void npShadowMapBoneRenderer::setup()
{
    npProgramLoader pl;
    program = pl.loadProgram ("ShadowShaderBones");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    //glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
    //glBindAttribLocation(program,ATTRIB_UV,"uv");
	glBindAttribLocation(program,ATTRIB_IDS,"ids");
	glBindAttribLocation(program,ATTRIB_WEIGHTS,"weights");

    pl.linkProgram();
    glUseProgram(program);
    
     uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
	uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uLightProjectionMatrix = glGetUniformLocation(program,"lightProjectionMatrix");

    uBoneMatrixList = glGetUniformLocation(program,"boneMatrixList");
	//uBoneNormalMatrixList = glGetUniformLocation(program,"boneNormalMatrixList");
    glUseProgram(0);
}


void  npShadowMapBoneRenderer::start(const npCamera &cam)
{
	glEnable(GL_TEXTURE_2D);
    glUseProgram(program);
	glUniformMatrix4fv(uLightProjectionMatrix , 1, 0,   cam.lightMatrix1.getPtr());
	 glUniformMatrix4fv(uWorldMatrix , 1, 0,   cam.worldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
	 glEnableVertexAttribArray(ATTRIB_IDS);
	 glEnableVertexAttribArray(ATTRIB_WEIGHTS);
    

}
void  npShadowMapBoneRenderer::draw(const npBoneMesh *mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
	//glBindTexture(GL_TEXTURE_2D,mesh->material.diffuseTexture);
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 0));
  
    glVertexAttribPointer(ATTRIB_IDS, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 8));
    glVertexAttribPointer(ATTRIB_WEIGHTS, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 10));
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
    glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
 
    glUniformMatrix4fv( uBoneMatrixList,22,0, mesh->boneMatrices);
	// glUniformMatrix4fv( uBoneNormalMatrixList,22,0, mesh->normalMatrices);
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);



}
void npShadowMapBoneRenderer::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);

	  glDisableVertexAttribArray(ATTRIB_IDS);
	   glDisableVertexAttribArray(ATTRIB_WEIGHTS);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

}
