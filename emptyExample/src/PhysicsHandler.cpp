#include "PhysicsHandler.h"
PhysicsHandler *PhysicsHandler::mSingleton =NULL;
PhysicsHandler::PhysicsHandler(){};
PhysicsHandler::~PhysicsHandler(){};
PhysicsHandler * PhysicsHandler::getInstance()
{
	if (mSingleton==NULL)
	{
		mSingleton = new PhysicsHandler();
	}
	return mSingleton;
}

void PhysicsHandler::setup()
{
	    broadphase = new btDbvtBroadphase();
 
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
       solver = new btSequentialImpulseConstraintSolver;
 
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
 
        dynamicsWorld->setGravity(btVector3(0,-20,0));
	
 
        groundShape = new btStaticPlaneShape(btVector3(0,1,0),0);
 
       
 
 
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
		//groundRigidBodyCI.m_friction =0.1;
        btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
		
       dynamicsWorld->addRigidBody(groundRigidBody);
 
  fallShape = new btSphereShape(1);
        btDefaultMotionState* fallMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,2,4)));
        btScalar mass = 0;
        btVector3 fallInertia(0.0,0.0,0.0);
        fallShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
	

        fallRigidBody = new btRigidBody(fallRigidBodyCI);
        dynamicsWorld->addRigidBody(fallRigidBody);
	

	



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



	npMaterial mat3;
		mat3.hasColor =true;
		mat3.hasUV =false;
		mat3.r =0.5f;
		mat3.g =0.5f;
		mat3.b =0.5f;

	testBox.setup(mat3,20,2,4);
	ofQuaternion q;
	ofMatrix4x4 m;
	m.makeRotationMatrix(30,0,0,1);

	q.set(m);
	testBox.setPos(5,1,0,q);
	testBox.makePhysicsBox();
	    dynamicsWorld->addRigidBody(testBox.fRigidBody);
	}

	void PhysicsHandler::update(float timeStep)
	{
	
	 dynamicsWorld->stepSimulation(timeStep,100);
 
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
