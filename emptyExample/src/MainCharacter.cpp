#include "MainCharacter.h"


void MainCharacter::setup()
{
	
	//	aLoader.load(ofToDataPath("3DAssets/vrouwAnimeTest2.dae"));
aLoader.load(ofToDataPath("3DAssets/girlWalk.dae"));
	charMesh  = *aLoader.boneMeshes[0];
	charMesh.setPos(0,0,0);
	charMesh.material.loadDiffuse("3DAssets/vrouwFinal.png");
	walkDirRot =0;
	rotSpeed =2;
	walkDir.set(0,0,1);
	charPos.set(0,0,0);
	walkspeed =15;
	 isMoving =false;
	 lastDown =-1;
	 rightIsDown =false;
	 leftIsDown =false;
}
void MainCharacter::update(unsigned long timeStep)
{
	
	
	
	charMesh.update();

	if (lastDown >-1)
	{
	
		if (lastDown==RIGHT_DOWN)
		{
		walkDirRot-= rotSpeed * (float)timeStep/1000000;
		
		}else
		{
		walkDirRot+= rotSpeed * (float)timeStep/1000000;
		
		}
	
	
		walkDir.set(sin(walkDirRot),0,cos (walkDirRot));


		walkDir.normalize();
	
	}


	if (isMoving){
	charPos  +=walkDir*(walkspeed* (float)timeStep/1000000);

	
	
	}
	

	
	charPos.y =  terrainFunctions->getHeightForPos(charPos.x, charPos.z) +2.3;
	charMesh.objectMatrix.makeLookAtViewMatrix(ofVec3f(0,0,0),walkDir,ofVec3f(0,-1,0));
	charMesh.objectMatrix.postMultTranslate(charPos);
	//	charMesh.objectMatrix.preMultScale(ofVec3f(5,5,5));
	charMesh.calculateNormalMatrix();
}


void  MainCharacter::setKey(int key)
{

if (key== FORWARD_DOWN) isMoving =true;
else if (key== FORWARD_UP) isMoving =false;
	
else if (key== RIGHT_DOWN)
{
	lastDown= RIGHT_DOWN;
	
	rightIsDown =true;
} 
else if (key== LEFT_DOWN)
{
	lastDown= LEFT_DOWN;
	
	leftIsDown =true;
} else if (key== RIGHT_UP)
{
	rightIsDown =false;
	if (leftIsDown)
	{
		lastDown  =  LEFT_DOWN;
	}else
	{
		lastDown =-1;
	}
} 
else if (key== LEFT_UP)
{
	leftIsDown =false;
	if (rightIsDown)
	{
		lastDown  = RIGHT_DOWN;
	}else
	{
		lastDown =-1;
	}
} 



}