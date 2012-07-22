#pragma once


#include "npIncludes.h"
#include "npMesh.h"
#include "npMultiMesh.h"
#include "TerrainFunctions.h"

#include "TerrainVertex.h"
#include "npPointLight.h"
#include "npMultiPointLight.h"
#include "TerrainTextureHandler.h"
#include "TerrainMaterial.h"

class TerrainTextureHandler;
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
	TerrainTextureHandler  *texureHandler;

	int cDivX ;
	int cDivY ;
	TerrainMaterial *currentDetailMaterial;

	int posX ;	
	int posY;
	float updatePrio ;

	int posXStart;
	int	posYStart;


	int numChunksW2; 

	bool isReady;

	int vpX;
	int vpY;
	int vpW;
	int vpH;

	ofVec3f center;
	vector <npMultiMesh> detail1Objects;
	vector <npMultiMesh> detail2Objects;
	vector <npMultiMesh> detail3Objects;
	
	vector <npMultiMesh> detail1ObjectsTrans;
	vector <npMultiMesh> detail2ObjectsTrans;
	vector <npMultiMesh> detail3ObjectsTrans;
	 vector <npMultiPointLight > pLights;


	int detailLevel;

	
	npMesh * terrain;

	TerrainFunctions * terrainFunctions;

	vector <TerrainVertex > terrainVertices;

	 
};