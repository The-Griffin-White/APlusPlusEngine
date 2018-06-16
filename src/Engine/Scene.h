#ifndef _Scene
#define _Scene

#include <malloc.h>
#include "Align16.h"
#include "APPECore.h"

#include "CollisionManager.h"
#include "CollidableGroupDeleteCommand.h"
#include "CollidableGroupUpdateCommand.h"

#include "UpdateableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "SpriteManager.h"
#include "Inputable.h"

class Camera;
class CameraManager;

class SceneRegistrationBroker;
class SceneRegistrationCommand;

class DeleteBaseCommand;
class Terrain;

class Scene : public Align16
{
public:
	Scene();
	virtual ~Scene();

private:
	friend class SceneAttorneyToSceneManager;
	void preInitialize();

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

	/// \brief Defined by the user, used for any cleanup to be done before the Scene is deleted during scene change
	/// \ingroup SCENE
	///
	/// \par EXAMPLE
	///		\code
	///		void ExampleScene::SceneEnd()
	///		{
	///			EnemyFactory::RecallEnemies();
	///		}
	///		\endcode
	virtual void SceneEnd() {};

	friend class SceneAttorneyToUpdateable;
	friend class SceneAttorneyToDrawable;
	friend class SceneAttorneyToAlarmable;
	friend class SceneAttorneyToInputable;
	friend class SceneAttorneyToGameObject;
	friend class SceneAttorneyToCollidable;
	friend class SceneAttorneyToSprite;

	/// \brief Registers this Sprite to the SpriteManager.
	/// \ingroup SCENE-REGISTER
	/// \param s Pointer to the Sprite being registered.
	/// \return Iterator used for reference when we deregister.
	/// \ref SPRITE-MANAGE
	SpriteManager::SpriteListRef AddSprite(Sprite* s);
	/// \brief Deregisters this Sprite from the SpriteManager.
	/// \ingroup SCENE-REGISTER
	/// \param p Iterator used to deregister quickly.
	/// \ref SPRITE-MANAGE
	void RemoveSprite(SpriteManager::SpriteListRef p);

	template<typename C>
	friend class SceneAttorneyToCollidableGroup;

	SceneRegistrationBroker* regBrkr;
	DrawableManager* drawMgr;
	UpdateableManager* updateMgr;
	AlarmableManager* alarmMgr;
	CameraManager* cameraMgr;
	KeyboardEventManager* kbMgr;
	CollisionManager* colMgr;
	SpriteManager* sprMgr;

	/// \brief Registers this Updateable to the UpdateableManager.
	/// \ingroup SCENE-REGISTER
	/// \param up Pointer to the Updateable being registered.
	/// \return Iterator used for reference when we deregister.
	/// \ref UPDATE-MANAGE
	UpdateableManager::UpdateableListRef RegisterUpdateable(Updateable* up);
	/// \brief Deregisters this Updateable from the UpdateableManager.
	/// \ingroup SCENE-REGISTER
	/// \param itr Iterator used to deregister quickly.
	/// \ref UPDATE-MANAGE
	void DeregisterUpdateable(UpdateableManager::UpdateableListRef itr);

	/// \brief Registers this Drawable to the DrawableManager.
	/// \ingroup SCENE-REGISTER
	/// \param dr Pointer to the Drawable being registered.
	/// \return Iterator used for reference when we deregister.
	/// \ref DRAW-MANAGE
	DrawableManager::DrawableListRef RegisterDrawable(Drawable* dr);
	/// \brief Deregisters this Drawable from the DrawableManager.
	/// \ingroup SCENE-REGISTER
	/// \param itr Iterator used to deregister quickly.
	/// \ref DRAW-MANAGE
	void DeregisterDrawable(DrawableManager::DrawableListRef itr);

	/// \brief Registers this Alarmable to the AlarmableManager.
	/// \ingroup SCENE-REGISTER
	/// \param al Pointer to the Alarmable being registered.
	/// \param id Type of Alarm being registered.
	/// \param t Time when the alarm will go off.
	/// \return Iterator used for reference when we deregister.
	/// \ref ALARM-MANAGE
	AlarmableManager::TimelineRef RegisterAlarmable(Alarmable* al, AlarmableManager::ALARM_ID id, float t);
	/// \brief Deregisters this Alarmable from the AlarmableManager.
	/// \ingroup SCENE-REGISTER
	/// \param itr Iterator used to deregister quickly.
	/// \ref ALARM-MANAGE
	void DeregisterAlarmable(AlarmableManager::TimelineRef itr);

