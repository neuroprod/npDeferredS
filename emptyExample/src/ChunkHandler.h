#pragma once


#include "npIncludes.h"
#include "Chunk.h"
#include "TerrainFunctions.h"
#include "TerrainFBO.h"
#include "TerrainTextureHandler.h"
#include "TerrainVertex.h"
struct ComparePrio 
{
  bool operator () ( Chunk * a, Chunk * b )
  {
	return a->updatePrio > b->updatePrio;
  }
};



class ChunkHandler
{
public:
	ChunkHandler();
	~ChunkHandler(){};
	void setup();
	void update( ofVec3f camPos,const ofVec3f lookDir);
	void checkChunkPositions(int x,int y);
	void updateChunkPositions();

	vector <Chunk *> chunks;
	
	unsigned long frameCount;
	int numChunksW ;
	int numChunksW2; 

	int chunkSize;
	int chunkParts;
	 GLuint texture;
	TerrainFunctions *terrainFunctions;

	Chunk *getClosestChunk(const ofVec3f &pos, int detailLevel =1);
	TerrainVertex getVertexforPos(const ofVec3f &pos, int detailLevel =1);
	float barMass(const ofVec3f &p, const ofVec3f &l0 , const ofVec3f &l1);
	TerrainFBO terrainFBO;
	TerrainTextureHandler textureHandler;


	TerrainVertex *v0;
	TerrainVertex *v1;
	TerrainVertex *v2;
};

