#include "npBoneMesh.h"


npBoneMesh::npBoneMesh(void)
{
}


npBoneMesh::~npBoneMesh(void)
{
}
void npBoneMesh::prepBones()
{
	boneMatrices =new float[22*16];
	normalMatrices =new float[22*16];
	/*for (int i=0;i< bones.size();i++)
	{
		//bones[i]->boneMatrix.makeInvertOf(bones[i]->nodeMatrix);
		if (i<5){	cout <<bones[i]->name<<endl;
		cout <<bones[i]->nodeMatrix<< endl<< endl;
		cout <<bones[i]->boneMatrix<< endl<<endl<< endl;}
	}*/

	time =0;
}
void npBoneMesh::update(){

	//rootBone
	time+=0.08f;
	if (time> bones[1]->animations[0].totalTime)time =0;

	for (int i=0;i< bones.size();i++)
	{

		bones[i]->animeMatrix.makeIdentityMatrix();
		if (bones[i]->animations.size()>0)
		{
			

			ofQuaternion quat;
			 quat.set(1,0,0,0);
			if (bones[i]->animations[0].rotations.size() ==1)
			{
				quat = bones[i]->animations[0].rotations[0].quat;
			}
			else
			{
				for (int j=1; j<bones[i]->animations[0].rotations.size() ;j++)
				{
					if (bones[i]->animations[0].rotations[j].time >time)
					{
						
						
						float time1  = bones[i]->animations[0].rotations[j-1].time ;
						float timeTotal  = bones[i]->animations[0].rotations[j].time -time1 ;
						float timeCurrent = time-time1;
						float timeslerp = timeCurrent /timeTotal;
						
						quat.slerp(timeslerp , bones[i]->animations[0].rotations[j-1].quat, bones[i]->animations[0].rotations[j].quat);
					
						break;
					}
				
				}
			
			}

			bones[i]->animeMatrix.makeRotationMatrix(quat);

			
			
			
			
			
			
			if (bones[i]->animations[0].translations.size()>0)
			{
				bones[i]->animeMatrix.postMultTranslate(	bones[i]->animations[0].translations[0].pos);
			
			}
		

		}
	
	
	}

	for (int i=0;i< bones.size();i++)
	{
	
		bones[i]->finalMatrix=bones[i]->boneMatrix;
		const npBone* tempNode = bones[i];
		while( tempNode)
		{
				// check your matrix multiplication order here!!!
				bones[i]->finalMatrix =bones[i]->finalMatrix * tempNode->animeMatrix;
				
				tempNode = tempNode->parent;
		}
	//bones[i]->finalMatrix =bones[i]->animeMatrix;
	};

	setMatrixes();
}
void npBoneMesh::setMatrixes()
{
	
	int count =0;
	for (int i=1;i< 23;i++)
	{
		
		float*_mat = bones[i]->finalMatrix.getPtr();
		
		ofMatrix4x4 rot;
		bones[i]->finalMatrix.getRotate().get(rot);
		float*_matN =rot.getPtr();
	
		for (int j=0;j<16;j++)
		{
		
			boneMatrices[count] = _mat[j];
			normalMatrices[count++]= _matN[j];
		}
	
	
	}



}

	