
#include "ObjectLib.h"

void ObjectLib::setup()
{
	{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/treeTest2.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/tree1.png",GL_RGBA);
	tree1_hr->material.loadNormal("3DAssets/tree1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}

	{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/grass.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/grass1.png",GL_RGBA);
	tree1_hr->material.loadNormal("3DAssets/grass1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}
	{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/rocks1.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/rocks1.png",GL_RGB);
	tree1_hr->material.loadNormal("3DAssets/rocks1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}
		{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/plant1.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/rocks1.png",GL_RGB);
	tree1_hr->material.loadNormal("3DAssets/rocks1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}
	for (int i =0;i<20;i++)
	{
		npPointLight *p = new npPointLight();
		p->setup(10+(float) rand()/RAND_MAX *30,(float) rand()/RAND_MAX *2,(float) rand()/RAND_MAX *2,(float) rand()/RAND_MAX*2 ,0.4f);
		//p->setPos (vertex->position.x,vertex->position.y +5,vertex->position.z);
		 pointLights.push_back(p );
	}
	
}
/*
void  ObjectLib::getMultiMeshes(Chunk *chunk)
{

	chunk->detail1Objects.push_back(npMultiMesh(objects[0]));
	chunk->detail1Objects.push_back(npMultiMesh(objects[1]));
	*/
//}