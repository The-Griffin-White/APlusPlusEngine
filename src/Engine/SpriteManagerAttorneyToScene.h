#ifndef _SpriteManagerAttorneyToScene
#define _SpriteManagerAttorneyToScene

#include "SpriteManager.h"

class SpriteManagerAttorneyToScene
{
private:
	friend class Scene;
	static void Update(SpriteManager* sprMgr) { sprMgr->Update(); };
	static void Draw(SpriteManager* sprMgr) { sprMgr->Draw(); };
};

#endif