#include "SkyColorBox.h"
#include "npProgramLoader.h"
void SkyColorBox::setup(){

		 skyMaterial.loadDiffuse("3DAssets/skyBoxColor.jpg",GL_RGB,false);


	npProgramLoader pLoader;
	program = pLoader.loadProgram(ofToDataPath("SkyBoxColorShader"));
	
	glBindAttribLocation(program, 0, "position");
	pLoader.linkProgram();
    glUseProgram(program);
     uPerspectiveMatrix = glGetUniformLocation(program,"perspectiveMatrix");
  glUseProgram(0);
GLfloat vertices[] = {
	  -1.0,  1.0,  1.0,  
	  -1.0, -1.0,  1.0,
	   1.0, -1.0,  1.0,
	   1.0,  1.0,  1.0,
	  -1.0,  1.0, -1.0,
	  -1.0, -1.0, -1.0,
	   1.0, -1.0, -1.0,
	   1.0,  1.0, -1.0,
	};

	glGenBuffers(1, &cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
 
	
	GLuint indices[] = {
	  0, 1, 2, 3,
	  3, 2, 6, 7,
	  7, 6, 5, 4,
	  4, 5, 1, 0,
	  0, 3, 7, 4,
	  1, 2, 6, 5,
	};
	 numIndices =4*6;
	glGenBuffers(1, &cube_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);







}

void SkyColorBox::update(){}

void SkyColorBox::draw(const GameCamera &camera){

	glBindTexture(GL_TEXTURE_2D, skyMaterial.diffuseTexture);
	
	 glUseProgram(program);
	 glEnableVertexAttribArray(0);

	



	 glUniformMatrix4fv( uPerspectiveMatrix, 1, 0, camera.skyBoxMatrix.getPtr());
	

	 glBindBuffer(GL_ARRAY_BUFFER,cube_vertices);
	
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*) 0);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_indices);
	glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_INT, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glDisableVertexAttribArray(0);


}