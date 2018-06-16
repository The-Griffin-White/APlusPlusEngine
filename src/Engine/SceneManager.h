#ifndef _SceneManager
#define _SceneManager

#include "SceneAttorneyToSceneManager.h"

class Scene;
class Camera;

class SceneChangeCommandBase;
class SceneChangeNullCommand;
class SceneChangeNextCommand;

class SceneManager
{
private:
	static SceneManager *ptrInstance;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager();

	static SceneManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SceneManager;
		return *ptrInstance;
	}

	Scene* currScene;
	SceneChangeCommandBase* currCmd;
	SceneChangeCommandBase* swapCmd;
	SceneChangeNullCommand* nullCmd;
	SceneChangeNextCommand* nextCmd;

	Scene* privGet();
	void privSetNextScene(Scene* ptrSc);

	Camera* privGetCurrentCamera();
	Camera* privGet2DCamera();

	friend class SceneManagerAttorneyToSceneChange;
	void privSetCurrentScene(Scene* s);
	void LoadNextScene();
	static void SetCurrentScene(Scene* s) { Instance().privSetCurrentScene(s); };

	friend class SceneManagerAttorneyToEngine;
	/// \brief Deletes the manager.
	/// \ingroup SCENE-MANAGE
	static void Terminate();

public:
	/// \brief Calls update on current Scene and starts the next scene if given one.
	/// \ingroup SCENE-MANAGE
	static void Update();
	/// \brief Calls draw on current Scene
	/// \ingroup SCENE-MANAGE
	static void Draw();
	/// \brief Used to grab the current scene if necessary, avoid GameObjects keeping a Scene pointer.
	/// \ingroup SCENE
	static Scene* Get() { return Instance().privGet(); };

	/// \brief Called to start the next scene
	///
	/// \param ptrSc Pointer to a new Scene that we begin on the next frame. Memory handled in the SceneManager after passing to it
	static void SetNextScene(Scene* ptrSc) { Instance().privSetNextScene(ptrSc); };

	/// \brief Called to grab the camera currently used by the scene's camera manager
	/// \ingroup SCENE
	static Camera* GetCurrentCamera() { return Instance().privGetCurrentCamera(); };
	static Camera* Get2DCamera() { return Instance().privGet2DCamera(); };

	/// \brief Called to grab the terrain currently used in the scene
	/// \ingroup TERRAIN
	///
	/// \param t Output parameter, returns the Terrain
	/// \return A boolean indicating whether the terrain is present or nullptr.
	static bool GetTerrain(Terrain*& t);

	/// \brief Called to grab the terrain currently used in the scene
	/// \ingroup TERRAIN
	///
	/// \param col Collidable we need to get the proper vector
	/// \param n The normal from the terrain
	/// \return The up vector from the terrain
	static bool GetTerrainVector(Collidable* col, Vect& n);

	/// \brief Grabs the height of the point on the terrain directly below the collidable
	/// \ingroup TERRAIN
	///
	/// \param col The collidable
	/// \param y The height from the terrain
	/// \return boolean for whether there is terrain underneath the collidable that we can return a height for
	static bool GetTerrainHeight(Collidable* col, float& y);

	/// \brief Grabs the point on the terrain directly below the collidable
	/// \ingroup TERRAIN
	///
	/// \param col The collidable
	/// \param p The point from the terrain
	/// \return boolean for whether there is terrain underneath the collidable that we can return a point for
	static bool GetTerrainPointBelowCollidable(Collidable* col, Vect& p);

};

#endif