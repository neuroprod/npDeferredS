#pragma once


#include "npIncludes.h"
#include "TerrainFunctions.h"
#include "Chunk.h"
class TerrainFBO
{
public:
	TerrainFBO(){}
	void setup();
	void 	setupProgram();
	void setupFBO();
	void setupDrawData();
	void draw(Chunk *chunk);
	GLuint fbo;
	 GLuint textureNoise;
    GLuint texture;
	GLint program;
   
	float * vertices;
	unsigned *indices;
	int numIndices;
	int numVertices;
	int stride;
	int cDivX;
	int cDivY;
    enum {
        ATTRIB_VERTEX,
        ATTRIB_COLOR,
        ATTRIB_UV,
	};

	int numSamples;
    int w;
    int h;
	
};