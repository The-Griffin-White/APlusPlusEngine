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
	SceneChangeNullCommand* nullCmd;
	SceneChangeNextCommand* nextCmd;

	Scene* privGet();
	void privSetNextScene(Scene* ptrSc);

	Camera* privGetCurrentCamera();

	friend class SceneManagerAttorneyToSceneChange;
	void privSetCurrentScene(Scene* s);
	static void SetCurrentScene(Scene* s) { Instance().privSetCurrentScene(s); };

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

	/// \brief Deletes the manager.
	/// \ingroup SCENE-MANAGE
	static void Terminate();

	/// \brief Called to grab the camera currently used by the current scene
	static Camera* GetCurrentCamera() { return Instance().privGetCurrentCamera(); };

};

#endif