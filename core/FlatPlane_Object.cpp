#include "FlatPlane_Object.h"
#include "Model.h"
#include "ShaderTexLight.h"
#include "Texture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>

#include "FlatPlane.h"
#include "ShaderManager.h"

FlatPlane_Object::FlatPlane_Object(float size, float hrep, float vrep)
{
	pPlane = new FlatPlane(size, hrep, vrep);
	pShader = ShaderManager::GetShaderTexLight();

	World = Matrix(IDENTITY);

	pTex = nullptr;
	Ambient = Vect(0, 0, 0);
	Diffuse = Vect(0, 0, 0);
	Specular = Vect(0, 0, 0);
}

FlatPlane_Object::~FlatPlane_Object()
{
	delete pPlane;
}

void FlatPlane_Object::SetTexture(Texture* tex)
{
	pTex = tex;
}

void FlatPlane_Object::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	Ambient = amb;
	Diffuse = dif;
	Specular = sp;

}

void FlatPlane_Object::SetWorld(const Matrix& m)
{
	World = m;
}

void FlatPlane_Object::Render()
{
	pShader->SetToContext();

	EngineAttorneyToGraphics::SetSolidRender();

	pShader->SetTextureResourceAndSampler(pTex);
	pShader->SendWorldAndMaterial(World, Ambient, Diffuse, Specular);
	pPlane->Render(pShader->GetContext());
}