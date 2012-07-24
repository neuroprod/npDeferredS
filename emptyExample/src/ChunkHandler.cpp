#include "ChunkHandler.h"
ChunkHandler::ChunkHandler()
{
	chunkSize =256/2;
	numChunksW=16*2; 
	numChunksW2=numChunksW/2;

	frameCount =0;
	 chunkParts =64/2;
	 v0 =NULL;
	 v1 =NULL;
	 v2 =NULL;
};


void ChunkHandler::setup()
{
	 terrainFBO.cDivX = chunkParts;
 terrainFBO.cDivY = chunkParts;
	 terrainFBO.setup();
	 textureHandler.setup();

	for (int y= -numChunksW2;y<numChunksW2;y++)
	{
		for (int x= -numChunksW2;x<numChunksW2;x++)
		{
				Chunk * chunk = new Chunk();
				chunk->texureHandler = &textureHandler;
				chunk->posX = x;
				chunk->posY= y;
				chunk-> posXStart =x;
				chunk-> posYStart =y;
				chunk->numChunksW2 = numChunksW2;
				chunk->width  =  chunkSize;
				chunk->height  =  chunkSize;
				chunk->cDivX  =  chunkParts;
				chunk->cDivY  =  chunkParts;
				chunk->terrainFunctions  =terrainFunctions;
				chunks.push_back(chunk);
		
		}
	}

}
TerrainVertex  ChunkHandler::getVertexforPos(const ofVec3f &pos, int detailLevel)
{
	TerrainVertex  vert ;
	vert.position.y =0;

	Chunk *chunk = getClosestChunk(pos,  detailLevel);
	if (chunk==NULL) {
	return vert;
	}

	ofVec2f posSearch;
	posSearch.x = pos.x;
	posSearch.y= pos.z;
	posSearch.x-=chunk->center.x-chunkSize/2;
	posSearch.y-=chunk->center.z-chunkSize/2;

	posSearch.x/=4.0f;
	posSearch.y/=4.0f;

	int posX0 =floor( posSearch.x+0.5);
	int posY0 =floor(  posSearch.y+0.5);

	v0 =  chunk->getVertexForXY( posX0,posY0);
	float difx = posSearch.x-posX0;
	float dify = posSearch.y;
	int	posX1= posX0 ;
	int	posX2= posX0 ;
	int	posY1= posY0 ;
	int	posY2= posY0 ;

	if (pos.x <v0->position.x)
	{
		if (pos.z >v0->position.z)
		{
			posX2-=1;
			posY2+=1;
	
			v1 =  chunk->getVertexForXY( posX0-1,posY0);
			v2 =  chunk->getVertexForXY( posX0,posY0+1);

			if(pos.distance(v1->position)<pos.distance(v2->position))
			{
				posX1-=1;
			
			
			}else
			{
				posY1+=1;
				
			}

		}else
		{
			
			posY2-=1;
			posX1-=1;
		}
	}else
	{
		if (pos.z >v0->position.z)
		{
			posY2+=1;
			posX1+=1;
		
		}else
		{
			posX2+=1;
			posY2-=1;
		
			v1 =  chunk->getVertexForXY( posX0+1,posY0);
			v2 =  chunk->getVertexForXY( posX0,posY0-1);
			if(pos.distance(v1->position)<pos.distance(v2->position))
			{
				posX1+=1;
				
			}
			else
			{
				posY1-=1;
					
			}

		}
	}
	

	v1 =  chunk->getVertexForXY( posX1,posY1);
	v2 =  chunk->getVertexForXY( posX2,posY2);


	ofVec3f normal= terrainFunctions->getNormal(v0->position,v1->position,v2->position);

	///
	
	ofVec3f  rayStartPoint;
	rayStartPoint.set(pos.x,10000,pos.z);
	ofVec3f  raydir;
	raydir.set(0,-1,0);
	if (normal.y<0)normal*=-1;
	ofVec3f  tv0 = rayStartPoint -v0->position;    
	float a  = normal.dot(tv0);
	float b = normal.dot(raydir);
			
				
		
                   
                   
	float r  = -a / b;
			
		
                

	ofVec3f intersectionPoint ;
	intersectionPoint.set(rayStartPoint.x + (raydir.x * r), rayStartPoint.y + (raydir.y * r), rayStartPoint.z + (raydir.z * r));
	vert.position = intersectionPoint;

	



	ofVec3f vp1,vp2,vp0;
	vp0.set(v0->position.x,v0->position.y,v0->position.z);
	vp1.set(v1->position.x,v1->position.y,v1->position.z);
	vp2.set(v2->position.x,v2->position.y,v2->position.z);
	
	float  b0  = barMass(intersectionPoint, vp1, vp2);
	float  b1  = barMass(intersectionPoint, vp0, vp2);
	float  b2  = barMass(intersectionPoint, vp0, vp1);
	
	float  bn = b0 + b1 + b2;
	b0 /= bn;
	b1 /= bn;
	b2 /= bn;
	
	
	vert.normal=(v0->normal *b0)+(v1->normal *b1)+(v2->normal *b2);
	return vert;
	
}
float ChunkHandler::barMass(const ofVec3f &p, const ofVec3f &l0 , const ofVec3f &l1)
{
	
			ofVec3f v  = l0 -l1;
			ofVec3f w = p -l0;

			float c1= v.dot(w);
			float  c2  = v.dot(v);
			float  b = c1 / c2;
			v.scale(b);
			ofVec3f pB = l0 +v;
			ofVec3f t1  = pB-p ;
			ofVec3f t2  = l0-l1 ;
			return t1.length() * t2.length();
}

