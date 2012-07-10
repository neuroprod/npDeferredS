
#include "TerrainFunctions.h"

void TerrainFunctions::setup()
{

	objectLib.setup();
	srand(3);
	heightPerlin1 = new Perlin(5,1,1,122335);
	
	heightPerlin2= new Perlin(3,1,1,1223);
	typePerlin= new Perlin(8,1,1,1243);	


	vegatationPerlin =new Perlin(5,1,1,125523);
}

float TerrainFunctions::getHeightForPos(float  x, float z)
{
	
	float heightMac1  =heightPerlin1->Get(x/1500.1, z/1500.1)+0.5+0.3 ;
	heightMac1 =  heightMac1*heightMac1*heightMac1*100;
	if (heightMac1 >70)
	{
		float tp =typePerlin->Get(x/1500.1, z/1500.1)*2;
		if (tp >0)
		{
		
			float heightMac2  =heightPerlin2->Get(x/250.1, z/250.1)+0.5+0.1 ;
			heightMac2 =  heightMac2*heightMac2*heightMac2*50;
			if (tp >0.5)
			{
				heightMac1=  heightMac2+50;
			}else
			{
				tp*=2;
				heightMac1 = heightMac1 *(1-tp) +( heightMac2+50)*(tp);
			
			}

		}
	}
	return heightMac1 ;

}
void  TerrainFunctions::getNormalforVertex( TerrainVertex &vertex)
{

		ofVec3f pos1 = vertex.positionT;
	pos1.x-=0.5f;
		pos1.z-=0.5f;
	pos1.y=getHeightForPos(pos1.x,pos1.z);

	ofVec3f pos2 = vertex.positionT;
	pos2.x+=0.7f;
	pos2.y=getHeightForPos(pos2.x,pos2.z);
	ofVec3f pos3= vertex.positionT;
	pos3.z+=0.7f;
	pos3.y=getHeightForPos(pos3.x,pos3.z);


	vertex.normalT = getNormal( pos1, pos2,pos3 );




}
ofVec3f TerrainFunctions::getNormalforPos(float x, float z)
{

	ofVec3f normal;
	
	normal= getNormal( ofVec3f(x,getHeightForPos(x,z), z) , ofVec3f(x+1.5,getHeightForPos(x+1.5,z), z)   , ofVec3f(x,getHeightForPos(x,z+1.5),(z+1.5)) );
	

	return normal;


}
ofVec3f  TerrainFunctions::getNormal(const ofVec3f &p1,const ofVec3f &p2,const ofVec3f &p3)
{
	ofVec3f d1  = p1-p2;
	ofVec3f d2 = p1-p3;
	ofVec3f normal= d2.getCrossed( d1).normalize();

	
	return normal;
}





//
//
//   OBJECTS
//
//





void TerrainFunctions::startNewObjectsForChunk(Chunk *chunk)
{
	//objectLib.getMultiMeshes(chunk);

	chunk->detail1Objects.push_back(npMultiMesh(objectLib.objects[0]));
	chunk->detail1Objects.push_back(npMultiMesh(objectLib.objects[1]));

		chunk->detail2Objects.push_back(npMultiMesh(objectLib.objects[0]));
	chunk->detail2Objects.push_back(npMultiMesh(objectLib.objects[1]));

		chunk->detail3Objects.push_back(npMultiMesh(objectLib.objects[0]));
	chunk->detail3Objects.push_back(npMultiMesh(objectLib.objects[1]));

	for (int i=0;i<objectLib.pointLights.size();i++)
	{
		chunk->pLights.push_back(npMultiPointLight(objectLib.pointLights[i]));
	
	}



}

