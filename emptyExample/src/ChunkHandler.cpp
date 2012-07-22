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


