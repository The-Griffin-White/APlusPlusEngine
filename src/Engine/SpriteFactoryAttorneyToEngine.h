#ifndef _SpriteFactoryAttorneyToEngine
#define _SpriteFactoryAttorneyToEngine

#include "SpriteFactory.h"

class SpriteFactoryAttorneyToEngine
{
private:
	friend class APlusPlusEngine;
	static void Delete() { SpriteFactory::Instance().Delete(); };
	static void Terminate() { SpriteFactory::Terminate(); };
};

#endif _SpriteFactoryAttorneyToEngine