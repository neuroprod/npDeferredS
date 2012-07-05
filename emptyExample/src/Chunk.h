#pragma once


#include "npIncludes.h"
#include "npMesh.h"
#include "TerrainFunctions.h"
class Chunk
{
public:
	Chunk();
	~Chunk(){};
	float width ;
	float height ;

	void calculateDetail(const ofVec3f &camPos,const ofVec3f &lookDir);
	void setDetailLevel(int _detailLevel);

	void setPos(int posX ,int posY);
	void update();
	void buildFirst();


	int cDivX ;
	int cDivY ;


	int posX ;	
	int posY;
	float updatePrio ;

	int numChunksW2; 

	bool isReady;



	ofVec3f center;
	vector <npMesh*> objects;

	int detailLevel;

	
	npMesh * terrain;

	TerrainFunctions *terrainFunctions;
	
};