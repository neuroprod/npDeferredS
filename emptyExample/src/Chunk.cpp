
#include "Chunk.h"



Chunk::Chunk(){
	
	width =20;
	height=20 ;
	posX =1000000;
	posY =10000;
	isReady =false;
	terrain = new npMesh();
	cDivX =1;
		cDivY =1;
}


void Chunk::update()
{

	if ( terrain->numVertices == -1)
	{

		buildFirst();
		return;
	} 
	
	float worldX = posX *width;
	float worldY = posY *height;



	float cStepY  = (float)height/cDivY;
	float cStepX  =(float) width/cDivX;


	npMesh * mesh = terrain;
	

	

	float  r= (float) rand()/RAND_MAX;
	
	float  g= (float) rand()/RAND_MAX;
	float  h= (float) rand()/RAND_MAX*5;
	int vertcount =0;
	for(int y=0;y<cDivY +1 ;y++)
	{
		int pPosY = y* cStepY;
		for(int x=0;x<cDivX+1;x++)
		{
			int pPosX = x* cStepX ;
	
			mesh->vertices[vertcount++] =   (float) pPosX  +worldX;
            mesh->vertices[vertcount++] =terrainFunctions-> getHeightForPos( pPosX  +worldX,(float) pPosY +worldY);
            mesh->vertices[vertcount++] =  (float) pPosY +worldY;//getHeightForPixelPos( pPosX, pPosY);
            
           ofVec3f n =  terrainFunctions->getNormalforPos((float) pPosX  +worldX, (float) pPosY +worldY);
            
            mesh->vertices[vertcount++] = n.x;
            mesh->vertices[vertcount++] =  n.y;
            mesh->vertices[vertcount++] =n.z;
            
			//mesh->vertices[vertcount++] = r;//(float)(pPosX+pixelX)/totalWidth;
            //mesh->vertices[vertcount++] =g;//(float)(pPosY+pixelY)/totalHeight;

			vertcount++;
				vertcount++;





		}
		
	}
	
	  glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER,0, mesh->numVertices*mesh->stride* sizeof(float), mesh->vertices);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	isReady =true;

}









void Chunk::setPos(int posCenterX ,int posCenterY)
{

	
	if (posCenterX-numChunksW2> posX)
	{
		
		 posX = posCenterX +numChunksW2-1;
		isReady =false;
	
	}else if (posCenterX+numChunksW2<posX)
	{
		// xRechts
		posX = posCenterX -numChunksW2+1;
		isReady =false;
	}

	if (posCenterY-numChunksW2> posY)
	{
	
		 posY = posCenterY +numChunksW2-1;
		isReady =false;
	
	}else if (posCenterY+numChunksW2<posY)
	{
		posY = posCenterY -numChunksW2+1;
		isReady =false;
	}
	

	center.set(posX*width+width/2,0,posY*height+height/2);

}










void Chunk::calculateDetail(const ofVec3f &camPos,const ofVec3f &lookDir)
{



	float dist = center.distance(camPos);
	ofVec3f dirChunk =  center-camPos; 
	 dirChunk.normalize();
	
	 float dot = lookDir.dot( dirChunk);
	 updatePrio = 1/dist ;
	 if( dot < 0)updatePrio*=-1; 

	if (dist< width*1.5)updatePrio =2;
	if (isReady ==false)
	{
	setDetailLevel(0);
	
	return;
	}
	
	
	if ( dist< width*1.5)
	{
	setDetailLevel(1);
	return;
	}
	else if( dist< width*4)
	{

		if (dot>0.1)
		{
			//
			
			setDetailLevel(2);
			//
			
			return;
		}
		setDetailLevel(0);
		
	}
	else if (dot>0.3)
	{	
			setDetailLevel(3);
			return;
	}
	setDetailLevel(0);
	
}
void Chunk::setDetailLevel(int _detailLevel)
{
	detailLevel = _detailLevel;

}








void  Chunk::buildFirst()
{
	float totalWorld = (numChunksW2*2*width);
	
	float halfWorld = totalWorld/2; 
	float worldX = posX *width;
	float worldY = posY *height;

	float cStepY  = (float)height/cDivY;
	float cStepX  =(float) width/cDivX;

		float uvXStart =(worldX+halfWorld)/ totalWorld;
	float uvYStart =(worldY+halfWorld)/ totalWorld;
	cout << uvXStart<<" " << uvYStart  << endl;;

		float uvXStep =width/totalWorld /cDivX;
	float uvYStep =height/totalWorld /cDivY;
	cout << uvXStep<<" " <<  uvYStep   << endl;;
 terrain =new npMesh();
	npMesh * mesh = terrain;
	
	mesh->stride = 8;
	mesh->numVertices =(cDivX+1) *(cDivY+1); 
	
	mesh->vertices =new float [mesh->numVertices*	mesh->stride ];

	mesh->numIndices  = (cDivX )* (cDivY ) *6 ;
	mesh->indices =new unsigned int[mesh->numIndices ];

		mesh->numIndices2  = (cDivX/4 )* (cDivY/4 ) *6 ;
	mesh->indices2 =new unsigned int[mesh->numIndices ];
	


	int vertcount =0;
	
	for(int y=0;y<cDivY +1 ;y++)
	{
		int pPosY = y* cStepY;
		for(int x=0;x<cDivX+1;x++)
		{
			int pPosX = x* cStepX ;
	
			mesh->vertices[vertcount++] =   (float) pPosX  +worldX;
            mesh->vertices[vertcount++] =terrainFunctions-> getHeightForPos( pPosX  +worldX,(float) pPosY +worldY);
            mesh->vertices[vertcount++] =  (float) pPosY +worldY;//getHeightForPixelPos( pPosX, pPosY);
            
           ofVec3f n =  terrainFunctions->getNormalforPos((float) pPosX  +worldX, (float) pPosY +worldY);
            
            mesh->vertices[vertcount++] = n.x;
            mesh->vertices[vertcount++] =  n.y;
            mesh->vertices[vertcount++] =n.z;
            
			mesh->vertices[vertcount++] =uvXStart+x*uvXStep ;//(float)(pPosX+pixelX)/totalWidth;
            mesh->vertices[vertcount++] =uvYStart+y*uvYStep;//(float)(pPosY+pixelY)/totalHeight;
	






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
	indexCount = 0;
	for(int y=0;y<cDivY ;y+=4)
	{
	
		for(int x=0;x< cDivX;x+=4)
		{
			mesh->indices2[indexCount++] = x+(y* (cDivX+1));
			
			mesh->indices2[indexCount++] = x+((y+4)* (cDivX+1));
			mesh->indices2[indexCount++] = x+4+(y* (cDivX+1));


			
			mesh->indices2[indexCount++] = x+4+((y+4)* (cDivX+1));
			mesh->indices2[indexCount++] = x+4+(y* (cDivX+1));
			mesh->indices2[indexCount++] = x+((y+4)* (cDivX+1));
		}
	
	}

	mesh->createBuffers(GL_DYNAMIC_DRAW);
	mesh->objectMatrix.makeIdentityMatrix();
	mesh->normalMatrix.makeIdentityMatrix();
	isReady =true;
}