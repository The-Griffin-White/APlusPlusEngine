#ifndef _Drawable
#define _Drawable

#include "DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

enum class RegistrationState;

class Drawable
{
public:
	Drawable();
	virtual ~Drawable();

protected:
	/// \brief The scene will call the objects Draw() function every frame
	/// \ingroup DRAW
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Drawable::SubmitDrawRegistration();
	///		}
	/// \endcode
	void SubmitDrawRegistration();
	/// \brief Deregisters the object so that it's Draw() function is not called
	/// \ingroup DRAW
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Drawable::SubmitDrawDeregistration();
	///		}
	/// \endcode
	void SubmitDrawDeregistration();

private:
	friend class DrawableAttorneyToDrawableManager;
	friend class DrawableAttorneyToDrawRegCmd;
	friend class DrawableAttorneyToDrawDeregCmd;
	/// \brief Called every frame and used to render the object's models, textures, sprites, etc.
	/// \ingroup DRAW
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Draw()
	///		{
	///			MainModel->Render(SceneManager::GetCurrentCamera());
	///		}
	/// \endcode
	virtual void Draw() {};

	void SceneRegistration();
	void SceneDeregistration();

	RegistrationState RegStateCurr;
	DrawableManager::DrawableListRef storageRef;
	DrawRegistrationCommand* pRegistrationCmd;
	DrawDeregistrationCommand* pDeregistrationCmd;
};

#endif