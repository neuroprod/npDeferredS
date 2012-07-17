#include "npMultiMesh.h"


void npMultiMesh::makeOneMesh()
{
		int numObjects  = objectMatrices.size();
	if (numObjects<2) return;


	isCombinedMesh = true;
	combinedMesh = new npMesh();
	int numVerticesM = mesh->numVertices ;
	int numIndicesM = mesh->numIndices ;
	int numVerticesT = mesh->numVertices *numObjects;
	int numIndicesT = mesh->numIndices *numObjects;
	int stride =mesh->stride;
	
	combinedMesh->vertices =  new float[numVerticesM*numObjects* stride];
	
	float * vertices =combinedMesh->vertices;
	
	combinedMesh->indices= new unsigned int [numIndicesM *numObjects];

	unsigned int *indices =combinedMesh->indices;
	combinedMesh->stride = stride;
	combinedMesh->numVertices = numVerticesT;
	combinedMesh->numIndices = numIndicesT;
	
	int indexCount =0;
	int vertexCount =0;
	ofMatrix4x4 objectMatrix;
	ofVec3f pos ;
	ofVec3f post ;
	
	for(int i=0;i<numObjects;i++)
	{
		objectMatrix = objectMatrices[i];
	
		for(int j=0;j<numVerticesM;j++)
		{
			int ofset =  (i* numVerticesM*stride) +(j*stride);
			pos.set(mesh->vertices[j*stride],mesh->vertices[j*stride +1],mesh->vertices[j*stride+2]);
			post =pos* objectMatrix;
	
			vertices[vertexCount ++ ] = post.x;
			vertices[vertexCount ++  ] = post.y;
			vertices[vertexCount ++ ] = post.z;

			vertices[vertexCount ++ ] =  mesh->vertices[j*stride +3];
			vertices[vertexCount ++ ] =  mesh->vertices[j*stride +4];;
			vertices[vertexCount ++ ] =  mesh->vertices[j*stride +5];;


			vertices[vertexCount ++ ] =mesh->vertices[j*stride +6];
			vertices[vertexCount ++  ] = mesh->vertices[j*stride +7];
			vertices[vertexCount ++ ] =mesh->vertices[j*stride +8];


			vertices[vertexCount ++ ] = mesh->vertices[j*stride +9];
			vertices[vertexCount ++ ] = mesh->vertices[j*stride +10];
			

		}
		int ofset =i* numVerticesM;
		for(int j=0;j<numIndicesM;j++)
		{
		
			int index = mesh->indices[j];
			indices[indexCount] = index +ofset;
			indexCount++;
		}
	
	
	
	}
	combinedMesh->material.diffuseTexture =mesh->material.diffuseTexture;
		combinedMesh->material.normalTexture =mesh->material.normalTexture;
	combinedMesh->objectMatrix.makeIdentityMatrix();
	combinedMesh->normalMatrix.makeIdentityMatrix();
	combinedMesh->createBuffers();
	
	delete [] combinedMesh->indices;
	combinedMesh->indices =NULL;
	delete [] combinedMesh->vertices;
	combinedMesh->vertices =NULL;

	/*mesh->numVertices;
	mesh->vertices;
	mesh->stride;
	mesh->indices;
	mesh->numIndices;*/

	
	
}