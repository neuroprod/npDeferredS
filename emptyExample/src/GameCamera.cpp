#include "GameCamera.h"

void GameCamera::setMouse(bool mouseIsDown,float moveX,float moveY)
{
	if (mouseIsDown)
	{
	mouseIsDown =true;
	
		mouseMatrix.makeIdentityMatrix();
	mouseMatrix.rotate( moveX,0,0,1);
		mouseMatrix.rotate( moveY/10,1,0,0);
	
	
	
	}else
	{
	mouseIsDown =false;
	
	
	
	}




}


void GameCamera::update(unsigned long timeStep)
{
	lookAtPos  =  mainCharacter->charPos;


	ofVec3f camTarget = mainCharacter->walkDir*100 ;
	camTarget.y-=5;


  
	ofMatrix4x4 targetRotationWalk;
	targetRotationWalk.makeLookAtViewMatrix(ofVec3f(0,0,0),camTarget,ofVec3f(0,1,0));
	targetRotationWalk.postMult(mouseMatrix);
	ofQuaternion targetRotationWalkQuat =  targetRotationWalk.getRotate();


	ofQuaternion currentQuaternationTemp;

	 currentQuaternationTemp.slerp(0.04f,currentQuaternation,targetRotationWalkQuat);
	//cout << currentQuaternation<< endl<< targetRotationWalkQuat<< endl<< endl<< endl<< endl<< endl;
	 currentQuaternationTemp.get(currentRotation);


	 currentQuaternation =  currentQuaternationTemp;
	

	camDir =  currentRotation *ofVec3f(0,0,10);
	camPos =camDir +lookAtPos;

	float terHeight = terrainFunctions->getHeightForPos(camPos.x,camPos.z);
	if (camPos.y<terHeight+1){
		camPos.y =terHeight+1 ;
	
	}
	//
	 worldMatrix.makeLookAtViewMatrix(camPos,  lookAtPos, ofVec3f (0,1,0));

	 //cout << lookAtPos<<endl <<	camPos << endl;
	




    ofQuaternion q = worldMatrix.getRotate();
	q.inverse();
    normalWorldMatrix.makeRotationMatrix(q);


	//// SHADOWS
	
	worldInv  =worldMatrix.getInverse();
	camDir.y =0;
	camDir.normalize(); 

	//// SHADOW 1

	lightPerspectivedMatrix1.makeOrthoMatrix(-60,60,-60,60,250,800);
	ofVec3f eye;
	eye =lightDir *-500+camPos-camDir*60 ;
	ofVec3f lookat;
	lookat = ofVec3f(0,0,0)+camPos-camDir*60 ;
	ofVec3f up;
	up =ofVec3f(0,1,0);
	
	



	lightWorldMatrix1.makeLookAtViewMatrix (eye,	lookat, up);
	lightMatrix1 =worldInv*   lightWorldMatrix1	*lightPerspectivedMatrix1;

		//// SHADOW 2

	lightPerspectivedMatrix2.makeOrthoMatrix(-300,300,-300,300,100,2200);

	eye =lightDir *-1000+camPos-camDir*300;
	
	lookat = ofVec3f(0,0,0)+camPos-camDir*300 ;
	
	up =ofVec3f(0,1,0);
	
	



	lightWorldMatrix2.makeLookAtViewMatrix (eye,	lookat, up);
	lightMatrix2 =worldInv*   lightWorldMatrix2	*lightPerspectivedMatrix2;

		//// SHADOW 3

	lightPerspectivedMatrix3.makeOrthoMatrix(-1000,1000,-1000,1000,100,2000);

	eye =lightDir *-1000+camPos-camDir*1000 ;
	
	lookat = ofVec3f(0,0,0)+camPos-camDir*1000 ;
	
	up =ofVec3f(0,1,0);
	
	



	lightWorldMatrix3.makeLookAtViewMatrix (eye,	lookat, up);
	lightMatrix3 =worldInv*   lightWorldMatrix3	*lightPerspectivedMatrix3;


}
void GameCamera::setup()
{
	 testtime=0;
	lookAtPos.set(0,0,0);
	perspectiveMatrix.makePerspectiveMatrix(60, (float)SCREEN_W/(float)SCREEN_H, 2,1900);
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}