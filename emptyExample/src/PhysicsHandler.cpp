#include "PhysicsHandler.h"

void PhysicsHandler::setup()
{
	    broadphase = new btDbvtBroadphase();
 
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
       solver = new btSequentialImpulseConstraintSolver;
 
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
 
        dynamicsWorld->setGravity(btVector3(0,-10,0));
 
 
        groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
 
       
 
 
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
		groundRigidBodyCI.m_friction =0.1;
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		
        dynamicsWorld->addRigidBody(groundRigidBody);
 
  fallShape = new btSphereShape(1);
        btDefaultMotionState* fallMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,10,0)));
        btScalar mass = 1;
        btVector3 fallInertia(0.1,0.1,0.1);
        fallShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
		fallRigidBodyCI.m_friction =0.1;
		fallRigidBodyCI.m_linearDamping =0.8;

        fallRigidBody = new btRigidBody(fallRigidBodyCI);
        dynamicsWorld->addRigidBody(fallRigidBody);
	

		capsuleShape = new btCapsuleShape(1,3.6);
       // btDefaultMotionState* fallMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,1,0)));
     btDefaultMotionState* capsuleMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0.2,1.8+2,0.2)));
       // btVector3 fallInertia(0,0,0);
       capsuleShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI(mass,capsuleMotionState,capsuleShape,fallInertia);
        capsuleRigidBody = new btRigidBody(capsuleRigidBodyCI);
		  capsuleRigidBody->setSleepingThresholds(0.0, 0.0);
capsuleRigidBody->setAngularFactor(0.0);

        dynamicsWorld->addRigidBody(capsuleRigidBody);



 /*
 
        for (int i=0 ; i<300 ; i++) {
                dynamicsWorld->stepSimulation(1/60.f,10);
 
                btTransform trans;
                fallRigidBody->getMotionState()->getWorldTransform(trans);
 
                std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
        }*/
 
       /* dynamicsWorld->removeRigidBody(fallRigidBody);
        delete fallRigidBody->getMotionState();
        delete fallRigidBody;
 
        dynamicsWorld->removeRigidBody(groundRigidBody);
        delete groundRigidBody->getMotionState();
        delete groundRigidBody;
 
 
        delete fallShape;
 
        delete groundShape;
 
 
        delete dynamicsWorld;
        delete solver;
        delete collisionConfiguration;
        delete dispatcher;
        delete broadphase;
	*/
		npMaterial mat;
		mat.hasColor =true;
		mat.hasUV =false;
		mat.r =1.0f;
		mat.g =0.0f;
		mat.b =0.0f;
	
	testSphere.setup( mat,1  ,10 ,10);

	npMaterial mat2;
		mat2.hasColor =true;
		mat2.hasUV =false;
		mat2.r =1.0f;
		mat2.g =0.0f;
		mat2.b =1.0f;
	testSphereChar2.setup( mat2,1  ,10 ,10);
	testSphereChar1.setup( mat2,1  ,10 ,10);
	}

	void PhysicsHandler::update(float timeStep)
	{
	
	 dynamicsWorld->stepSimulation(timeStep,10);
 
                btTransform trans;
                fallRigidBody->getMotionState()->getWorldTransform(trans);
 float posY = trans.getOrigin().getY();
  float posX = trans.getOrigin().getX();
  float posZ = trans.getOrigin().getZ();
 testSphere.setPos(posX,posY, posZ);
             //   std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
  capsuleRigidBody->getMotionState()->getWorldTransform(trans);
	
	 posY = trans.getOrigin().getY();
   posX = trans.getOrigin().getX();
  posZ = trans.getOrigin().getZ();
  	testSphereChar1.setPos(posX,posY-1.8, posZ);
		testSphereChar2.setPos(posX,posY+1.8, posZ);

		//capsuleRigidBody->setLinearVelocity(btVector3(0.0,0,0));
	}
