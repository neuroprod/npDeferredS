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
	void updateDetailMaterial(TerrainMaterial *mat,Chunk *chunk);
	vector<TerrainMaterial *> detailMaterials;

};