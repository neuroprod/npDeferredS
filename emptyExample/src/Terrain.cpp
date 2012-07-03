#include "Terrain.h"
#include "npSphere.h"
#include "npAssimpLoader.h"

void Terrain::setup(string heightMap,string objectMap)
{
	heightMacroPerlin=new Perlin(5,1,1,rand());
heightMicroPerlin  =new Perlin(2,1,1,rand());
vegetationPerlin=new Perlin(2,1,1,rand());

	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/treeTest.dae"));
	treeMesh = loader.meshes[0];
	treeMesh->material.loadDiffuse("3DAssets/tree1.png",GL_RGB );
	treeMesh->material.loadNormal("3DAssets/tree1_n.png",GL_RGB );



	mainPixelSize =1.0f;
  
	divX =16;
	divY =16;
	totalWidth =2048;
	totalHeight = 2048;
	
	chunkSizeX = totalWidth/divX;
	chunkSizeY = totalHeight/divY;
	
	int startX = chunkSizeX * (divX/-2);
	int startY =chunkSizeY * (divY/-2);

	for(int y=0;y<divY ;y++)
	{
		for(int x=0;x<divX;x++)
		{
			Chunk * chunk =new Chunk();

			getObjects(x*chunkSizeX,y*chunkSizeY,(float) (startX +x*chunkSizeX)*mainPixelSize,(float) (startY +y*chunkSizeY)*mainPixelSize,chunk);

			createChunkLow(x*chunkSizeX,y*chunkSizeY,(float) (startX +x*chunkSizeX)*mainPixelSize,(float) (startY +y*chunkSizeY)*mainPixelSize,chunk );
			createChunkHigh(x*chunkSizeX,y*chunkSizeY,(float) (startX +x*chunkSizeX)*mainPixelSize,(float) (startY +y*chunkSizeY)*mainPixelSize,chunk );
			chunk->center.set((startX +x*chunkSizeX)*mainPixelSize  +  (chunkSizeX/2)*mainPixelSize ,0,(startY +y*chunkSizeY)*mainPixelSize  +  (chunkSizeY/2)*mainPixelSize  );
			chunkHandler->chunks.push_back( chunk );
		}
	}

	


}
void Terrain::createChunkLow(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk)
{
		
	int cDivX = 32;
	int cDivY = 32;
	int cStepX = chunkSizeX/ cDivX;
	int cStepY = chunkSizeY/ cDivY;

	//int startX = x*  (terainMainMap.width/8);
	//int startX = y*  (terainMainMap.height/8);
	
	chunk->terrainLowRes  =new npMesh();
	npMesh * mesh = chunk->terrainLowRes;
	mesh->stride = 8;
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
            
		mesh->vertices[vertcount++] = (float)(pPosX+pixelX)/totalWidth;
            mesh->vertices[vertcount++] =(float)(pPosY+pixelY)/totalHeight;







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
		
	int cDivX = 256/4;
	int cDivY = 256/4;
	int cStepX = chunkSizeX/ cDivX;
	int cStepY = chunkSizeY/ cDivY;

	//int startX = x*  (terainMainMap.width/8);
	//int startX = y*  (terainMainMap.height/8);
	
	chunk->terrainHighRes  =new npMesh();
	npMesh * mesh = chunk->terrainHighRes;
	mesh->stride = 8;
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
            
			mesh->vertices[vertcount++] = (float)(pPosX+pixelX)/totalWidth;
            mesh->vertices[vertcount++] =(float)(pPosY+pixelY)/totalHeight;






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




void Terrain::getObjects(int pixelX,int pixelY,float worldX,float worldY,Chunk *chunk)
{
		
	int cDivX = 256/2;
	int cDivY = 256/2;
	int cStepX = 1;
	int cStepY = 1;
	npMesh *treeMeshL =treeMesh->getGLCopy();

	for(int y=0;y<cDivY -1 ;y++)
	{
		int pPosY = y* cStepY;
		for(int x=0;x<cDivX-1;x++)
		{
			int pPosX = x* cStepX ;
			ofVec3f worldPos;
			worldPos.set( (float) pPosX*mainPixelSize  +worldX,  getHeightForPixelPos( pPosX+pixelX, pPosY+pixelY),(float) pPosY*mainPixelSize  +worldY);
				
		float veg =  vegetationPerlin->Get(worldPos.x/1000.1, worldPos.z/1000.1)+0.5;
		
		if (veg>0.5 && worldPos.y <100){

			int b = rand()%1000;
		
			if (b==1)
			{
			
			
				
				ofMatrix4x4 objMatrix;
				objMatrix.makeRotationMatrix(90,ofVec3f(1,0,0) );
				objMatrix.postMultRotate(  (float)rand()/RAND_MAX *360.0f,0,1,0);
				float s = (float)rand()/RAND_MAX *0.4 +0.8;
				objMatrix.postMultScale(ofVec3f(s,s,s));

				objMatrix.postMultTranslate(worldPos);
				
				
				
				treeMeshL->objectMatrices.push_back(objMatrix);
				
			
			}

			
          
		}





		}
		
	}
	
	if(treeMeshL->objectMatrices.size()>0)
	{
		treeMeshL->isMultiObject =true;
	treeMeshL->calculateNormalMatrix();
	chunk->objects.push_back(treeMeshL);
	}else 
	{

		// chek for leaks;
//	delete treeMeshL;
	
	}
	


}



float Terrain::getHeightForPixelPos(int x, int y)
{
	float heightMac  =heightMacroPerlin->Get((float) x/1500.1, float(y)/1500.1)+0.5+0.3 ;
	heightMac =  heightMac*heightMac*heightMac*100;
	//float heightMic  = heightMicroPerlin->Get((float) x/10.1, float(y)/10.1)*heightMac/50;
	return heightMac  ;
}

ofVec3f  Terrain::getNormalforPixelPos(int x, int y)
{

	ofVec3f normal;
	normal.set(0,0,0);
	normal+= getNormal( ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y),mainPixelSize* y) , ofVec3f(mainPixelSize *(x+1),getHeightForPixelPos(x+1,y),mainPixelSize* y)   , ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y+1),mainPixelSize* (y+1))                              );
	normal+= getNormal( ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y),mainPixelSize* y) , ofVec3f(mainPixelSize *(x),getHeightForPixelPos(x,y-1),mainPixelSize* (y-1))   , ofVec3f(mainPixelSize *(x+1),getHeightForPixelPos((x+1),y+1),mainPixelSize* (y+1)) );
	normal+= getNormal( ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y),mainPixelSize* y) , ofVec3f(mainPixelSize *(x-1),getHeightForPixelPos(x-1,y),mainPixelSize* (y))   , ofVec3f(mainPixelSize *(x-1),getHeightForPixelPos((x-1),y-1),mainPixelSize* (y-1)) );
	normal+= getNormal( ofVec3f(mainPixelSize *x,getHeightForPixelPos(x,y),mainPixelSize* y) , ofVec3f(mainPixelSize *(x),getHeightForPixelPos(x,y+1),mainPixelSize* (y+1))   , ofVec3f(mainPixelSize *(x-1),getHeightForPixelPos((x-1),y),mainPixelSize* (y)) );
	normal.normalize();

	return normal;


}
ofVec3f  Terrain::getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3)
{
	ofVec3f d1  = p1-p2;
	ofVec3f d2 = p1-p3;

	return d2.getCrossed( d1).normalize();
}


float Terrain::getHeightForWorldPos(float x, float y)
{
	
	return 	getHeightForPixelPos( x/mainPixelSize +totalWidth/2,y/mainPixelSize+totalHeight/2);

}

