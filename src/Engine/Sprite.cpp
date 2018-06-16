#include "Sprite.h"

#include "SpriteFactory.h"

#include "SceneAttorneyToSprite.h"

#include "SpriteRegistrationCommand.h"
#include "SpriteDeregistrationCommand.h"
#include "APlusPlusEngine.h"

Sprite::Sprite()
{
	sprite = nullptr;
	pReg = new SpriteRegistrationCommand(this);
	pDereg = new SpriteDeregistrationCommand(this);

	xFix = (1 / (float)APlusPlusEngine::GetWindowWidth()) * -0.1f;
	yFix = (1 / (float)APlusPlusEngine::GetWindowHeight()) * 0.1f;
}

void Sprite::SceneRegistration()
{
	pRef = SceneAttorneyToSprite::SceneRegistration(this);
}
void Sprite::SceneDeregistration()
{
	SceneAttorneyToSprite::SceneDeregistration(pRef);
}
void Sprite::SubmitRegistration()
{
	SceneAttorneyToSprite::SubmitCommand(pReg);
}
void Sprite::SubmitDeregistration()
{
	SceneAttorneyToSprite::SubmitCommand(pDereg);
}

void Sprite::Initialize(Texture* i, Rect* r)
{
	if (sprite) delete sprite;
	sprite = new GraphicsObject_Sprite(r);
	sprite->SetTexture(i);
	scale = Matrix(IDENTITY);
	rot = Matrix(IDENTITY);
	trans = Matrix(IDENTITY);
	newWorld = false;
}

Sprite::~Sprite()
{
	delete sprite;
	delete pReg;
	delete pDereg;
}

void Sprite::Pos(const float& x, const float& y)
{
	Matrix world(TRANS, x * xFix, y * yFix, 0);
	trans = world;
	newWorld = true;
}
void Sprite::Rot(const float& angle)
{
	Matrix world(ROT_Z, angle);
	rot = world;
	newWorld = true;
}
void Sprite::Scale(const float& factor)
{
	Matrix world(SCALE, factor, factor, factor);
	scale = world;
	newWorld = true;
}
void Sprite::Scale(const float& height, const float& width)
{
	sprite->UpdateRect(height, width);
}
void Sprite::Update()
{
	if (newWorld)
	{
		Matrix world = trans * rot * scale;
		sprite->SetWorld(world);
		newWorld = false;
	}
}
void Sprite::Draw()
{
	sprite->Render();
}