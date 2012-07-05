#pragma once


#include "npIncludes.h"
#include "Chunk.h"
#include "TerrainFunctions.h"
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
	TerrainFunctions *terrainFunctions;
};

