//
//  npSphere.h
//  emptyExample
//
//  Created by Kris Temmerman on 24/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_npBox_h
#define emptyExample_npBox_h
#include "npMesh.h"
#include "btBulletDynamicsCommon.h"

class npBox:public npMesh
{
private:
	int vertcount ;
    int indcount ;
	int indPos;
	float r;
    float g;
    float b;
	void addPlane(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3,const ofVec3f &p,const ofVec3f &normal);
	 bool hasColor ;
     bool hasUV;
public : 
    
   npBox(){};
    ~npBox(){};
    
    void setup(npMaterial mat, float w,float h,float d);
	float width;
	float height ;
	float depth;



	void makePhysicsBox();
	btCollisionShape* fCollisionShape;
	btRigidBody* fRigidBody ;
};


#endif
