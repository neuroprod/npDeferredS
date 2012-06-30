#pragma once


#include "npIncludes.h"
#include "npMesh.h"
#include "ChunkHandler.h"
#include "Chunk.h"
class Terrain
{
public:
	Terrain(){};
	~Terrain(){};

	void setup(string heightMap,string objectMap);
	void createChunkLow(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk);
		void createChunkHigh(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk);

		void getObjects(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk);

	//void createChunkHigh(int x,int y);


	float getHeightForPixelPos(int x, int y);

	ofVec3f getNormalforPixelPos(int x, int y);
	ofVec3f getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3);
	float getHeightForWorldPos(float x, float y);

	ChunkHandler * chunkHandler;

	ofImage terainMainMap;
	ofImage	objectMainMap;
	float mainPixelSize;
	int divX;
	int divY;
	int totalWidth;
	int totalHeight;

	int chunkSizeX ;
	int chunkSizeY;





	npMesh * treeMesh;

};
