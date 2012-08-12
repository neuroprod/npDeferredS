#pragma once;
#include "npIncludes.h"
#include "btBulletDynamicsCommon.h"
#include "npSphere.h"
#include "npBox.h"
class PhysicsHandler
{

private:
	static PhysicsHandler *mSingleton;
protected:
	PhysicsHandler();
public:
	virtual ~PhysicsHandler();
	static PhysicsHandler * getInstance();
	void setup();


	void update(float timeStep);



	 btBroadphaseInterface* broadphase ;
 
        btDefaultCollisionConfiguration* collisionConfiguration ;
        btCollisionDispatcher* dispatcher ;
 
        btSequentialImpulseConstraintSolver* solver ;
 
        btDiscreteDynamicsWorld* dynamicsWorld ;
 
      
 
 
        btCollisionShape* groundShape ;
 
        btCollisionShape* fallShape;
		 btRigidBody* fallRigidBody ;
		

		btRigidBody* capsuleRigidBody ;

		npSphere testSphere;
		npSphere testSphereChar1;
		npSphere testSphereChar2;


		npBox testBox;
};