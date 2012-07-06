#pragma once

#include "npIncludes.h"
#include "ObjectLib.h"
#include "perlin.h"
#include "Chunk.h"

class Chunk;

class TerrainFunctions {
public:
	TerrainFunctions(){};
	~TerrainFunctions(){};

	void setup();

	float getHeightForPos(float  x, float z);

	ofVec3f getNormalforPos(float x, float z);
	ofVec3f getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3);



	Perlin *heightPerlin1;
	Perlin *heightPerlin2;
	Perlin *typePerlin;

	Perlin *vegatationPerlin;
	
	ObjectLib objectLib;
	void startNewChunk();
	void getObjectsForPos(float x, float y); 
	void stopNewChunk(Chunk *chunk);
	vector <npMesh *> tempObjects;

};