#ifndef _SpriteAttorneyToManager
#define _SpriteAttorneyToManager

#include "Sprite.h"

class SpriteAttorneyToManager
{
private:
	friend class SpriteManager;
	static void Update(Sprite* s) { s->Update(); };
	static void Draw(Sprite* s) { s->Draw(); };
};

#endif _SpriteAttorneyToManager