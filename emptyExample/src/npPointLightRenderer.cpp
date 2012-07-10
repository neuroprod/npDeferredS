//
//  npPointLightRenderer.cpp
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "npPointLightRenderer.h"

#include "npProgramLoader.h"
#include "GLErrorCheck.h"

void npPointLightRenderer::setup(int w,int h )
{

    width =w;
    height =h;
    
    
    npProgramLoader pl;
    program = pl.loadProgram ("DeferredShaderPointLight");
    
    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_NORMAL,"normal");
    glBindAttribLocation(program,ATTRIB_COLOR,"color");
    
    
    
    pl.linkProgram();
    glUseProgram(program);
    
    uNormalTexture= glGetUniformLocation( program, "normalTexture");
    uDepthTexture= glGetUniformLocation( program, "depthTexture");
    glUniform1i(  uNormalTexture, 0);
    glUniform1i(  uDepthTexture, 1);
    
  
   
    uCenter = glGetUniformLocation(program,"center");
    uLightSize= glGetUniformLocation(program,"lightSize");
    uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
   
    uWorldMatrix = glGetUniformLocation(program,"worldMatrix");
    uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
    uPerspectiveInvMatrix = glGetUniformLocation(program,"perspectiveInvMatrix");
	 uNormalWorldMatrix= glGetUniformLocation(program,"normalWorldMatrix");
   
    
    
    glUseProgram(0);


    
    
    glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER,fbo );
    
    glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    //color texture
    glGenTextures(1, &pointLightTexture);
    glBindTexture(GL_TEXTURE_2D, pointLightTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA16F, w, h, 0, GL_RGBA, GL_FLOAT, 0 );
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D,pointLightTexture, 0);
  

    
    
    
    int status =glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status !=GL_FRAMEBUFFER_COMPLETE)cout << "npPointLightRenderer FBO error ::" << status << endl;
    
    
    glBindTexture( GL_TEXTURE_2D, 0 );
    glBindFramebuffer(GL_FRAMEBUFFER,0 );

    

    
}

void npPointLightRenderer::start( const npCamera &cam)
{
	glBindFramebuffer(GL_FRAMEBUFFER,fbo );
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0,width  ,height);
    glUseProgram(program);  
    
    glDepthMask(GL_FALSE);
  
    
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,depthTexture);
  
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,normalTexture);  
    
    
    glUniformMatrix4fv(uWorldMatrix, 1, 0,  cam.worldMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveMatrix, 1, 0,   cam.perspectiveMatrix.getPtr());
    glUniformMatrix4fv(uPerspectiveInvMatrix, 1, 0,   cam.perspectiveInvMatrix.getPtr());
	glUniformMatrix4fv(uNormalWorldMatrix, 1, 0,   cam.normalWorldMatrix.getPtr());
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glEnableVertexAttribArray(ATTRIB_COLOR);

}
void npPointLightRenderer::stop( )
{
	glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_NORMAL);
    glDisableVertexAttribArray(ATTRIB_COLOR);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    
     glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER,0 );   
    glDepthMask(GL_TRUE);
 

}
void npPointLightRenderer::draw( const npMultiPointLight &pLights)
{

	
        
      
        glUniform1f(uLightSize,pLights.pLight->lightSize );
       // glUniformMatrix4fv(uNormalMatrix, 1, 0,  pLights[i]->rangeSphere.normalMatrix.getPtr());
        
        glBindBuffer(GL_ARRAY_BUFFER,pLights.pLight->rangeSphere.vertexBuffer);
    
	
        glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 0));
        glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) *3 ));
        glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 6));
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pLights.pLight->rangeSphere.indexBuffer);
		for (int i =0;i< pLights.objectMatrices.size();i++){
      glUniform3f(uCenter,pLights.objectCenters[i].x,pLights.objectCenters[i].y,pLights.objectCenters[i].z);
			glUniformMatrix4fv(uObjectMatrix, 1, 0, pLights.objectMatrices[i].getPtr());
				glDrawElements(GL_TRIANGLES,pLights.pLight->rangeSphere.numIndices , GL_UNSIGNED_INT, (void*)0);
		}

}


void npPointLightRenderer::draw(const vector<npPointLight *> &pLights)
{
  
    
  
    
   
   
    for (int i=0;i<pLights.size();i++)
    {

        glUniformMatrix4fv(uObjectMatrix, 1, 0,  pLights[i]->rangeSphere.objectMatrix.getPtr());
        
        glUniform3f(uCenter,pLights[i]->rangeSphere.x,pLights[i]->rangeSphere.y,pLights[i]->rangeSphere.z );
        glUniform1f(uLightSize,pLights[i]->lightSize );
       // glUniformMatrix4fv(uNormalMatrix, 1, 0,  pLights[i]->rangeSphere.normalMatrix.getPtr());
        
        glBindBuffer(GL_ARRAY_BUFFER,pLights[i]->rangeSphere.vertexBuffer);
    
	
        glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 0));
        glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) *3 ));
        glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9,(GLvoid*) (sizeof(float) * 6));
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  pLights[i]->rangeSphere.indexBuffer);
      
   
        glDrawElements(GL_TRIANGLES,pLights[i]->rangeSphere.numIndices , GL_UNSIGNED_INT, (void*)0);
          
    }
    
    
  

    
}


