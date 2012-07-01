
#include "npAssimpLoader.h"
#include "aiConfig.h"
#include "aiPostProcess.h"
#include "npBoneAnimation.h"

void npAssimpLoader::load(string fileName)
{



	aiSetImportPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT );
    aiSetImportPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, true);

    // aiProcess_FlipUVs is for VAR code. Not needed otherwise. Not sure why.
    unsigned int flags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_FlipUVs| aiProcess_ImproveCacheLocality | aiProcess_OptimizeGraph |aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices |
			aiProcess_RemoveRedundantMaterials|aiProcess_CalcTangentSpace ;
	
    scene = aiImportFile(fileName.c_str(), flags);

	if(scene)
	{
	processScene();
	
	}else
	{
	cout << "didn't load "<<fileName;
	
	}






}
void npAssimpLoader::processScene()
{


	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		
		aiMesh* mesh = scene->mMeshes[i];
			 
		if (mesh->HasBones())
		{	 
				 makeBoneMesh(mesh); 
				 getAnime();
		}
		else
		{ 
			makeMesh( mesh );
		}
}

}
void  npAssimpLoader::makeBoneMesh(aiMesh *mesh)
{
	
	npBoneMesh * boneMesh = new npBoneMesh();

	int numVertices  = mesh->mNumVertices;
	vector < vector<pair <unsigned,float>> > boneweights;
	boneweights.resize(numVertices);
	aiBone **bones  =mesh->mBones;
	if (mesh->mNumBones != 22) cout << "WARNING CURRENT SHADERS SUPPORTS 22 BONES +ROOT, NOW USING "<< mesh->mNumBones<< endl;
	
	npBone *bone = new npBone();
	bone->name ="root";
	bone->finalMatrix.makeIdentityMatrix();
	bone->boneMatrix.makeIdentityMatrix();
	boneMesh->bones.push_back(bone);
	boneMesh->rootBone  = bone;
	for (int i =0;i<mesh->mNumBones;i++)
	{
			aiBone *aibone   	 =bones[i] ;
			npBone *bone = new npBone();

			bone->finalMatrix.makeIdentityMatrix();
			bone->id = i+1;
			bone->name= aibone->mName.data ;
		
			aiMatrix4x4ToOfMatrix4x4(aibone->mOffsetMatrix,bone->boneMatrix);

			for (unsigned j=0;j< aibone->mNumWeights;j++)
			{
				aiVertexWeight iaWeight =aibone->mWeights[j];

				boneweights[iaWeight.mVertexId].push_back(make_pair(i,iaWeight.mWeight));
			
			}
		
	
			boneMesh->bones.push_back(bone);
	}
	boneMeshes.push_back(boneMesh);
	for (int i =0;i<boneMesh->bones.size();i++)
	{
		
		aiNode *node; 
		npBone * bone = boneMesh->bones[i];
	
			
		node =scene->mRootNode->FindNode( bone->name);
		

		if (node->mParent)
		{
			string parentName =  node->mParent->mName.data;
			bone->parent = getBoneByName(parentName );
		}
		else
		{
			bone->parent =NULL;
		}



		for(int j=0;j< node->mNumChildren;j++)
		{
		
			string childName =  node->mChildren[j]->mName.data;
		
			bone->children.push_back( getBoneByName(childName ));
		}
		
		aiMatrix4x4ToOfMatrix4x4( node->mTransformation, bone->nodeMatrix);

	}
	//getBoneByName("root" )->parent =NULL;


	boneMesh->numVertices = mesh->mNumVertices;
	boneMesh->stride = 3+3+2+2+2;
	boneMesh->vertices =new float[numVertices*boneMesh->stride ];

	int count =0;
	for (int i=0;i<mesh->mNumVertices;i++)
	{
		//cout << 	boneweights[i].size()<<endl;
		float id1 =0;
		float id2 =0;
		float weight1=0;
		float weight2=0;
		
		if (boneweights[i].size()==1)
		{
			 id1 =boneweights[i][0].first;
			 weight1 =1;
			 id2=0;
			 weight2 =0;
		}
		else if (boneweights[i].size()==2)
		{
			 id1 =boneweights[i][0].first;
			 weight1 =boneweights[i][0].second;
			 id2=boneweights[i][1].first;
			 weight2 =boneweights[i][1].second;
		}
		else if (boneweights[i].size()==0)
		{
			 id1 =0;
			 weight1 =1;
			 id2=0;
			 weight2 =0;
		}
		else if (boneweights[i].size()>2)
		{
			// only 2 weights in mij vertex shader
			// take 2 max
			for(int j=0;j< boneweights[i].size() ;j++)
			{
				if (boneweights[i][j].second>weight1)
				{
					weight2 =weight1;
					id2 =id1;
					id1 =boneweights[i][j].first;
					weight1 =boneweights[i][j].second;

				}
				else if (boneweights[i][j].second>weight2)
				{
					id2 =boneweights[i][j].first;
					weight2 =boneweights[i][j].second;
				
				}
			}
			
		
			
	
		}
	
		if (weight1 ==0)
		{
			weight2=1;
		}
		else if(weight2 ==0)
		{
			weight1=1;
		}
		else
		{
			weight2= 1-weight1;
		}


		boneMesh->vertices[count++] = mesh->mVertices[i].x ;
		boneMesh->vertices[count++] = mesh->mVertices[i].y ;
		boneMesh->vertices[count++] = mesh->mVertices[i].z ;

		boneMesh->vertices[count++] = mesh->mNormals[i].x;
		boneMesh->vertices[count++] = mesh->mNormals[i].y;
		boneMesh->vertices[count++] = mesh->mNormals[i].z;


		boneMesh->vertices[count++] = mesh->mTextureCoords[0][i].x;
		boneMesh->vertices[count++] = mesh->mTextureCoords[0][i].y;
			
		boneMesh->vertices[count++] =id1;
		boneMesh->vertices[count++] =id2;
		
		boneMesh->vertices[count++] =weight1;
		boneMesh->vertices[count++] =weight2;

	

		
	}
		


	boneMesh->numIndices = mesh->mNumFaces*3;
	boneMesh->indices =new unsigned[boneMesh->numIndices];

	count =0;
	for (int i=0;i< mesh->mNumFaces;i++)
	{
			for (unsigned int a = 0; a < 3; ++a){
				boneMesh->indices[count++]=mesh->mFaces[i].mIndices[a];
			}
	}

	boneMesh->createBuffers();
	boneMesh->prepBones();
	


}
void  npAssimpLoader::makeMesh(aiMesh *mesh)
{

	npMesh * npmesh = new npMesh();

	

	meshes.push_back( npmesh );
	
		


	 npmesh->numVertices = mesh->mNumVertices;
	npmesh->stride = 3+3+3+2;
	npmesh->vertices =new float[npmesh->numVertices*npmesh->stride ];

	int count =0;
	for (int i=0;i<mesh->mNumVertices;i++)
	{
		
		
		npmesh->vertices[count++] = mesh->mVertices[i].x ;
		npmesh->vertices[count++] = mesh->mVertices[i].y ;
		npmesh->vertices[count++] = mesh->mVertices[i].z ;

		npmesh->vertices[count++] = mesh->mNormals[i].x;
		npmesh->vertices[count++] = mesh->mNormals[i].y;
		npmesh->vertices[count++] = mesh->mNormals[i].z;

		npmesh->vertices[count++] = mesh->mTangents[i].x;
		npmesh->vertices[count++] = mesh->mTangents[i].y;
		npmesh->vertices[count++] = mesh->mTangents[i].z;
	

		npmesh->vertices[count++] = mesh->mTextureCoords[0][i].x;
		npmesh->vertices[count++] = mesh->mTextureCoords[0][i].y;
	
		

	

		
	}
		


	npmesh->numIndices = mesh->mNumFaces*3;
	npmesh->indices =new unsigned[npmesh->numIndices];

	count =0;
	for (int i=0;i< mesh->mNumFaces;i++)
	{
			for (unsigned int a = 0; a < 3; ++a){
				npmesh->indices[count++]=mesh->mFaces[i].mIndices[a];
			}
	}

	npmesh->createBuffers();

}
void  npAssimpLoader::getAnime()
{

	const aiAnimation* mAnim = scene->mAnimations[0];
	
//	cout << mAnim->mName.data << " anime name"<< endl;
	float duration = mAnim->mDuration;

	for( unsigned int a = 0; a < mAnim->mNumChannels; a++)
	{
		const aiNodeAnim* channel = mAnim->mChannels[a];

		aiNode* targetNode = scene->mRootNode->FindNode(channel->mNodeName);
		npBone * targetBone = getBoneByName(targetNode->mName.data);

		npBoneAnimation anime;
		
		anime.totalTime  =duration;



        if( channel->mNumPositionKeys > 0)
        {
		
			for (int p=0;p<channel->mNumPositionKeys;p++)
			{
				//cout <<"pos:"<< channel->mPositionKeys[p].mTime<< " "<< channel->mPositionKeys[p].mValue.x <<","<< channel->mPositionKeys[p].mValue.y<<","<< channel->mPositionKeys[p].mValue.z << endl;
				npAnimeTranslation trans;
				trans.pos.set( channel->mPositionKeys[p].mValue.x, channel->mPositionKeys[p].mValue.y, channel->mPositionKeys[p].mValue.z);
				trans.time =channel->mPositionKeys[p].mTime;
				anime.translations.push_back(trans);
			
			}





		
		}else 
		{
		
			npAnimeTranslation trans;
			trans.pos.set(0,0,0);
			trans.time =0;
			anime.translations.push_back(trans);
		
		}

		
        if( channel->mNumRotationKeys > 0)
        {
				for (int p=0;p<channel->mNumRotationKeys;p++)
				{
					

					npAnimeRotation rot;
					rot.quat.set(channel->mRotationKeys[p].mValue.x,channel->mRotationKeys[p].mValue.y,channel->mRotationKeys[p].mValue.z,channel->mRotationKeys[p].mValue.w);

					rot.time =	channel->mRotationKeys[p].mTime;
					anime.rotations.push_back(rot);
				
				
				
				}
			
          
		}else
		{
			npAnimeRotation rot;
			rot.quat.set(1,0,0,0);
			rot.time =	0;
			anime.rotations.push_back(rot);
		}


		targetBone->animations.push_back(anime);
	

	}

	

}

npBone * npAssimpLoader::getBoneByName(string name)
{
	

	for (int i=0;i<boneMeshes[0]->bones.size();i++)
	{
	
		if (boneMeshes[0]->bones[i]->name.compare(name) == 0)
		{
			return boneMeshes[0]->bones[i];
		}
	}
	npBone *rBone;
	rBone =new npBone();
	rBone->boneMatrix.makeIdentityMatrix();
	rBone->isNodeBone =true;
	rBone->name = name;

	boneMeshes[0]->bones.push_back(rBone);
	return rBone;
}


void npAssimpLoader::aiMatrix4x4ToOfMatrix4x4(const aiMatrix4x4& aim, ofMatrix4x4& ofm){

	float m[16] = { aim.a1,aim.b1,aim.c1,aim.d1,
					aim.a2,aim.b2,aim.c2,aim.d2,
					aim.a3,aim.b3,aim.c3,aim.d3,
					aim.a4,aim.b4,aim.c4,aim.d4 };

	ofm.set(	m);
}