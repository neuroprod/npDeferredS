#include "Terrain.h"

void Terrain::setup(string heightMap)
{

	mainPixelSize =0.8f;
    terainMainMap.loadImage(heightMap);
	terainMainMap.setImageType(OF_IMAGE_COLOR);

	divX =8;
	divY =8;
	totalWidth = terainMainMap.width;
	totalHeight = terainMainMap.height;
	
	chunkSizeX = totalWidth/divX;
	chunkSizeY = totalHeight/divY;
	
	int startX = chunkSizeX * (divX/-2);
	int startY =chunkSizeY * (divY/-2);

	for(int y=0;y<divY ;y++)
	{
		for(int x=0;x<divX;x++)
		{
			Chunk * chunk =new Chunk();
			createChunkLow(x*chunkSizeX,y*chunkSizeY,(float) (startX +x*chunkSizeX)*mainPixelSize,(float) (startY +y*chunkSizeY)*mainPixelSize,chunk );
			createChunkHigh(x*chunkSizeX,y*chunkSizeY,(float) (startX +x*chunkSizeX)*mainPixelSize,(float) (startY +y*chunkSizeY)*mainPixelSize,chunk );
			chunk->center.set((startX +x*chunkSizeX)*mainPixelSize  +  (chunkSizeX/2)*mainPixelSize ,0,(startY +y*chunkSizeY)*mainPixelSize  +  (chunkSizeY/2)*mainPixelSize  );
			chunkHandler->chunks.push_back( chunk );
		}
	}

	


}
void Terrain::createChunkLow(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk)
{
		
	int cDivX = 64;
	int cDivY = 64;
	int cStepX = chunkSizeX/ cDivX;
	int cStepY = chunkSizeY/ cDivY;

	//int startX = x*  (terainMainMap.width/8);
	//int startX = y*  (terainMainMap.height/8);
	
	chunk->terrainLowRes  =new npMesh();
	npMesh * mesh = chunk->terrainLowRes;
	mesh->stride = 9;
	mesh->numVertices =(cDivX+1) *(cDivY+1); 
	mesh->vertices =new float [mesh->numVertices*	mesh->stride ];

	mesh->numIndices  = (cDivX )* (cDivY ) *6 ;
	mesh->indices =new unsigned int[mesh->numIndices ];

	float  r= (float) rand()/RAND_MAX*0.3 +0.7;

	int vertcount =0;
	for(int y=0;y<cDivY +1 ;y++)
	{
		int pPosY = y* cStepY;
		for(int x=0;x<cDivX+1;x++)
		{
			int pPosX = x* cStepX ;

			mesh->vertices[vertcount++] =   (float) pPosX*mainPixelSize  +worldX;
            mesh->vertices[vertcount++] =  getHeightForPixelPos( pPosX+pixelX, pPosY+pixelY);
            mesh->vertices[vertcount++] =  (float) pPosY*mainPixelSize  +worldY;//getHeightForPixelPos( pPosX, pPosY);
            
           ofVec3f n =  getNormalforPixelPos(pPosX+pixelX, pPosY+pixelY);
            
            mesh->vertices[vertcount++] =  n.x;
            mesh->vertices[vertcount++] =  n.y;
            mesh->vertices[vertcount++] = n.z;
            
			mesh->vertices[vertcount++] = r;
            mesh->vertices[vertcount++] =0;
            mesh->vertices[vertcount++] =0;







		}
		
	}
	int indexCount = 0;
	for(int y=0;y<cDivY ;y++)
	{
	
		for(int x=0;x< cDivX;x++)
		{
			mesh->indices[indexCount++] = x+(y* (cDivX+1));
			
			mesh->indices[indexCount++] = x+((y+1)* (cDivX+1));
			mesh->indices[indexCount++] = x+1+(y* (cDivX+1));


			
			mesh->indices[indexCount++] = x+1+((y+1)* (cDivX+1));
			mesh->indices[indexCount++] = x+1+(y* (cDivX+1));
			mesh->indices[indexCount++] = x+((y+1)* (cDivX+1));
		}
	
	}
	mesh->createBuffers();
	mesh->objectMatrix.makeIdentityMatrix();
	mesh->calculateNormalMatrix();

	


}