Chunk * ChunkHandler::getClosestChunk(const ofVec3f &pos, int detailLevel)
{

	ofVec3f vec;
	float maxDist =1000000;
	Chunk *cChunk =NULL;
	for (int i=0;i< chunks.size(); ++i)
	{
		if (chunks[i]->detailLevel>detailLevel)break;
	       vec =   chunks[i]->center -pos;
		   float ds = vec.lengthSquared();
		   if (ds<maxDist)
		   {
		   cChunk = chunks[i];
		   maxDist = ds ; 
		   }
	}
	return cChunk;

}
void ChunkHandler::update(ofVec3f camPos, ofVec3f lookPos)
{
	camPos.y =0;
	ofVec3f lookDir = camPos -lookPos;
	lookDir.y =0; 
	lookDir.normalize();
	
	for (int i=0;i< chunks.size(); ++i)
	{
	
	chunks[i]->calculateDetail(camPos,lookDir);
	
	}


	

	unsigned updateTime =frameCount%2;

	if (updateTime ==0)
	{
		

		int xPos = camPos.x ;
		int chunkPosX = xPos/chunkSize; 
		int yPos = camPos.z ;
		int chunkPosY= yPos/chunkSize;  
	
		checkChunkPositions( chunkPosX, chunkPosY);
	
	}if (updateTime ==1)
	{
		updateChunkPositions();
		
	}



	

	frameCount++;

}

void ChunkHandler::updateChunkPositions()
{
	//cout <<endl;
	
	for (int i=0;i< chunks.size(); ++i)
	{
		//if (chunks[i]->detailLevel==1 )cout << chunks[i]->detailLevel;
	
		if (!chunks[i]->isReady)
		{
			
			chunks[i]->update();
			 terrainFBO.draw(chunks[i]);

			return;
		
		}
	
	}
	

}




void ChunkHandler::checkChunkPositions(int _x,int _y)
{
	int count = 0;





	for (int y= -numChunksW2;y<numChunksW2;y++)
	{
		for (int x= -numChunksW2;x<numChunksW2;x++)
		{
				
				chunks[count]->setPos( _x, _y);
				count++;
				
		}
	}

	sort ( chunks.begin(), chunks.end(), ComparePrio() );
}


