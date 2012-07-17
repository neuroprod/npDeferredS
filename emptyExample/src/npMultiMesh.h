#pragma once

#include "npIncludes.h"
#include "npMesh.h"

class npMultiMesh
{
public: 
	npMultiMesh(){};
	npMultiMesh(npMesh *_mesh){ mesh =_mesh;combinedMesh=NULL;isCombinedMesh =false;};
	~npMultiMesh(){if (isCombinedMesh) {


	glDeleteBuffers(1 ,&combinedMesh->vertexBuffer);
		glDeleteBuffers(1 ,&combinedMesh->indexBuffer);
	delete combinedMesh;
	combinedMesh =NULL;
	isCombinedMesh =false;
	} };

	npMesh *mesh;
	npMesh *combinedMesh;
	vector <ofMatrix4x4> objectMatrices;
	vector <ofMatrix4x4> normalMatrices;
	void makeOneMesh();
	
	void calculateNormalMatrices()
    {
		normalMatrices.clear();
		
		for(int i=0;i< objectMatrices.size();i++)
		{
				ofQuaternion q = objectMatrices[i].getRotate();
				q.inverse();
				ofMatrix4x4 normalMatrix;
				q.get(normalMatrix);
				normalMatrices.push_back( normalMatrix);
		}
        
    }
	bool isCombinedMesh;
};