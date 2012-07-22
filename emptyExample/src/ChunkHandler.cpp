#include "ChunkHandler.h"
ChunkHandler::ChunkHandler()
{
	chunkSize =256/2;
	numChunksW=16*2; 
	numChunksW2=numChunksW/2;

	frameCount =0;
	 chunkParts =64/2;
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
	Chunk *chunk = getClosestChunk(pos,  detailLevel);
	ofVec2f posSearch;
 posSearch.x = pos.x;
posSearch.y= pos.z;
	posSearch.x-=chunk->center.x-chunkSize/2;
	posSearch.y-=chunk->center.z-chunkSize/2;

	posSearch.x/=4.0f;
	posSearch.y/=4.0f;

	int posX0 =floor( posSearch.x+0.5);
	int posY0 =floor(  posSearch.y+0.5);
	cout << posSearch << " "<< posX0 <<" "<<posY0 <<endl;
	TerrainVertex *v0 =  chunk->getVertexForXY( posX0,posY0);
	float dif1 = posSearch.x-posX0;
	int	posX1;
	if (dif1 <0)
	{
		posX1 =  posX0 -1;
	}else
	{
	posX1 =  posX0 +1;
	}
	
	float dif2 = posX0-posSearch.y;
	int	posY2;
	if (dif2 <0)
	{
		posY2 =  posY0 -1;
	}else
	{
		posY2 =  posY0 +1;
	}

	TerrainVertex *v1 =  chunk->getVertexForXY( posX1,posY0);
	TerrainVertex *v2 =  chunk->getVertexForXY( posX0,posY2);

	


	return *v1;
	
}
Chunk * ChunkHandler::getClosestChunk(const ofVec3f &pos, int detailLevel)
{

	ofVec3f vec;
	float maxDist =10000000000;
	Chunk *cChunk;
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


