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
void npBoneMesh::update(float timeStep,float _animeSlerp,int ani1,int ani2){

	int anime1 =ani1;
	int anime2 =ani2;
	float animeSlerp =_animeSlerp;
	//rootBone
	time+=timeStep;
	if (time> bones[1]->animations[1].totalTime)time =0;

	for (int i=0;i< bones.size();i++)
	{

		bones[i]->animeMatrix.makeIdentityMatrix();
		if (bones[i]->animations.size()>0)
		{
			
			ofQuaternion quat;
			ofQuaternion quat1;
			 quat1.set(1,0,0,0);
			if (bones[i]->animations[anime1].rotations.size() ==1)
			{
				quat1 = bones[i]->animations[anime1].rotations[0].quat;
			}
			else
			{
				for (int j=1; j<bones[i]->animations[anime1].rotations.size() ;j++)
				{
					if (bones[i]->animations[anime1].rotations[j].time >time)
					{
						
						
						float time1  = bones[i]->animations[anime1].rotations[j-1].time ;
						float timeTotal  = bones[i]->animations[anime1].rotations[j].time -time1 ;
						float timeCurrent = time-time1;
						float timeslerp = timeCurrent /timeTotal;
						
						quat1.slerp(timeslerp , bones[i]->animations[anime1].rotations[j-1].quat, bones[i]->animations[anime1].rotations[j].quat);
					
						break;
					}
				
				}
			
			}

			ofQuaternion quat2;
			 quat2.set(1,0,0,0);
			if (bones[i]->animations[anime2].rotations.size() ==1)
			{
				quat2 = bones[i]->animations[anime2].rotations[0].quat;
				
			}
			else
			{
				for (int j=1; j<bones[i]->animations[anime2].rotations.size() ;j++)
				{
					if (bones[i]->animations[anime2].rotations[j].time >time)
					{
						
						
						float time1  = bones[i]->animations[anime2].rotations[j-1].time ;
						float timeTotal  = bones[i]->animations[anime2].rotations[j].time -time1 ;
						float timeCurrent = time-time1;
						float timeslerp = timeCurrent /timeTotal;
						
						quat2.slerp(timeslerp , bones[i]->animations[anime2].rotations[j-1].quat, bones[i]->animations[anime2].rotations[j].quat);
					
						break;
					}
				
				}
			
			}


			quat.slerp(animeSlerp , quat1, quat2);
			if (i==4) quat.makeRotate(0,ofVec3f(0,1,0));
			bones[i]->animeMatrix.makeRotationMatrix(quat);

			
			
			
			ofVec3f translation(0,0,0);
			ofVec3f translation1(0,0,0);
			ofVec3f translation2(0,0,0);
			if (bones[i]->animations[0].translations.size()>0)
			{
				if (bones[i]->animations[anime1].translations.size() ==1)
				{
				translation1 = bones[i]->animations[anime1].translations[0].pos;
				}else
				{
					for (int j=1; j<bones[i]->animations[anime1].translations.size() ;j++)
					{
						if (bones[i]->animations[anime1].translations[j].time >time)
						{
						
						
							float time1  = bones[i]->animations[anime1].translations[j-1].time ;
							float timeTotal  = bones[i]->animations[anime1].translations[j].time -time1 ;
							float timeCurrent = time-time1;
							float timeslerp = timeCurrent /timeTotal;
						
					
						translation1 = bones[i]->animations[anime1].translations[j-1].pos *(1.0f -timeslerp) +bones[i]->animations[anime1].translations[j].pos *(timeslerp);

							break;
						}
				
					}
				}


				if (bones[i]->animations[anime2].translations.size() ==1)
				{
				translation2= bones[i]->animations[anime2].translations[0].pos;
				}else
				{
					for (int j=1; j<bones[i]->animations[anime2].translations.size() ;j++)
					{
						if (bones[i]->animations[anime2].translations[j].time >time)
						{
						
						
							float time1  = bones[i]->animations[anime2].translations[j-1].time ;
							float timeTotal  = bones[i]->animations[anime2].translations[j].time -time1 ;
							float timeCurrent = time-time1;
							float timeslerp = timeCurrent /timeTotal;
						
					
						translation2 = bones[i]->animations[anime2].translations[j-1].pos *(1.0f -timeslerp) +bones[i]->animations[anime2].translations[j].pos *(timeslerp);

							break;
						}
				
					}
				}

				translation= translation1 *(1.0f -animeSlerp) +translation2 *(animeSlerp);

				bones[i]->animeMatrix.postMultTranslate(translation);
				
			
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

	
	//objectMatrix =  bones[0]->finalMatrix;
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

	