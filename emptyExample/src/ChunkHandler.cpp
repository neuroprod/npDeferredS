#include "ChunkHandler.h"






void ChunkHandler::update(ofVec3f camPos, ofVec3f lookPos)
{
	
	camPos.y =0;
	ofVec3f lookDir = camPos -lookPos;
	lookDir.y =0; 
	 lookDir.normalize();
	

	for(int i=0;i<chunks.size();i++)
	{
	chunks[i]->calculateDetail(camPos,lookDir);

	
	}


}