#ifndef _Scene
#define _Scene

#include "CollisionManager.h"
#include "CollidableGroupDeleteCommand.h"

#include "UpdateableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "Inputable.h"

class GameObject;
class Camera;

class CameraManager;

class SceneRegistrationBroker;
class SceneRegistrationCommand;

class DeleteBaseCommand;

class Scene
{
public:
	Scene();
	virtual ~Scene();

private:
	friend class SceneAttorneyToSceneManager;
	/// \brief Defined by the user, used to place GameObjects into Scene and anything else needed to start the scene
	/// \ingroup SCENE
	///
	/// \par EXAMPLE
	///		\code
	///		void ExampleScene::Initialize()
	///		{
	///			player = new PlayerObject;
	///			player->Initialize();
	///			player->SubmitEntry();
	///		}
	///		\endcode
	virtual void Initialize() {};

	friend class SceneAttorneyToUpdateable;
	friend class SceneAttorneyToDrawable;
	friend class SceneAttorneyToAlarmable;
	friend class SceneAttorneyToInputable;
	friend class SceneAttorneyToGameObject;
	friend class SceneAttorneyToCollidable;

	template<typename C>
	friend class SceneAttorneyToCollidableGroup;
	
	SceneRegistrationBroker* regBrkr;
	DrawableManager* drawMgr;
	UpdateableManager* updateMgr;
	AlarmableManager* alarmMgr;
	CameraManager* cameraMgr;
	KeyboardEventManager* kbMgr;
	CollisionManager* colMgr;

	/// \brief Registers this Updateable to the UpdateableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Updateable being registered.
	/// \return Iterator used for reference when we deregister.
	/// \ref UPDATE-MANAGE
	UpdateableManager::UpdateableListRef RegisterUpdateable(Updateable* up);
	/// \brief Deregisters this Updateable from the UpdateableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Iterator used to deregister quickly.
	/// \ref UPDATE-MANAGE
	void DeregisterUpdateable(UpdateableManager::UpdateableListRef itr);

	/// \brief Registers this Drawable to the DrawableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Drawable being registered.
	/// \return Iterator used for reference when we deregister.
	/// \ref DRAW-MANAGE
	DrawableManager::DrawableListRef RegisterDrawable(Drawable* dr);
	/// \brief Deregisters this Drawable from the DrawableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Iterator used to deregister quickly.
	/// \ref DRAW-MANAGE
	void DeregisterDrawable(DrawableManager::DrawableListRef itr);

	/// \brief Registers this Alarmable to the AlarmableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Alarmable being registered.
	/// \param Type of Alarm being registered.
	/// \param Time when the alarm will go off.
	/// \return Iterator used for reference when we deregister.
	/// \ref ALARM-MANAGE
	AlarmableManager::TimelineRef RegisterAlarmable(Alarmable* dr, AlarmableManager::ALARM_ID id, float t);
	/// \brief Deregisters this Alarmable from the AlarmableManager.
	/// \ingroup SCENE-REGISTER
	/// \param Iterator used to deregister quickly.
	/// \ref ALARM-MANAGE
	void DeregisterAlarmable(AlarmableManager::TimelineRef itr);

	/// \brief Registers this key to be Inputable.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Inputable being registered.
	/// \param Type of key being registered.
	/// \param Type of Key event we are looking for.
	/// \ref INPUT-MANAGE
	void RegisterInputable(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e);
	/// \brief Deregisters this key from the Inputable system.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Inputable being registered.
	/// \param Type of key being registered.
	/// \param Type of Key event we are looking for.
	/// \ref INPUT-MANAGE
	void DeregisterInputable(Inputable* in, AZUL_KEY k, Inputable::INPUT_EVENT_TYPE e);

	/// \brief Adds a command to delete CollidableGroup of type C to the Collision Manager.
	/// \ingroup COL-MANAGE
	/// \tparam C Type of CollidableGroup being deleted.
	template<typename C>
	void AddDeleteCommand()
	{
		colMgr->AddDeleteCmd(new CollidableGroupDeleteCommand<C>());
	};

	/// \brief Sends a command created elsewhere to the Registration Broker.
	/// \ingroup SCENE-REGISTER
	void SubmitCommand(SceneRegistrationCommand* c);

protected:
	/// \brief Called in Scene to register a pair for collision.
	/// \ingroup SCENE
	///
	/// \tparam C1 The first type of GameObject in our collision pair
	/// \tparam C1 The second type of GameObject in our collision pair
	/// \par Used as such:
	///	SetCollisionPair<PlayerBomb, EnemyShip>();
	template< typename C1, typename C2 >
	void SetCollisionPair()
	{
		colMgr->SetCollisionPair<C1, C2>();
	};

	/// \brief Called in Scene to register a single type for collision.
	/// \ingroup SCENE
	///
	/// \tparam C The type of GameObject to collide
	/// \par Used as such:
	///	SetCollisionPair<PlayerBomb>();
	template< typename C >
	void SetCollisionSelf()
	{
		colMgr->SetCollisionSelf<C>();
	};

	/// \brief Used to grab the current camera in the camera manager. Called by SceneManager to avoid GameObjects having a Scene pointer.
	/// \ingroup SCENE-MANAGE
	Camera* GetCurrentCamera();
	/// \brief Used to update registered GameObjects through their appropriate managers, as well as call other managers.
	/// \ingroup SCENE-MANAGE
	void UpdateObjects();
	/// \brief Used to Draw registered GameObjects through their appropriate managers.
	/// \ingroup SCENE-MANAGE
	void DrawObjects();
	/// \brief Defined by user, used for anything the scene itself needs to update every frame. GameObject updates are called by the engine
	/// \ingroup SCENE
	virtual void Update() {};
	/// \brief Defined by user, used for anything the scene itself needs to draw every frame. GameObject draws are called by the engine
	/// \ingroup SCENE
	virtual void Draw() {};
};

#endif