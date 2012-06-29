#include "GameCamera.h"



void GameCamera::update()
{
	ofVec3f charPos  =  mainCharacter->charPos;
	ofVec3f campos  =  charPos  + mainCharacter->walkDir *-20;
    campos.y+=10;
	worldMatrix.makeLookAtViewMatrix(campos, charPos, ofVec3f (0,1,0));
	
    ofQuaternion q = worldMatrix.getRotate();
	q.inverse();
    normalWorldMatrix.makeRotationMatrix(q);
	

}
void GameCamera::setup()
{
	 perspectiveMatrix.makePerspectiveMatrix(60, (float)ofGetScreenWidth()/(float)ofGetScreenHeight(), 1, 2000);
 
    perspectiveInvMatrix.makeInvertOf(perspectiveMatrix);


}