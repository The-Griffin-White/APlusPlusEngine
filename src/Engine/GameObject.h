#ifndef _GameObject
#define _GameObject

#include <malloc.h>

#include "APPECore.h"
#include "Align16.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject 
	: public Drawable, public Updateable, public Alarmable, 
	public Inputable, public Collidable, public Align16
{
public:
	GameObject();

	virtual ~GameObject();

	/// \brief Adds the GameObject to the scene
	/// \ingroup REGISTER
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Initialize()
	///		{
	///			GameObject::SubmitEntry();
	///		}
	/// \endcode
	void SubmitEntry();
	/// \brief Removes the GameObject from the scene
	/// \ingroup REGISTER
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Explode()
	///		{
	///			GameObject::SubmitExit();
	///			ExplosionFactory::MakeExplosionHere(pos);
	///		}
	/// \endcode
	void SubmitExit();
	
private:
	bool registeredToScene;

	friend class GameObjAttorneyToEntryCommand;
	friend class GameObjAttorneyToExitCommand;

	void ConnectToScene();
	void DisconnectToScene();

	/// \brief Defined by the user and used to connect the GameObject to the current scene
	/// \ingroup REGISTER
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Updateable::SubmitUpdateRegistration();
	///			Drawable::SubmitDrawRegistration();
	///			Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 10.0f);
	///			Inputable::SubmitKeyRegistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	///			Collidable::CollisionRegistration<SpaceFrigate>(this);
	///		}
	/// \endcode
	virtual void SceneEntry() {};
	/// \brief Defined by the user and used to disconnect the GameObject from the current scene
	/// \ingroup REGISTER
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Updateable::SubmitUpdateDeregistration();
	///			Drawable::SubmitDrawDeregistration();
	///			Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	///			Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	///			Collidable::CollisionDeregistration<SpaceFrigate>(this);
	///		}
	/// \endcode
	virtual void SceneExit() {};

	GameObjectEntryCommand* pRegistrationCmd;
	GameObjectExitCommand* pDeregistrationCmd;
};

#endif