	/// \brief Registers this key to be Inputable.
	/// \ingroup SCENE-REGISTER
	/// \param in Pointer to the Inputable being registered.
	/// \param k Type of key being registered.
	/// \param e Type of Key event we are looking for.
	/// \ref INPUT-MANAGE
	KeyboardEventManager::KeyMgrRef RegisterInputable(Inputable* in, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);
	/// \brief Deregisters this key from the Inputable system.
	/// \ingroup SCENE-REGISTER
	/// \param Pointer to the Inputable being registered.
	/// \param Type of key being registered.
	/// \param Type of Key event we are looking for.
	/// \ref INPUT-MANAGE
	void DeregisterInputable(Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);

	/// \brief Adds a command to delete CollidableGroup of type C to the Collision Manager.
	/// \ingroup COL-MANAGE
	/// \tparam C Type of CollidableGroup being deleted.
	template<typename C>
	void AddDeleteCommand()
	{
		colMgr->AddDeleteCmd(new CollidableGroupDeleteCommand<C>());
	};

	/// \brief Adds a command to update CollidableGroup of type C to the Collision Manager.
	/// \ingroup COL-MANAGE
	/// \tparam C Type of CollidableGroup being updated.
	template<typename C>
	void AddUpdateCommand()
	{
		colMgr->AddUpdateCmd(new CollidableGroupUpdateCommand<C>());
	};

	/// \brief Sends a command created elsewhere to the Registration Broker.
	/// \ingroup SCENE-REGISTER
	void SubmitCommand(SceneRegistrationCommand* c);
	
	/// \brief Grabs the current terrain
	/// \ingroup TERRAIN
	///
	/// \param t Return parameter (will reference the current terrain)
	/// \return true if there is a current terrain, false if it is nullptr
	bool GetTerrain(Terrain*& t);

	/// \brief Grabs the up-vector of the point on the terrain directly below the collidable
	/// \ingroup TERRAIN
	///
	/// \param col The collidable
	/// \param up The normal from the terrain
	/// \return boolean for whether there is terrain underneath the collidable that we can return a normal for
	bool GetTerrainVector(Collidable* col, Vect& up);

	/// \brief Grabs the height of the point on the terrain directly below the collidable
	/// \ingroup TERRAIN
	///
	/// \param col The collidable
	/// \param y The height from the terrain
	/// \return boolean for whether there is terrain underneath the collidable that we can return a height for
	bool GetTerrainHeight(Collidable* col, float& y);

	/// \brief Grabs the point on the terrain directly below the collidable
	/// \ingroup TERRAIN
	///
	/// \param col The collidable
	/// \param p The point from the terrain
	/// \return boolean for whether there is terrain underneath the collidable that we can return a point for
	bool GetTerrainPointBelowCollidable(Collidable* col, Vect& p);

	Terrain * currTerrain;
protected:
	/// \brief Called to Register a previously loaded Terrain into the scene
	/// \ingroup TERRAIN
	///
	/// \param terrName Name of the terrain asset (Previously loaded in LoadAllResources.cpp)
	void SetTerrain(std::string terrName);

	/// \brief Called to change the lighting material of the current terrain
	/// \ingroup TERRAIN
	///
	/// \param terrName Name of the terrain asset (Previously loaded in LoadAllResources.cpp)
	void SetTerrainMaterial(const Vect ambient, const Vect diffuse, const Vect specular);

	/// \brief Called in Scene to register an object to collide with Terrain
	/// \ingroup SCENE
	///
	/// \tparam C The object type we want to collide with terrain
	/// \par Note that this will only make GameObjects collide with terrain, not move along it. Used as such:
	///	SetCollisionTerrain<PlayerBomb>();
	template<typename C>
	void SetCollisionTerrain()
	{
		colMgr->SetCollisionTerrain<C>();
	}

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


	Camera* Get2DCamera();
	/// \brief Used to grab the current camera in the camera manager. Called by SceneManager to avoid GameObjects having a Scene pointer.
	/// \ingroup SCENE-MANAGE
	Camera* GetCurrentCamera();
	/// \brief Used to update registered GameObjects through their appropriate managers, as well as call other managers.
	/// \ingroup SCENE-MANAGE
	virtual void UpdateObjects();
	/// \brief Used to Draw registered GameObjects through their appropriate managers.
	/// \ingroup SCENE-MANAGE
	virtual void DrawObjects();
	/// \brief Defined by user, used for anything the scene itself needs to update every frame. GameObject updates are called by the engine
	/// \ingroup SCENE
	virtual void Update() {};
	/// \brief Defined by user, used for anything the scene itself needs to draw every frame. GameObject draws are called by the engine
	/// \ingroup SCENE
	virtual void Draw() {};
};

#endif