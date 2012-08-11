#pragma once;
#include "npIncludes.h"
#include "btBulletDynamicsCommon.h"
#include "npSphere.h"
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
		
		 btCollisionShape* capsuleShape;
		btRigidBody* capsuleRigidBody ;

		npSphere testSphere;
		npSphere testSphereChar1;
		npSphere testSphereChar2;
};