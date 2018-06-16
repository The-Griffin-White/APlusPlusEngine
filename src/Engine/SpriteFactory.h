#ifndef _SpriteFactory
#define _SpriteFactory

#include "APPECore.h"
#include "Camera.h"
#include <list>

class Sprite;

class SpriteFactory
{
private:
	static SpriteFactory *ptrInstance;

	SpriteFactory();
	SpriteFactory(const SpriteFactory&) = delete;
	SpriteFactory& operator=(const SpriteFactory&) = delete;
	~SpriteFactory();

	static SpriteFactory& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteFactory;
		return *ptrInstance;
	}
	
	std::list<Sprite*> recycledSprites;

	friend class SpriteFactoryAttorneyToEngine;
	static void Terminate();
	void Delete();

	Sprite* privCreateSprite(Texture* t, Rect* r);
	void privReycleSprite(Sprite* s);

public:
	/// \brief Creates and returns a new sprite to be drawn each frame.
	/// \ingroup SPRITE
	///
	/// \return The sprite we created
	/// \param t The Texture used to create the sprite.
	/// \param r The Rectangle dimensions of the sprite.
	static Sprite* CreateSprite(Texture* t, Rect* r) { return Instance().privCreateSprite(t, r); };

	/// \brief Recycles a sprite for later use
	/// \ingroup SPRITE
	///
	/// \param s The sprite to be recycled
	static void RecycleSprite(Sprite* s) { Instance().privReycleSprite(s); };

};

#endif _SpriteFactory