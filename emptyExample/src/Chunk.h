#pragma once


#include "npIncludes.h"
#include "npMesh.h"
#include "TerrainFunctions.h"
#include "ObjectLib.h"
#include "TerrainVertex.h"
class TerrainFunctions;
class Chunk
{
public:
	Chunk();
	~Chunk(){};
	float width ;
	float height ;

	void calculateDetail(const ofVec3f &camPos,const ofVec3f &lookDir);
	void setDetailLevel(int _detailLevel);
	TerrainVertex * getVertexForXY(int x, int y);
	void setPos(int posX ,int posY);
	void update();
	void makeTerrainObjects();
	void buildFirst();
	void clearCurrent();

	int cDivX ;
	int cDivY ;


	int posX ;	
	int posY;
	float updatePrio ;

	int numChunksW2; 

	bool isReady;

	int vpX;
	int vpY;
	int vpW;
	int vpH;

	ofVec3f center;
	vector <npMesh*> detail1Objects;
	vector <npMesh*> detail2Objects;
	vector <npMesh*> detail3Objects;
	
	int detailLevel;

	
	npMesh * terrain;

	TerrainFunctions * terrainFunctions;

	vector <TerrainVertex > terrainVertices;

	
};