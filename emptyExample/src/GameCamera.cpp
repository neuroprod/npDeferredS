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


void GameCamera::update()
{
	lookAtPos  =  mainCharacter->charPos;


	ofVec3f camTarget = mainCharacter->walkDir*20 ;
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
	

	camDir =  currentRotation *ofVec3f(0,0,15);
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

		
	lightPerspectivedMatrix1.makeOrthoMatrix(-75,75,-75,75,200,1500);
	
	ofVec3f eye;
	eye =lightDir *-500+camPos+mainCharacter->walkDir *75 ;
	ofVec3f lookat;
	lookat = ofVec3f(0,0,0)+camPos+mainCharacter->walkDir *75;
	ofVec3f up;
	up =ofVec3f(0,1,0);
	

	  ofQuaternion qw = worldMatrix.getRotate();
	  //qw.inverse();
	 ofMatrix4x4 worldRot;
	 worldRot.makeRotationMatrix(qw);
	  worldInv  =worldMatrix.getInverse();

	  ofMatrix4x4 worldTrans;
	  worldTrans.makeTranslationMatrix(worldMatrix.getTranslation());


	lightWorldMatrix1.makeLookAtViewMatrix (eye,	lookat, up);
	lightMatrix1 =worldInv*  lightWorldMatrix1	* lightPerspectivedMatrix1;

	

	lightMatrix2 = worldInv*  lightWorldMatrix1* 	 lightPerspectivedMatrix1;

}
void GameCamera::setup()
{
	lookAtPos.set(0,0,0);
	 perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 2,1900);
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}