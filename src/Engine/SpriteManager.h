#ifndef _SpriteManager
#define _SpriteManager

#include <list>
#include "APPECore.h"

class Sprite;

class SpriteManager
{
public:
	using SpriteList = std::list<Sprite*>;
	using SpriteListRef = SpriteList::iterator;

	SpriteManager();
	~SpriteManager();

	void Delete();

	/// \brief Adds sprite to the manager to be drawn each frame
	/// \ingroup SPRITE-MANAGE
	/// \param s Pointer to sprite we're adding to the manager
	/// \return Reference to this Sprite's position in the list - used when removing it
	SpriteListRef AddSprite(Sprite* s);
	/// \brief Removes sprite from the manager; it will no longer be drawn
	/// \ingroup SPRITE-MANAGE
	/// \param p Reference to the Sprite's position in the list - used for quick removal
	void RemoveSprite(SpriteListRef p);

private:
	SpriteList spriteList;

	friend class SpriteManagerAttorneyToScene;
	/// \brief Updates all sprites with any worldmatrix data given to them.
	/// \ingroup SPRITE-MANAGE
	void Update();

	/// \brief Draws all sprites.
	/// \ingroup SPRITE-MANAGE
	void Draw();
	
};

#endif