#ifndef _SceneAttorneyToCollidableGroup
#define _SceneAttorneyToCollidableGroup

template<typename C>
class SceneAttorneyToCollidableGroup
{
private:
	template<typename C>
	friend class CollidableGroup;

	static void DeleteCmd() { SceneManager::Get()->AddDeleteCommand<C>(); };
	static void UpdateCmd() { SceneManager::Get()->AddUpdateCommand<C>(); };
};

#endif