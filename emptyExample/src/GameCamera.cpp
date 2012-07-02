#include "GameCamera.h"



void GameCamera::update()
{
	 lookAtPos  =  mainCharacter->charPos;
	 camPos  =  lookAtPos   + mainCharacter->walkDir *-70/3;
    camPos.y+=20/3;
	worldMatrix.makeLookAtViewMatrix(camPos,  lookAtPos, ofVec3f (0,1,0));
	//worldMatrix.makeIdentityMatrix();
    ofQuaternion q = worldMatrix.getRotate();
	q.inverse();
    normalWorldMatrix.makeRotationMatrix(q);
	
	/*
	ofMatrix4x4 lightPerspectivedMatrix1;
	ofMatrix4x4 lightWorldMatrix1;*/
	//	ofMatrix4x4 lightMatrix1;

		
	lightPerspectivedMatrix1.makeOrthoMatrix(-100,100,-100,100,50,300);
	
	lightWorldMatrix1.makeLookAtViewMatrix ( (lightDir *-100) + lookAtPos,ofVec3f(0,0,0)  +lookAtPos, ofVec3f(0,1,0));

	


	lightMatrix1 = lightWorldMatrix1* lightPerspectivedMatrix1;
	
	// perspectiveMatrix= lightMatrix1;
  //  perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);

}
void GameCamera::setup()
{
	 perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 1, 2000);
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}