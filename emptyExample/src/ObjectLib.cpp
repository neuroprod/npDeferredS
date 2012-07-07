
#include "ObjectLib.h"

void ObjectLib::setup()
{
	{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/treeTest.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/tree1.png",GL_RGBA);
	tree1_hr->material.loadNormal("3DAssets/tree1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}

		{
	npAssimpLoader loader;
	loader.load(ofToDataPath("3DAssets/grass.dae"));
	tree1_hr = loader.meshes[0];
	tree1_hr->material.loadDiffuse("3DAssets/grass.png",GL_RGBA);
	tree1_hr->material.loadNormal("3DAssets/tree1_n.png",GL_RGB );
	objects.push_back(tree1_hr);
	}
	
	
}

vector <npMesh *> ObjectLib::getGLClones()
{


	vector <npMesh *> clones;
	for (int i=0;i<objects.size();i++)
	{
		clones.push_back(objects[i]->getGLCopy());
		
	}

	return clones;
}