#pragma once


#include "npIncludes.h"
#include "Chunk.h"

class ChunkHandler
{
public:
	ChunkHandler(){};
	~ChunkHandler(){};
	void setup(){};
	void update( ofVec3f camPos,const ofVec3f lookDir);
	
	vector <Chunk *> chunks;
	


};