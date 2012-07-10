#pragma once

#include "npIncludes.h"

#include "Chunk.h"
#include "ObjectLib.h"
#include "perlin.h"

#include "npMultiMesh.h"
#include "TerrainVertex.h"
#include "npPointLight.h"

class Chunk;
class ObjectLib;


class TerrainFunctions {
public:
	TerrainFunctions(){};
	~TerrainFunctions(){};

	void setup();

	float getHeightForPos(float  x, float z);

	ofVec3f getNormalforPos(float x, float z);
	void getNormalforVertex( TerrainVertex &vertex);
	ofVec3f getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3);



	Perlin *heightPerlin1;
	Perlin *heightPerlin2;
	Perlin *typePerlin;

	Perlin *vegatationPerlin;
	
	ObjectLib objectLib;


	void startNewObjectsForChunk(Chunk *chunk);
	void getObjectsForVertex( TerrainVertex *vertex, Chunk *chunk);
	void stopNewObjectsForChunk(Chunk *chunk);

	
};