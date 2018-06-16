#ifndef _Sprite
#define _Sprite

#include "APPECore.h"
#include "Align16.h"
#include <malloc.h>

#include "SpriteManager.h"

class SpriteRegistrationCommand;
class SpriteDeregistrationCommand;

class Sprite : public Align16
{
public:
	Sprite();
	void Initialize(Texture* i, Rect* r);
	~Sprite();

	/// \brief Sets the position of the sprite onscreen with an x/y coordinate
	/// \ingroup SPRITE
	///
	/// \param x New x-coordinate of the sprite
	/// \param y New y-coordinate of the sprite
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Initialize()
	///		{
	///			ExampleSprite->Pos(600.0f, 500.0f);
	///		}
	/// \endcode
	void Pos(const float& x, const float& y);
	/// \brief Sets the rotation of the sprite onscreen with an angle
	/// \ingroup SPRITE
	///
	/// \param angle New angle of the sprite
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Initialize()
	///		{
	///			ExampleSprite->Rot(90.0f);
	///		}
	/// \endcode
	void Rot(const float& angle);
	/// \brief Sets the scale of the sprite onscreen with a factor
	/// \ingroup SPRITE
	///
	/// \param factor New scale factor of the sprite
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Initialize()
	///		{
	///			ExampleSprite->Scale(2.5f);
	///		}
	/// \endcode
	void Scale(const float& factor);
	/// \brief Sets the scale of the sprite onscreen by setting a new height/width
	/// \ingroup SPRITE
	///
	/// \param height New height of the sprite
	/// \param width New width of the sprite
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Initialize()
	///		{
	///			ExampleSprite->Scale(100.0f, 200.0f);
	///		}
	/// \endcode
	void Scale(const float& height, const float& width);

	/// \brief Submits the sprite to be registered next frame; it will be drawn by the scene's SpriteManager
	/// \ingroup SPRITE
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SubmitEntry()
	///		{
	///			ExampleSprite->SubmitRegistration();
	///		}
	/// \endcode
	void SubmitRegistration();
	/// \brief Submits the sprite to be deregistered next frame; it will no longer be drawn
	/// \ingroup SPRITE
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SubmitExit()
	///		{
	///			ExampleSprite->SubmitDeregistration();
	///		}
	/// \endcode
	void SubmitDeregistration();

private:
	friend class SpriteAttorneyToManager;
	void Update();
	void Draw();

	friend class SpriteAttorneyToCommands;
	void SceneRegistration();
	void SceneDeregistration();

	GraphicsObject_Sprite * sprite;

	// Use this to scale down the translate values
	float xFix;
	float yFix;

	Matrix scale;
	Matrix rot;
	Matrix trans;
	bool newWorld;

	SpriteRegistrationCommand* pReg;
	SpriteDeregistrationCommand* pDereg;
	SpriteManager::SpriteListRef pRef;

};

#endif _Sprite