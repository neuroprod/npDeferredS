#include "SkyBoxElements.h"
#include "npProgramLoader.h"
void SkyBoxElements::setup(){




	stars.setup();




	sunMaterial.loadDiffuse("3DAssets/sun.png",GL_RGBA,false);
	starsMaterial.loadDiffuse("3DAssets/stars.png",GL_RGBA,false);

	npProgramLoader pLoader;
	program = pLoader.loadProgram(ofToDataPath("SkyBoxTextureShader"));
	
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "uv");
	pLoader.linkProgram();
    glUseProgram(program);
     uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
	  uObjectMatrix = glGetUniformLocation(program,"objectMatrix");
  glUseProgram(0);

  
  

	

	sunVertices = new float[16];
	sunVertices[0] = -1;
	sunVertices[1] = -1;

	sunVertices[2] = 0;
	sunVertices[3] = 0;

	sunVertices[4] = -1;
   sunVertices[5] = 1;
	sunVertices[6] = 0;
	sunVertices[7] = 1;

	sunVertices[8] = 1;
	sunVertices[9] = 1;
	sunVertices[10] = 1;
	sunVertices[11] = 1;

	sunVertices[12] = 1;
	sunVertices[13] = -1;
	sunVertices[14] = 1;
	sunVertices[15] = 0;
	

}

void SkyBoxElements::update(){}

void SkyBoxElements::draw(const GameCamera &camera,const float &time){

	 glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ofMatrix4x4	objectMatrix;

	glUseProgram(program);
	glUniformMatrix4fv( uPerspectiveMatrix, 1, 0,camera.skyBoxMatrix.getPtr());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// stars

	objectMatrix.makeIdentityMatrix();
	objectMatrix.glRotate(time*360,1,0,0);
	glUniformMatrix4fv( uObjectMatrix, 1, 0,objectMatrix.getPtr());  
	glBindTexture(GL_TEXTURE_2D, starsMaterial.diffuseTexture);
	float * pointer = stars.vertices;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),pointer);
	pointer+=3;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,5*sizeof(float), pointer);
	glDrawArrays(GL_QUADS,0,4*	stars.numStars);



	// sun 

	ofVec4f p= light->pos;
	p.normalize();
	objectMatrix.makeLookAtMatrix(p,ofVec3f(0,0,0),ofVec3f(0,1,0.0));
	glUniformMatrix4fv( uObjectMatrix, 1, 0,objectMatrix.getPtr());  
	glBindTexture(GL_TEXTURE_2D, sunMaterial.diffuseTexture);
	 pointer = sunVertices;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float),pointer);
	pointer+=2;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,4*sizeof(float), pointer);
	glDrawArrays(GL_QUADS,0,4);

	

	glUseProgram(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	 glDisable(GL_BLEND);
}