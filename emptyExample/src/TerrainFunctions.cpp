
#include "TerrainFunctions.h"

void TerrainFunctions::setup()
{

	objectLib.setup();
	srand(3);
	heightPerlin1 = new Perlin(5,1,1,122335);
	
	heightPerlin2= new Perlin(3,1,1,1223);
	typePerlin= new Perlin(8,1,1,123);	


	vegatationPerlin =new Perlin(5,1,1,125523);
}

float TerrainFunctions::getHeightForPos(float  x, float z)
{
	
	float heightMac1  =heightPerlin1->Get(x/1500.1, z/1500.1)+0.5+0.3 ;
	heightMac1 =  heightMac1*heightMac1*heightMac1*100;
	if (heightMac1 >70)
	{
		float tp =typePerlin->Get(x/1500.1, z/1500.1)*2;
		if (tp >0)
		{
		
			float heightMac2  =heightPerlin2->Get(x/250.1, z/250.1)+0.5+0.1 ;
			heightMac2 =  heightMac2*heightMac2*heightMac2*50;
			if (tp >0.5)
			{
				heightMac1=  heightMac2+50;
			}else
			{
				tp*=2;
				heightMac1 = heightMac1 *(1-tp) +( heightMac2+50)*(tp);
			
			}

		}
	}
	return heightMac1 ;

}

ofVec3f TerrainFunctions::getNormalforPos(float x, float z)
{

	ofVec3f normal;
	
	normal= getNormal( ofVec3f(x,getHeightForPos(x,z), z) , ofVec3f(x+0.5,getHeightForPos(x+0.5,z), z)   , ofVec3f(x,getHeightForPos(x,z+0.5),(z+0.5)) );
	

	return normal;


}
ofVec3f  TerrainFunctions::getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3)
{
	ofVec3f d1  = p1-p2;
	ofVec3f d2 = p1-p3;

	return d2.getCrossed( d1).normalize();
}





//
//
//   OBJECTS
//
//





void TerrainFunctions::startNewChunk()
{
	tempObjects =objectLib.getGLClones();


}

void TerrainFunctions::getObjectsForPos(float x, float y)
{
	int r  = rand();
	if (r%2 ==0)return;
	r  = rand();
	float height = getHeightForPos( x,  y);
	ofVec3f worldPos;
	worldPos.set(x,height,y);

	float veg  = vegatationPerlin->Get(x/1500.1, y/1500.1)*2;
	
	if ( veg>0.2)
	{
	if (r%25==1){
			ofMatrix4x4 objMatrix;
			objMatrix.makeRotationMatrix(90,ofVec3f(1,0,0) );
			objMatrix.postMultRotate(  (float)rand()/RAND_MAX *360.0f,0,1,0);
			float s = (float)rand()/RAND_MAX *0.4 +0.8;
			objMatrix.postMultScale(ofVec3f(s,s,s));

			objMatrix.postMultTranslate(worldPos);
				
				
				
			
			tempObjects[0]->objectMatrices.push_back(objMatrix);
	}
	
	
	}

}
void TerrainFunctions::stopNewChunk(Chunk *chunk)
{
	for (int i =0; i<tempObjects.size();i++)
	{
		if (	tempObjects[i]->objectMatrices.size()>0)
		{
		tempObjects[i]->isMultiObject =true;
		tempObjects[i]->calculateNormalMatrix();
			chunk->detail1Objects.push_back(tempObjects[i]);
				chunk->detail2Objects.push_back(tempObjects[i]);
					chunk->detail3Objects.push_back(tempObjects[i]);
		
		}else
		{
			delete tempObjects[i];
		
		}
	}
	tempObjects.clear();

}