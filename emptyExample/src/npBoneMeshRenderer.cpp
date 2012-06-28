#include "npBoneMeshRenderer.h"
#include "npProgramLoader.h"

npBoneMeshRenderer::npBoneMeshRenderer(void)
{
}


npBoneMeshRenderer::~npBoneMeshRenderer(void)
{
}

void npBoneMeshRenderer::setup()
{
    npProgramLoader pl;
    program = pl.loadProgram ("DeferredShaderBones");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
    glBindAttribLocation(program,ATTRIB_UV,"uv");
	glBindAttribLocation(program,ATTRIB_IDS,"ids");
	glBindAttribLocation(program,ATTRIB_WEIGHTS,"weights");

    pl.linkProgram();
    glUseProgram(program);
    
    uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
    uNormalMatrix = glGetUniformLocation(program,"normalMatrix");
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
    uBoneMatrixList = glGetUniformLocation(program,"boneMatrixList");
    glUseProgram(0);
}


void  npBoneMeshRenderer::start(npCamera *cam)
{
    glUseProgram(program);
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam->worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam->perspectiveMatrix.getPtr());
   //  glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam->normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_UV);
	 glEnableVertexAttribArray(ATTRIB_IDS);
	 glEnableVertexAttribArray(ATTRIB_WEIGHTS);
    

}
void  npBoneMeshRenderer::draw(const npBoneMesh *mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER,mesh->vertexBuffer);
    
	
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 0));
    glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) *3 ));
    glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 6));
    glVertexAttribPointer(ATTRIB_IDS, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 8));
    glVertexAttribPointer(ATTRIB_WEIGHTS, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12,(GLvoid*) (sizeof(float) * 10));
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  mesh->indexBuffer);
    glUniformMatrix4fv(uObjectMatrix, 1, 0,  mesh->objectMatrix.getPtr());
    glUniformMatrix4fv(uNormalMatrix, 1, 0,   mesh->normalMatrix.getPtr());
    glUniformMatrix4fv( uBoneMatrixList,22,0, mesh->matrixes);
    glDrawElements(GL_TRIANGLES,mesh->numIndices , GL_UNSIGNED_INT, (void*)0);



}
void npBoneMeshRenderer::stop()
{
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
     glDisableVertexAttribArray(ATTRIB_UV);
	  glDisableVertexAttribArray(ATTRIB_IDS);
	   glDisableVertexAttribArray(ATTRIB_WEIGHTS);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

}
