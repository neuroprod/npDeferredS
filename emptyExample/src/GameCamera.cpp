#include "GameCamera.h"



void GameCamera::update()
{
	ofVec3f camOf = mainCharacter->walkDir *-70/4;
	camOf.y+=20/4;
	 lookAtPos  =  mainCharacter->charPos;
	 camPos  =  lookAtPos   +camOf;
  
	worldMatrix.makeLookAtViewMatrix(camPos,  lookAtPos, ofVec3f (0,1,0));
	
    ofQuaternion q = worldMatrix.getRotate();
	q.inverse();
    normalWorldMatrix.makeRotationMatrix(q);

		
	lightPerspectivedMatrix1.makeOrthoMatrix(-75,75,-75,75,300,2000);
	
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
	 perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 2,1000);
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}