void TerrainFunctions::getObjectsForVertex( TerrainVertex *vertex, Chunk *chunk)
{
	int r  = rand();
	

	
	
	


	float veg  = (vegatationPerlin->Get(vertex->position.x/1500.1, vertex->position.z/1500.1)+1)*0.5;
	float veg2  =( vegatationPerlin->Get(vertex->position.x/150.1, vertex->position.z/150.1)+1 )*0.2;

	if(vertex->hil<0.8)
			{
			vertex->color.set(0.37f,0.27f,0.17f);
	}else
	{
			vertex->color.set(0.51f,0.66f,0.15f);
			
	}


	if (veg2<0.2 && vertex->hil>0.7)
	{
			float factor =  (veg2*5) ;
			vertex->color.x *= factor ;
			vertex->color.y *=factor;
			vertex->color.z *=factor ;
			factor =1-factor;

			vertex->color.x += factor*0.7f;
			vertex->color.y +=factor *0.8f;
			vertex->color.z +=factor*0 ;

	}

		float vegFactor =1- (veg-0.48f)*8.0f;
		if ( vegFactor <0.5f)  vegFactor =0.5f;
		if ( vegFactor >0.8)  vegFactor =0.8f;
		vegFactor+=veg2 ;
		vertex->color.x*=vegFactor   ;
		vertex->color.y *=vegFactor ; //*(1.0f-vegFactor );
		vertex->color.z *=vegFactor ; //*(1.0f-vegFactor );	




	if(vertex->position.y<100   ){
	
		
		

		if ( veg>0.5)
		{

			
		
			
			if (r%270==1){



				ofMatrix4x4 objMatrix;
				objMatrix.makeRotationMatrix(90,ofVec3f(1,0,0) );
				objMatrix.postMultRotate(  (float)rand()/RAND_MAX *360.0f,0,1,0);
				float s = (float)rand()/RAND_MAX *0.4 +0.8;
				objMatrix.postMultScale(ofVec3f(s,s,s));

				objMatrix.postMultTranslate(vertex->position);
				
				vertex->color.x =0;
				vertex->color.y =0;
				vertex->color.z =0.0;		
			
				chunk->detail1Objects[0].objectMatrices.push_back(objMatrix);
					chunk->detail2Objects[0].objectMatrices.push_back(objMatrix);
						chunk->detail3Objects[0].objectMatrices.push_back(objMatrix);
				return;
			}
	
	
		}
		else
		{

			if (r%40==1  && 	vertex->hil>0.9 && vertex->position.y<40){
				ofMatrix4x4 objMatrix;
				objMatrix.makeRotationMatrix(-90,ofVec3f(1,0,0) );
				objMatrix.postMultRotate(  (float)rand()/RAND_MAX *360.0f,0,1,0);
				//float s = (float)rand()/RAND_MAX *0.4 +0.8;
				//objMatrix.postMultScale(ofVec3f(s,s,s));

				objMatrix.postMultTranslate(vertex->position);
				
					
				chunk->detail1Objects[1].objectMatrices.push_back(objMatrix);
				chunk->detail2Objects[1].objectMatrices.push_back(objMatrix);
						
				return;
			}
		}
	}
	if ( veg>0.5)
	{
		 r  = rand();
		 if (r%70==1)
		 {
		
			int pIndex =  rand()%chunk->pLights.size();
			ofMatrix4x4 objMatrix;
			ofVec3f center =vertex->position +ofVec4f(0,5,0);

			objMatrix.makeTranslationMatrix( center);
			chunk->pLights[pIndex ].objectMatrices.push_back(objMatrix);

			chunk->pLights[pIndex ].objectCenters.push_back(center);
	
      
		 }
	
	}

}
void TerrainFunctions::stopNewObjectsForChunk(Chunk *chunk)
{
	for (int i=0;i<chunk->detail1Objects.size();i++)
	{
chunk->detail1Objects[i].calculateNormalMatrices();

	}
		for (int i=0;i<chunk->detail2Objects.size();i++)
	{
chunk->detail2Objects[i].calculateNormalMatrices();

	}
	for (int i=0;i<chunk->detail3Objects.size();i++)
	{
chunk->detail3Objects[i].calculateNormalMatrices();

	}

	for (int i=0;i<chunk->pLights.size();i++)
	{
		if (chunk->pLights[i].objectMatrices.size()==0)
		{
			chunk->pLights.erase(chunk->pLights.begin()+i);
			i--;
		}

	}

	/*	chunk->detail2Objects.push_back(npMultiMesh(objectLib.objects[0]));
	chunk->detail2Objects.push_back(npMultiMesh(objectLib.objects[1]));

		chunk->detail3Objects.push_back(npMultiMesh(objectLib.objects[0]));
	chunk->detail3Objects.push_back(npMultiMesh(objectLib.objects[1]));
	// clean?

	/*for (int i =0; i<tempObjects.size();i++)
	{
		if (	tempObjects[i]->objectMatrices.size()>0)
		{
			tempObjects[i]->isMultiObject =true;
			tempObjects[i]->calculateNormalMatrix();
			chunk->detail1Objects.push_back( tempObjects[i]);
			chunk->detail2Objects.push_back(tempObjects[i]);
			if (i==0)
			{
				chunk->detail3Objects.push_back(tempObjects[i]);
			}
		
		}else
		{
			delete tempObjects[i];
			tempObjects[i] =NULL;
		}
	}
	for (int i =0; i<pLights.size();i++)
	{
			chunk->pLights.push_back(pLights[i]);
	}
	tempObjects.clear();
	pLights.clear();*/
}