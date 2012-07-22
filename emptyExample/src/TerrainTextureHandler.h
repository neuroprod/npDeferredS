#pragma once
#include "Chunk.h"
#include "TerrainMaterial.h"
class Chunk;

class TerrainTextureHandler
{

public:
	TerrainTextureHandler(){};
	void setup();
	void getChunkMaterial(Chunk *chunk);



};