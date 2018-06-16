#ifndef _SceneAttorneyToSprite
#define _SceneAttorneyToSprite

#include "Scene.h"
#include "SceneManager.h"
#include "SpriteManager.h"

class SceneRegistrationCommand;
class Sprite;

class SceneAttorneyToSprite
{
private:
	friend class Sprite;
	static void SubmitCommand(SceneRegistrationCommand* cmd) { SceneManager::Get()->SubmitCommand(cmd); };
	static SpriteManager::SpriteListRef SceneRegistration(Sprite* p) { return SceneManager::Get()->AddSprite(p); };
	static void SceneDeregistration(SpriteManager::SpriteListRef p) { SceneManager::Get()->RemoveSprite(p); };
};

#endif