
#include "npBox.h"


void npBox::setup(npMaterial mat, float w , float h,float d )
{

	width =w;
	height =h;
	depth =d;
 
    material = mat;
    hasColor = false;
     hasUV = false;
  
    stride  =6;
    if (material.hasColor)
    {
    
        hasColor  =true;
        r =material.r;
        g =material.g;
        b =material.b;
        stride +=3;
    
    }if (material.hasUV)    {
    
        hasUV  =true;
        stride  +=2;
    }
        
    
    
    
    numVertices  =24;
    vertices  = new float[numVertices*stride ]; 
    numIndices =36;
    indices  =new unsigned int [ numIndices];
   
    vertcount =0;
    indcount =0;
	indPos =0;

	float w2 =w/2.0f;
	float h2 =h/2.0f;
	float d2 =d/2.0f;

	//top
	addPlane(ofVec3f(-w2,h2,-d2),ofVec3f(w2,h2,-d2),ofVec3f(w2,h2,d2),ofVec3f(-w2,h2,d2),ofVec3f(0,1,0));
    

	//bottem
	addPlane(ofVec3f(-w2,-h2,-d2),ofVec3f(w2,-h2,-d2),ofVec3f(w2,-h2,d2),ofVec3f(-w2,-h2,d2),ofVec3f(0,-1,0));

 
		//front
	addPlane(ofVec3f(-w2,h2,d2),ofVec3f(w2,h2,d2),ofVec3f(w2,-h2,d2),ofVec3f(-w2,-h2,d2),ofVec3f(0,0,1));

 
		//back
	addPlane(ofVec3f(-w2,h2,-d2),ofVec3f(w2,h2,-d2),ofVec3f(w2,-h2,-d2),ofVec3f(-w2,-h2,-d2),ofVec3f(0,0,-1));

 //right
	addPlane(ofVec3f(w2,-h2,-d2),ofVec3f(w2,-h2,d2),ofVec3f(w2,h2,d2),ofVec3f(w2,h2,-d2),ofVec3f(1,0,0));
 //left
	addPlane(ofVec3f(-w2,-h2,-d2),ofVec3f(-w2,-h2,d2),ofVec3f(-w2,h2,d2),ofVec3f(-w2,h2,-d2),ofVec3f(-1,0,0));
  
	   
    
    createBuffers();
	delete [ ] indices;
	indices =NULL;

	delete []vertices;
	vertices =NULL;




}

void npBox::addPlane(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3,const ofVec3f &p4,const ofVec3f &normal)
{
		indices[indPos++ ] = indcount;
        indices[indPos++]= indcount+1;
        indices[indPos++] = indcount+3;


		indices[indPos++ ] = indcount+1;
        indices[indPos++]= indcount+2;
        indices[indPos++] = indcount+3;
		indcount+=4;
	    //p1
            vertices[vertcount++] = p1.x ;
            vertices[vertcount++] = p1.y ;
            vertices[vertcount++] = p1.z;
            
            vertices[vertcount++] = normal.x;
            vertices[vertcount++] =  normal.y;
            vertices[vertcount++] =  normal.z;
            if (hasColor)
            {
                vertices[vertcount++] =  r;
                vertices[vertcount++] =  g;
                vertices[vertcount++] =  b;    
            }
            if (hasUV)
            {
                cout << "implement UV Sphere ";
            
                vertices[vertcount++] =  0;
                vertices[vertcount++] =  0;
            }
            
  //p2
            vertices[vertcount++] = p2.x ;
            vertices[vertcount++] = p2.y ;
            vertices[vertcount++] = p2.z;
            
            vertices[vertcount++] = normal.x;
            vertices[vertcount++] =  normal.y;
            vertices[vertcount++] =  normal.z;
            if (hasColor)
            {
                vertices[vertcount++] =  r;
                vertices[vertcount++] =  g;
                vertices[vertcount++] =  b;    
            }
            if (hasUV)
            {
                cout << "implement UV Sphere ";
            
                vertices[vertcount++] =  0;
                vertices[vertcount++] =  0;
            }

			  //p3
            vertices[vertcount++] = p3.x ;
            vertices[vertcount++] = p3.y ;
            vertices[vertcount++] = p3.z;
            
            vertices[vertcount++] = normal.x;
            vertices[vertcount++] =  normal.y;
            vertices[vertcount++] =  normal.z;
            if (hasColor)
            {
                vertices[vertcount++] =  r;
                vertices[vertcount++] =  g;
                vertices[vertcount++] =  b;    
            }
            if (hasUV)
            {
                cout << "implement UV Sphere ";
            
                vertices[vertcount++] =  0;
                vertices[vertcount++] =  0;
            }

			  //p4
            vertices[vertcount++] = p4.x ;
            vertices[vertcount++] = p4.y ;
            vertices[vertcount++] = p4.z;
            
            vertices[vertcount++] = normal.x;
            vertices[vertcount++] =  normal.y;
            vertices[vertcount++] =  normal.z;
            if (hasColor)
            {
                vertices[vertcount++] =  r;
                vertices[vertcount++] =  g;
                vertices[vertcount++] =  b;    
            }
            if (hasUV)
            {
                cout << "implement UV Sphere ";
            
                vertices[vertcount++] =  0;
                vertices[vertcount++] =  0;
            }


}

void npBox::makePhysicsBox()
{

	

	  fCollisionShape = new btBoxShape(btVector3(width/2,height/2,depth/2));
        btDefaultMotionState* fMotionState =new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(x,y,z)));
        btScalar mass = 0;
        btVector3 fallInertia(0.0,0.0,0.1);
        fCollisionShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fMotionState,fCollisionShape,fallInertia);
		 fRigidBody = new btRigidBody(fallRigidBodyCI);
}