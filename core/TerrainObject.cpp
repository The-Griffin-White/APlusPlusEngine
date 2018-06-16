#include "TerrainObject.h"
#include "Model.h"
#include "ShaderTexLight.h"
#include "Texture.h"
#include <assert.h>

#include "TerrainModel.h"
#include "ShaderManager.h"

TerrainObject::TerrainObject(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, 
	float firstU, float secondU, float firstV, float secondV)
{
	pShader = ShaderManager::GetShaderTexLight();
	pTerrain = new TerrainModel(heightmapFile, len, maxheight, ytrans, firstU, secondU, firstV, secondV);
	World = Matrix(IDENTITY);

	pTex = nullptr;
	Ambient = Vect(0, 0, 0);
	Diffuse = Vect(0, 0, 0);
	Specular = Vect(0, 0, 0);
}

TerrainObject::~TerrainObject()
{
	delete pTerrain;
}

void TerrainObject::SetTexture(Texture* tex)
{
	pTex = tex;
}

void TerrainObject::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	Ambient = amb;
	Diffuse = dif;
	Specular = sp;	
}

void TerrainObject::SetWorld(const Matrix& m)
{
	World = m;
}

void TerrainObject::Render()
{
	pShader->SetToContext();

	pShader->SetTextureResourceAndSampler(pTex);
	pShader->SendWorldAndMaterial(World, Ambient, Diffuse, Specular);
	pTerrain->Render(pShader->GetContext());
}