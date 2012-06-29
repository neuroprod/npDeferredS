#include "GameCamera.h"



void GameCamera::update()
{
	 lookAtPos  =  mainCharacter->charPos;
	 camPos  =  lookAtPos   + mainCharacter->walkDir *-70/3;
    camPos.y+=20/3;
	worldMatrix.makeLookAtViewMatrix(camPos,  lookAtPos, ofVec3f (0,1,0));
	
    ofQuaternion q = worldMatrix.getRotate();
	q.inverse();
    normalWorldMatrix.makeRotationMatrix(q);
	

}
void GameCamera::setup()
{
	 perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 1, 2000);
 
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}