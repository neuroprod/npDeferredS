#include "TerrainTextureHandler.h"

void TerrainTextureHandler::setup()
{


}
void TerrainTextureHandler::getChunkMaterial(Chunk *chunk)
{

	cout <<detailMaterials.size();
	for (int i=0;i< detailMaterials.size();i++)
	{
		if (!detailMaterials[i]->isUsed)
		{
		

			updateDetailMaterial(detailMaterials[i],chunk);

		return;

		}
		
	}
	TerrainMaterial *mat =new TerrainMaterial();
	detailMaterials.push_back(mat);
	updateDetailMaterial(mat,chunk);

}
void TerrainTextureHandler::updateDetailMaterial(TerrainMaterial *mat,Chunk *chunk)
{
	mat->isUsed =true;
	chunk->currentDetailMaterial=mat;


}