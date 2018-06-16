#include "GraphicsObject_TextureLight.h"
#include "Model.h"
#include "ShaderTexLight.h"
#include "Texture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>
#include "ShaderManager.h"

GraphicsObject_TextureLight::GraphicsObject_TextureLight(Model* mod)
{
	SetModel(mod);
	pShader = ShaderManager::GetShaderTexLight();

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pTex = new Texture*[n];
	Ambient = new Vect[n];
	Diffuse = new Vect[n];
	Specular = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		pTex[i] = nullptr; 
		Ambient[i] = Colors::White;
		Diffuse[i] = Colors::White;
		Specular[i] = Vect(1, 1, 1, 100);
	}
}

GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
{
	delete[] Ambient;
	delete[] Diffuse;
	delete[] Specular;
}

void GraphicsObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		pTex[i] = tex;
	}
}

void GraphicsObject_TextureLight::SetTexture(Texture* tex, const int& meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	pTex[meshnum] = tex;
}

void GraphicsObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		Ambient[i] = amb;
		Diffuse[i] = dif;
		Specular[i] = sp;
	}
}

void GraphicsObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	Ambient[meshnum] = amb;
	Diffuse[meshnum] = dif;
	Specular[meshnum] = sp;
}

void GraphicsObject_TextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicsObject_TextureLight::Render()
{
	pShader->SetToContext();
	pModel->BindVertexIndexBuffers(pShader->GetContext());

	EngineAttorneyToGraphics::SetSolidRender();

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pTex[i]);
		pShader->SendWorldAndMaterial(World, Ambient[i], Diffuse[i], Specular[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}

}