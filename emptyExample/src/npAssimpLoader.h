#pragma once

#include "npIncludes.h"
#include "assimp.h"
#include "aiScene.h"
#include "npMesh.h"
#include "npBoneMesh.h"
#include "npBone.h"
class npAssimpLoader
{
public:

	npAssimpLoader(){};
	void load(string fileName);
	void  processScene();

	void  makeBoneMesh(aiMesh *mesh);
	void getAnime();
	void  makeMesh(aiMesh *mesh);
	
	npBone * getBoneByName(string name);
	void aiMatrix4x4ToOfMatrix4x4(const aiMatrix4x4& aim, ofMatrix4x4& ofm);
	
	
	const aiScene* scene;

	vector < npBoneMesh *> boneMeshes;
	vector < npMesh *>meshes;
	
	void addAnimation(string fileName);
};

