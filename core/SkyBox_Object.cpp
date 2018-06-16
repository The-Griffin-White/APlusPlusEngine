#include "SkyBox_Object.h"
#include "Model.h"
#include "ShaderTexLight.h"
#include "Texture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>

#include "SkyBox.h"
#include "SFXManager.h"

SkyBox_Object::SkyBox_Object(float scale, ShaderTexLight* shader)
{
	pSkyBox = new SkyBox(scale);
	pShader = shader;

	World = Matrix(IDENTITY);

	pTex = nullptr;
	Ambient = Vect(0, 0, 0);
	Diffuse = Vect(0, 0, 0);
	Specular = Vect(0, 0, 0);
}

SkyBox_Object::~SkyBox_Object()
{
	delete pSkyBox;
}

void SkyBox_Object::SetTexture(Texture* tex)
{
	pTex = tex;
}

void SkyBox_Object::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	Ambient = amb;
	Diffuse = dif;
	Specular = sp;

}

void SkyBox_Object::SetWorld(const Matrix& m)
{
	World = m;
}

void SkyBox_Object::Render()
{
	pShader->SetToContext();

	EngineAttorneyToGraphics::SetSolidRender();

	pShader->SetTextureResourceAndSampler(pTex);
	pShader->SendWorldAndMaterial(World, Ambient, Diffuse, Specular);
	pSkyBox->Render(pShader->GetContext());
}