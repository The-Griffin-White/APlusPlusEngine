#ifndef _SpriteAttorneyToCommands
#define _SpriteAttorneyToCommands

#include "Sprite.h"

class SpriteAttorneyToCommands
{
private:
	friend class SpriteRegistrationCommand;
	friend class SpriteDeregistrationCommand;
	static void SceneRegistration(Sprite* s) { s->SceneRegistration(); };
	static void SceneDeregistration(Sprite* s) { s->SceneDeregistration(); };
};

#endif