
#include "TerrainFBO.h"
#include "npProgramLoader.h"
#include "npMaterial.h"
void TerrainFBO::setup()
{
	w =2048*2;
	h=2048*2;
	setupProgram();
	setupFBO();
	setupDrawData();

	npMaterial mat;
	mat.loadDiffuse("3DAssets/terrainNoise.png");
	textureNoise  = mat.diffuseTexture;







}


void TerrainFBO::draw(Chunk *chunk)
{
	int vertcount =0;
	for(int y=0;y<cDivY +1 ;y++)
	{
		
		for(int x=0;x<cDivX+1;x++)
		{
			TerrainVertex * vp = chunk->getVertexForXY(x,y);

			//pos
			vertcount++;
			vertcount++;
			//color
			
			vertices[vertcount++] =  vp->color.x;
            vertices[vertcount++] = vp->color.y;
			vertices[vertcount++] = vp->color.z;


			//uv
			vertcount++;
			vertcount++;
		}
	}

	glDisable(GL_DEPTH_TEST);
	glUseProgram(program);
	glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    glEnableVertexAttribArray(ATTRIB_UV);
	glBindFramebuffer(GL_FRAMEBUFFER,fbo );
	glViewport(chunk->vpX,chunk->vpY,chunk->vpW,chunk->vpH);
	glBindTexture(GL_TEXTURE_2D,textureNoise);
	/////////////////////draw


	float * pointer = vertices;
	glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride,pointer);
	pointer += 2;
	glVertexAttribPointer(ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride,pointer);
    pointer += 3;
	glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride,pointer);
    
 
    glDrawElements(GL_TRIANGLES,numIndices , GL_UNSIGNED_INT, (void*)indices);







	/////////////////////////
	
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(0);
	glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_COLOR);
    glDisableVertexAttribArray(ATTRIB_UV);
}


void 	TerrainFBO::setupDrawData()
{
	stride = 7;
	numVertices =(cDivX+1) *(cDivY+1); 
	
	vertices =new float [numVertices*	stride ];

	numIndices  = (cDivX )* (cDivY ) *6 ;
	indices =new unsigned int[numIndices ];


	
	float cStepY  =2.0f/cDivY;
	float cStepX  =2.0f/cDivX;
	int vertcount =0;

	for(int y=0;y<cDivY +1 ;y++)
	{
		float pPosY = (float)y* cStepY  -1.0f;
		for(int x=0;x<cDivX+1;x++)
		{
			float pPosX =(float) x* cStepX-1.0f;
			
			vertices[vertcount++] = pPosX ;
            vertices[vertcount++] = pPosY ;
          
            
         
            
            vertices[vertcount++] = 0;
            vertices[vertcount++] = 0;
           vertices[vertcount++] = 0;



		
			vertices[vertcount++] =(float)x/(cDivX +1) ;
            vertices[vertcount++] =(float)y/(cDivY +1);
	






		}
		
	}
	int indexCount = 0;
	for(int y=0;y<cDivY ;y++)
	{
	
		for(int x=0;x< cDivX;x++)
		{
			indices[indexCount++] = x+(y* (cDivX+1));
			
			indices[indexCount++] = x+((y+1)* (cDivX+1));
			indices[indexCount++] = x+1+(y* (cDivX+1));


			
			indices[indexCount++] = x+1+((y+1)* (cDivX+1));
			indices[indexCount++] = x+1+(y* (cDivX+1));
			indices[indexCount++] = x+((y+1)* (cDivX+1));
		}
	
	}

}

void 	TerrainFBO::setupProgram()
{
	 npProgramLoader pl;
    program = pl.loadProgram ("TerrainShader");

    glBindAttribLocation(program,ATTRIB_VERTEX,"position");
    glBindAttribLocation(program,ATTRIB_COLOR,"color");
    glBindAttribLocation(program,ATTRIB_UV,"uv");


    pl.linkProgram();
    glUseProgram(program);
  
    glUseProgram(0);

}
void TerrainFBO::setupFBO()
{
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