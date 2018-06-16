#include "GraphicsObject_ColorNoTexture.h"
#include "Model.h"
#include "ShaderColor.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>
#include "ShaderManager.h"

GraphicsObject_ColorNoTexture::GraphicsObject_ColorNoTexture(Model* mod)
{
	SetModel(mod );
	pShader = ShaderManager::GetShaderColor();

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshColors = new Vect[n];
	for (int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

GraphicsObject_ColorNoTexture::~GraphicsObject_ColorNoTexture()
{
	delete[] MeshColors;
}

void GraphicsObject_ColorNoTexture::SetColor(const Vect& col)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicsObject_ColorNoTexture::SetColor(const Vect& col, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicsObject_ColorNoTexture::SetWorld(const Matrix& m)
{ 
	World = m;
}

void GraphicsObject_ColorNoTexture::Render()
{
	pShader->SetToContext();
	pModel->BindVertexIndexBuffers(pShader->GetContext());

	EngineAttorneyToGraphics::SetSolidRender();

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(World, MeshColors[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}