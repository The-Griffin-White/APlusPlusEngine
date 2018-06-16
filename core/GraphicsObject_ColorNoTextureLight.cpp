#include "GraphicsObject_ColorNoTextureLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>
#include "ShaderManager.h"

GraphicsObject_ColorNoTextureLight::GraphicsObject_ColorNoTextureLight(Model* mod)
{
	SetModel(mod);
	pShader = ShaderManager::GetShaderColorLight();

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	Ambient = new Vect[n];
	Diffuse = new Vect[n];
	Specular = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		Ambient[i] = Colors::White;
		Diffuse[i] = Colors::White;
		Specular[i] = Vect(1, 1, 1, 100);
	}
}

GraphicsObject_ColorNoTextureLight::~GraphicsObject_ColorNoTextureLight()
{
	delete[] Ambient;
	delete[] Diffuse;
	delete[] Specular;
}

void GraphicsObject_ColorNoTextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		Ambient[i] = amb;
		Diffuse[i] = dif;
		Specular[i] = sp;
	}
}

void GraphicsObject_ColorNoTextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	Ambient[meshnum] = amb;
	Diffuse[meshnum] = dif;
	Specular[meshnum] = sp;
}

void GraphicsObject_ColorNoTextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicsObject_ColorNoTextureLight::Render()
{
	pShader->SetToContext();
	pModel->BindVertexIndexBuffers(pShader->GetContext());

	EngineAttorneyToGraphics::SetSolidRender();

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, Ambient[i], Diffuse[i], Specular[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}