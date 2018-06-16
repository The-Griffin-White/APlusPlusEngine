#include "SpriteFactory.h"
#include "APlusPlusEngine.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "Sprite.h"

SpriteFactory* SpriteFactory::ptrInstance = nullptr;

SpriteFactory::SpriteFactory()
{
	// The orthographic camera, model, and shader are handled elsewhere this time around, so nothing here
}

SpriteFactory::~SpriteFactory()
{
	DebugMsg::out("Deleted SpriteFactory\n");
	this->Delete();
}

void SpriteFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
void SpriteFactory::Delete()
{
	while (!recycledSprites.empty())
	{
		delete recycledSprites.front();
		recycledSprites.pop_front();
	}
}

Sprite* SpriteFactory::privCreateSprite(Texture* i, Rect* r)
{
	Sprite* b;
	if (recycledSprites.empty())
	{
		b = new Sprite;
	}
	else
	{
		b = recycledSprites.front();
		recycledSprites.pop_front();
	}
	b->Initialize(i, r);

	return b;
}
void SpriteFactory::privReycleSprite(Sprite* s)
{
	recycledSprites.push_front(s);
}