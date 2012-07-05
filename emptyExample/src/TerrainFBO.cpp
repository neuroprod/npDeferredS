
#include "TerrainFBO.h"

void TerrainFBO::setup()
{
	w =2048;
	h=2048;
	
	  glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
  
    GLuint rbuffer;
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

   
    
    
    glGenRenderbuffers(1, &rbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, rbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, w, h);
		
    
    glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);	
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,rbuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    
    GLint status =glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if(status !=GL_FRAMEBUFFER_COMPLETE)cout << "fbo interface faild\n";
    
      glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void TerrainFBO::draw(Chunk *chunk)
{
	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER,fbo );
	glViewport(chunk->vpX,chunk->vpY,chunk->vpW,chunk->vpH);

	
	  ofSetColor(0,200,255);
    ofFill();
    ofCircle(0, 0, 500);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glEnable(GL_DEPTH_TEST);
}

