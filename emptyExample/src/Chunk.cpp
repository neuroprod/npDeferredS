
#include "Chunk.h"

void Chunk::calculateDetail(const ofVec3f &camPos,const ofVec3f &lookDir)
{
	float dist = center.distance(camPos);
	ofVec3f dirChunk =  center-camPos; 
	 dirChunk.normalize();
	
	 float dot = lookDir.dot( dirChunk);
	
	if ( dist< 200)
	{
	setDetailLevel(1);
	
	}
	else 
	{

		if (dot<0.1)
		{
			//
			
			setDetailLevel(0);
			//
			
			return;
		}

		setDetailLevel(2);
	}
	
}
void Chunk::setDetailLevel(int _detailLevel)
{
	detailLevel = _detailLevel;

}