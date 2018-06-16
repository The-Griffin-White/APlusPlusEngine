#include "GraphicsObject_Sprite.h"
#include "Model.h"
#include "ShaderTexLight.h"
#include "ShaderTexture.h"
#include "EngineAttorneyToGraphics.h"
#include <assert.h>
#include "ShaderManager.h"
#include "ModelManager.h"
#include "FlatPlane.h"

GraphicsObject_Sprite::GraphicsObject_Sprite()
{
	rect = new Rect(0, 0, 1, 1);

	SetModel(ModelManager::Get("Sprite"));
	pShader = ShaderManager::GetShaderTexture();

	spriteSpace = Matrix(SCALE, rect->width * 1, rect->height * 1, 1)
		* Matrix(TRANS, 0.055f, -0.042f, 0);
	World = spriteSpace;

	pTex = nullptr;
}

GraphicsObject_Sprite::GraphicsObject_Sprite(Rect* _rect)
	: rect(_rect)
{
	SetModel(ModelManager::Get("Sprite"));
	pShader = ShaderManager::GetShaderTexture();

	spriteSpace = Matrix(SCALE, rect->width * 1, rect->height * 1, 1)
		* Matrix(TRANS, 0.055f, -0.042f, 0);
	World = spriteSpace;

	pTex = nullptr;
}

GraphicsObject_Sprite::~GraphicsObject_Sprite()
{
	delete rect;
}

void GraphicsObject_Sprite::SetTexture(Texture* tex)
{
	pTex = tex;
}
void GraphicsObject_Sprite::SetWorld(const Matrix& m)
{
	World = spriteSpace * m;
}

void GraphicsObject_Sprite::UpdateRect(float _height, float _width)
{
	rect->height = _height;
	rect->width = _width;
	spriteSpace = Matrix(SCALE, rect->width * 1, rect->height * 1, 1)
		* Matrix(TRANS, 0.055f, -0.042f, 0);
}

void GraphicsObject_Sprite::Render()
{
	pShader->SetToContext2D();
	pModel->BindVertexIndexBuffers(pShader->GetContext());

	EngineAttorneyToGraphics::SetSolidRender();

	pShader->SetTextureResourceAndSampler(pTex);
	pShader->SendWorld(World);
	pModel->Render(pShader->GetContext());
}