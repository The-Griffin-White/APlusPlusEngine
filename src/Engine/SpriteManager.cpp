#include "SpriteManager.h"
#include "APlusPlusEngine.h"

#include "ModelManager.h"
#include "ShaderManager.h"

#include "Sprite.h"
#include "SpriteAttorneyToManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	DebugMsg::out("Deleted SpriteManager\n");
	this->Delete();
}

void SpriteManager::Delete()
{
	spriteList.clear();
}

SpriteManager::SpriteListRef SpriteManager::AddSprite(Sprite* s)
{
	return spriteList.insert(spriteList.end(), s);
}
void SpriteManager::RemoveSprite(SpriteManager::SpriteListRef p)
{
	spriteList.erase(p);
}

void SpriteManager::Update()
{
	for (auto const& i : spriteList)
	{
		SpriteAttorneyToManager::Update(i);
	}
}
void SpriteManager::Draw()
{
	for (auto const& i : spriteList)
	{
		SpriteAttorneyToManager::Draw(i);
	}
}