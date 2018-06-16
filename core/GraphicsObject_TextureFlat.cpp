#include "GraphicsObject_TextureFlat.h"
#include "Model.h"
#include "ShaderTexture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>
#include "ShaderManager.h"

GraphicsObject_TextureFlat::GraphicsObject_TextureFlat(Model* mod)
{
	SetModel(mod);
	pShader = ShaderManager::GetShaderTexture();

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pTex = new Texture*[n];
	for (int i = 0; i < n; i++)
	{
		pTex[i] = nullptr;
	}
}

GraphicsObject_TextureFlat::~GraphicsObject_TextureFlat()
{
}

void GraphicsObject_TextureFlat::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		pTex[i] = tex;
	}
}

void GraphicsObject_TextureFlat::SetTexture(Texture* tex, const int& meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	pTex[meshnum] = tex;
}

void GraphicsObject_TextureFlat::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicsObject_TextureFlat::Render()
{
	pShader->SetToContext();
	pModel->BindVertexIndexBuffers(pShader->GetContext());

	EngineAttorneyToGraphics::SetSolidRender();

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pTex[i]);
		pShader->SendWorld(World);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}