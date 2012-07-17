
#include "SkyBoxStars.h"	

void SkyBoxStars::setup()
{
	numStars  =  500;
	ofVec4f pv1 ;
	ofVec4f pv2 ;
	ofVec4f pv3 ;
	ofVec4f pv4 ;
	ofVec4f v1 ;
	ofVec4f v2 ;
	ofVec4f v3 ;
	ofVec4f v4 ;
	ofVec3f n ;
	ofMatrix4x4 objectMatrix;
	vertices = new float[	numStars*20];
	int pos =0;
	for(int i=0; i<	numStars;i++)
	{
		float size =0.01f;
	
		pv1.set(-size,-size,-0.0,1);
		pv2.set(-size,size,0,1);
		pv3.set(size,size,0.0,1);
		pv4.set(size,-size,0,1);
		n.set((float)rand()/RAND_MAX -0.5,(float)rand()/RAND_MAX -0.5,(float)rand()/RAND_MAX -0.5);
		n.normalize();

	 
		n.scale((float)rand()/RAND_MAX*0.2+0.9);
		objectMatrix.makeLookAtMatrix(n,ofVec3f(0,0,0),ofVec3f(0,1,0));
	
		int sOf = rand()%5;
		float off = 0.2f *sOf ;

		v1 =pv1 *objectMatrix ;
		v2 =pv2* objectMatrix;
		v3 =pv3* objectMatrix ;
		v4 =pv4 *objectMatrix ;
		
		vertices[pos++]  = v1.x; 
		vertices[pos++]  = v1.y; 
		vertices[pos++]  = v1.z; 
		vertices[pos++]  = 0+off; 
		vertices[pos++]  = 0; 


		vertices[pos++]  = v2.x; 
		vertices[pos++]  = v2.y; 
		vertices[pos++]  = v2.z; 
		vertices[pos++]  = 0+off; 
		vertices[pos++]  = 1; 


		vertices[pos++]  = v3.x; 
		vertices[pos++]  = v3.y; 
		vertices[pos++]  = v3.z; 
		vertices[pos++]  = 0.2+off; 
		vertices[pos++]  = 1; 


		vertices[pos++]  = v4.x; 
		vertices[pos++]  = v4.y; 
		vertices[pos++]  = v4.z; 
		vertices[pos++]  = 0.2 +off; 
		vertices[pos++]  = 0; 
	}
	

}