void Terrain::createChunkHigh(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk)
{
		
	int cDivX = 256;
	int cDivY = 256;
	int cStepX = chunkSizeX/ cDivX;
	int cStepY = chunkSizeY/ cDivY;

	//int startX = x*  (terainMainMap.width/8);
	//int startX = y*  (terainMainMap.height/8);
	
	chunk->terrainHighRes  =new npMesh();
	npMesh * mesh = chunk->terrainHighRes;
	mesh->stride = 9;
	mesh->numVertices =(cDivX+1) *(cDivY+1); 
	mesh->vertices =new float [mesh->numVertices*	mesh->stride ];

	mesh->numIndices  = (cDivX )* (cDivY ) *6 ;
	mesh->indices =new unsigned int[mesh->numIndices ];

	float  r= (float) rand()/RAND_MAX*0.3 +0.7;

	int vertcount =0;
	for(int y=0;y<cDivY +1 ;y++)
	{
		int pPosY = y* cStepY;
		for(int x=0;x<cDivX+1;x++)
		{
			int pPosX = x* cStepX ;

			mesh->vertices[vertcount++] =   (float) pPosX*mainPixelSize  +worldX;
            mesh->vertices[vertcount++] =  getHeightForPixelPos( pPosX+pixelX, pPosY+pixelY);
            mesh->vertices[vertcount++] =  (float) pPosY*mainPixelSize  +worldY;//getHeightForPixelPos( pPosX, pPosY);
            
           ofVec3f n =  getNormalforPixelPos(pPosX+pixelX, pPosY+pixelY);
            
            mesh->vertices[vertcount++] =  n.x;
            mesh->vertices[vertcount++] =  n.y;
            mesh->vertices[vertcount++] = n.z;
            
			mesh->vertices[vertcount++] = 0;
            mesh->vertices[vertcount++] =r;
            mesh->vertices[vertcount++] =0;







		}
		
	}
	int indexCount = 0;
	for(int y=0;y<cDivY ;y++)
	{
	
		for(int x=0;x< cDivX;x++)
		{
			mesh->indices[indexCount++] = x+(y* (cDivX+1));
			
			mesh->indices[indexCount++] = x+((y+1)* (cDivX+1));
			mesh->indices[indexCount++] = x+1+(y* (cDivX+1));


			
			mesh->indices[indexCount++] = x+1+((y+1)* (cDivX+1));
			mesh->indices[indexCount++] = x+1+(y* (cDivX+1));
			mesh->indices[indexCount++] = x+((y+1)* (cDivX+1));
		}
	
	}
	mesh->createBuffers();
	mesh->objectMatrix.makeIdentityMatrix();
	mesh->calculateNormalMatrix();

	


}






float Terrain::getHeightForPixelPos(int x, int y)
{
	
	if (x>=2048)
	{
	return 0;
	}
		if (y>=2048)
	{
	return 0;
	}
	float pixelVal =  (float ) terainMainMap.getPixels()[(x+y*2048)*3];

	float height = pixelVal/256.0f   *8;
	return (height * height)-2 ;
}

ofVec3f  Terrain::getNormalforPixelPos(int x, int y)
{

	ofVec3f normal;
	normal.set(0,0,0);
	normal+= getNormal( ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y),mainPixelSize* y) , ofVec3f(mainPixelSize *(x+1),getHeightForPixelPos(x+1,y),mainPixelSize* y)   , ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y+1),mainPixelSize* (y+1))                              );
	normal.normalize();

	return normal;


}
ofVec3f  Terrain::getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3)
{
	ofVec3f d1  = p1-p2;
	ofVec3f d2 = p1-p3;

	return d2.getCrossed( d1 ).normalize();
}


float Terrain::getHeightForWorldPos(float x, float y)
{
	
	return 	getHeightForPixelPos( x/mainPixelSize +terainMainMap.width/2,y/mainPixelSize+terainMainMap.height/2);

}

