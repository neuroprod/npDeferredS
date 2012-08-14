#include "MainCharacter.h"
#include "TerrainVertex.h"

void MainCharacter::setup()
{
	physicsHandler = PhysicsHandler::getInstance();
	//	aLoader.load(ofToDataPath("3DAssets/vrouwAnimeTest2.dae"));
	aLoader.load(ofToDataPath("3DAssets/girlStop.dae"));
	aLoader.addAnimation(ofToDataPath("3DAssets/girlWalk.dae"));

	charMesh  = *aLoader.boneMeshes[0];
	charMesh.setPos(0.0,0.001,0.0);
	charMesh.material.loadDiffuse("3DAssets/vrouwFinal.png");
	walkDirRot =0;
	rotSpeed =2;
	//walkDir.set(-0.085,0,0.996);
	//charPos.set(98.99,77.23,189.178);

	walkDir.set(-0.085,0,0.996);
	charPos.set(0.00,0.00,0.00);

	walkspeed =15;
	isMoving =false;
	lastDown =-1;
	rightIsDown =false;
	leftIsDown =false;
	walkSlerp=0;

	btScalar mass = 1;
    btVector3 fallInertia(0.0,0.0,0.0);
	capsuleShape = new btCapsuleShape(1,3.6); 
    capsuleMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0.2,1.8+2+100,0.2)));
    capsuleShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo capsuleRigidBodyCI(mass,capsuleMotionState,capsuleShape,fallInertia);
    capsuleRigidBody = new btRigidBody(capsuleRigidBodyCI);
	capsuleRigidBody->setSleepingThresholds(0.0, 0.0);
	capsuleRigidBody->setAngularFactor(0.0);

	physicsHandler->capsuleRigidBody  =capsuleRigidBody; 
	physicsHandler->dynamicsWorld->addRigidBody(capsuleRigidBody);
	
}
void MainCharacter::update(unsigned long timeStep)
{
	
	
	

	if (lastDown >-1)
	{
	
		if (lastDown==RIGHT_DOWN)
		{
		walkDirRot-= rotSpeed * (float)timeStep/1000000;
		
		}else
		{
		walkDirRot+= rotSpeed * (float)timeStep/1000000;
		
		}
	
	
		walkDir.set(sin(walkDirRot),0,cos (walkDirRot));
		if (!isMoving){walkSlerp =0.4;}

		walkDir.normalize();
	
	}
	
	float yp = capsuleRigidBody->getLinearVelocity().y();
	if (isMoving)
	{
		ofVec3f moveStep = walkDir*(walkspeed* (float)timeStep/1000000);

		//charPos  +=walkDir*(walkspeed* (float)timeStep/1000000);
		
		capsuleRigidBody->setLinearVelocity(btVector3( moveStep.x*35,yp, moveStep.z*35));
		//physicsHandler->capsuleRigidBody->applyForce(btVector3(moveStep.x*200,0,moveStep.z*200),btVector3(0,0,0)); 
		walkSlerp +=0.2f;
		if (walkSlerp>1)
		{
			walkSlerp =1;
		}
	}else
	{
		walkSlerp -=0.2f;
		if (walkSlerp<0)
		{
			walkSlerp =0;
		}

			capsuleRigidBody->setLinearVelocity(btVector3( 0,yp,0));
	}
	if (capsuleRigidBody->getLinearVelocity().y() <0.0005 && capsuleRigidBody->getLinearVelocity().y() >-0.0005)
	{
	//cout << "onGround?"<< endl;
	onGround =true;
	}else
	{
		//cout << "not "<< capsuleRigidBody->getLinearVelocity().y() << endl;
		onGround =false;
	}

/*	if (chunkHandler->frameCount>10)
	{
		TerrainVertex v = chunkHandler->getVertexforPos(charPos);
	
		charPos.y =v.position.y+2.5;

		charMesh.objectMatrix.makeLookAtViewMatrix(ofVec3f(0,0,0),walkDir,ofVec3f(0,-1,0));
		charMesh.objectMatrix.postMultTranslate(charPos);

		charMesh.calculateNormalMatrix();
	}else
	{
	
	
	}*/
	
	
}
void MainCharacter::resolve( unsigned long timeStep)
{
	if (chunkHandler->frameCount>10)
	{
		//TerrainVertex v = chunkHandler->getVertexforPos(charPos);
		

		charPos.x =capsuleMotionState->m_graphicsWorldTrans.getOrigin().getX();
		charPos.y =capsuleMotionState->m_graphicsWorldTrans.getOrigin().getY();
//		cout<<"currentCharPos: " << charPos.y<< endl;
		charPos.z =capsuleMotionState->m_graphicsWorldTrans.getOrigin().getZ();
		charMesh.objectMatrix.makeLookAtViewMatrix(ofVec3f(0,0,0),walkDir,ofVec3f(0,-1,0));
		charMesh.objectMatrix.postMultTranslate(charPos);

		charMesh.calculateNormalMatrix();
	}else
	{
	
	
	}
	charMesh.update((float)timeStep/300000 ,walkSlerp,0,1);

	

}

void  MainCharacter::setKey(int key)
{

	if (key== JUMP ) //&& onGround)
	{
		cout <<"jump"<<endl;
		capsuleRigidBody->applyImpulse(btVector3(0,10,0),btVector3(0,0,0)); 
	}
	else if (key== FORWARD_DOWN) isMoving =true;
	else if (key== FORWARD_UP) isMoving =false;
	
	else if (key== RIGHT_DOWN)
	{
		lastDown= RIGHT_DOWN;
	
		rightIsDown =true;
	} 
	else if (key== LEFT_DOWN)
	{
		lastDown= LEFT_DOWN;
	
		leftIsDown =true;
	}
	else if (key== RIGHT_UP)
	{
		rightIsDown =false;
	
		if (leftIsDown)
		{
			lastDown  =  LEFT_DOWN;
		}
		else
		{
			lastDown =-1;
		}
	} 
	else if (key== LEFT_UP)
	{
		leftIsDown =false;
		if (rightIsDown)
		{
			lastDown  = RIGHT_DOWN;
		}
		else
		{
			lastDown =-1;
		}
	} 

}