#include "FlatPlane_Object_NoLight.h"
#include "Model.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>

#include "FlatPlane.h"
#include "ShaderManager.h"

FlatPlane_Object_NoLight::FlatPlane_Object_NoLight(float size, float hrep, float vrep)
{
	pPlane = new FlatPlane(size, hrep, vrep);
	pShader = ShaderManager::GetShaderTexture();

	World = Matrix(IDENTITY);

	pTex = nullptr;
	Ambient = Vect(0, 0, 0);
	Diffuse = Vect(0, 0, 0);
	Specular = Vect(0, 0, 0);
}

FlatPlane_Object_NoLight::~FlatPlane_Object_NoLight()
{
	delete pPlane;
}

void FlatPlane_Object_NoLight::SetTexture(Texture* tex)
{
	pTex = tex;
}

void FlatPlane_Object_NoLight::SetWorld(const Matrix& m)
{
	World = m;
}

void FlatPlane_Object_NoLight::Render()
{
	pShader->SetToContext();

	EngineAttorneyToGraphics::SetSolidRender();

	pShader->SetTextureResourceAndSampler(pTex);
	pShader->SendWorld(World);
	pPlane->Render(pShader->GetContext());
}