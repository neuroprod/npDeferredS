#pragma once


#include "npIncludes.h"
#include "TerrainFunctions.h"
#include "Chunk.h"
class TerrainFBO
{
public:
	TerrainFBO(){}
	void setup();


	void draw(Chunk *chunk);
	GLuint fbo;

    GLuint texture;

	int numSamples;
    int w;
    int h;
	
};