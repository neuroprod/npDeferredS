
#include "TerrainFunctions.h"

void TerrainFunctions::setup()
{
heightPerlin = new Perlin(5,1,1,122335);
		
}

float TerrainFunctions::getHeightForPos(float  x, float z)
{
	
	float heightMac  =heightPerlin->Get(x/1500.1, z/1500.1)+0.5+0.3 ;
	heightMac =  heightMac*heightMac*heightMac*100;

	return heightMac  ;

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
