#include "npDeferredShadowPass.h"
#include "npProgramLoader.h" 
#include "npMaterial.h"
void npDeferredShadowPass::setup(string prog)
{
	
  


	npMaterial matN;
	matN.loadDiffuse("3DAssets/AONoise.png");
	AONoiseTexture = matN.diffuseTexture;

	





    npProgramLoader pLoader ;
    program=    pLoader.loadProgram (prog);
    

    glBindAttribLocation(  program, ATTRIB_VERTEX_FS, "position");
    
    glBindAttribLocation(  program, ATTRIB_UV_FS, "uv");
    pLoader.linkProgram();
    
    glUseProgram( program);
    
	

    uNormalTexture= glGetUniformLocation( program, "normalTexture");
    uDepthTexture= glGetUniformLocation( program, "depthTexture");
   
	 uAONoiseTexture= glGetUniformLocation( program, "AONoiseTexture");
	 
	 uShadowTexture1= glGetUniformLocation( program, "shadowTexture1");



	uPerspectiveInvMatrix =  glGetUniformLocation( program, "perspectiveInvMatrix");
	uLight1Matrix=  glGetUniformLocation( program, "light1Matrix");



    glUniform1i(  uNormalTexture, 0);
    glUniform1i(  uDepthTexture, 1);
glUniform1i(   uAONoiseTexture, 2);
	glUniform1i(  uShadowTexture1, 3);
	
	
	glUseProgram(0);
    
  
    
  
    
   
    
    
    float  uvX = 1;
    float  uvY = 0.0;
    float uvWidth =-1;
	float uvHeight =1;
   
    
	
	dataFB = new float [36];
    
    
  
    
    dataFB[0] =1 ;
    dataFB[1] =-1 ;
    dataFB[2] =0;
    dataFB[3] = uvX;
    dataFB[4] = uvY;
    dataFB[5] = 0;
    
    
   
    
    
    
    dataFB[6] = 1 ;
    dataFB[7] = 1 ;
    dataFB[8] = 0;
    dataFB[9] = uvX ;
    dataFB[10] = uvY +uvHeight;
    dataFB[11] = 1;
    
    dataFB[12] = -1 ;
    dataFB[13] = -1 ;
    dataFB[14] = 0;
    dataFB[15] = uvX +uvWidth;
    dataFB[16] = uvY;
    dataFB[17] = 1;
    
    
    dataFB[18] = -1 ;
    dataFB[19] = 1 ;
    dataFB[20] = 0;
    dataFB[21] =  uvX +uvWidth; 
    dataFB[22] = uvY +uvHeight;
    dataFB[23] = 1;
    
    
    dataFB[24] = dataFB[12];
    dataFB[25] = dataFB[13];
    dataFB[26] = dataFB[14];
    dataFB[27] = dataFB[15];
    dataFB[28] = dataFB[16];
    dataFB[29] = dataFB[17];
    
    
    dataFB[30] = dataFB[6];
    dataFB[31] = dataFB[7];
    dataFB[32] = dataFB[8];
    dataFB[33] = dataFB[9];
    dataFB[34] = dataFB[10];
    dataFB[35] = dataFB[11];
    
}
void npDeferredShadowPass::draw(const npCamera &cam){
    
 
 
    glUseProgram(program);
  
   

   
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,normalTexture);
    
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,depthTexture);
    
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D,AONoiseTexture);


	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D,shadowTexture1);

	
	



	
	
	glUniformMatrix4fv(uPerspectiveInvMatrix, 1, 0,   cam.perspectiveInvMatrix.getPtr());
	glUniformMatrix4fv(uLight1Matrix, 1, 0,    cam.lightMatrix2.getPtr());

    glEnableVertexAttribArray(ATTRIB_VERTEX_FS);
    glEnableVertexAttribArray(ATTRIB_UV_FS);
	
	
	GLfloat *pointer;
    pointer =dataFB;

    glVertexAttribPointer(ATTRIB_VERTEX_FS, 3, GL_FLOAT, 0, 6*sizeof(GLfloat), pointer);
    glEnableVertexAttribArray(ATTRIB_VERTEX_FS);

    pointer +=3;
    glVertexAttribPointer(ATTRIB_UV_FS, 3, GL_FLOAT, 0, 6*sizeof(GLfloat), pointer);
    glEnableVertexAttribArray(ATTRIB_UV_FS);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    
    glDisableVertexAttribArray(ATTRIB_VERTEX_FS);
    glDisableVertexAttribArray(ATTRIB_UV_FS);
    
    
    glUseProgram(0);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,0);



}