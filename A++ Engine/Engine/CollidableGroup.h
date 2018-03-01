#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>
#include "SceneAttorneyToCollidableGroup.h"

template <typename C> 
class CollidableGroup
{
public:
	using CollidableCollection = std::list<C*>;

private:
	static CollidableGroup<C> *ptrInstance;

	CollidableGroup<C>() {};
	CollidableGroup<C>(const CollidableGroup<C>&) = delete;
	CollidableGroup<C>& operator=(const CollidableGroup<C>&) = delete;
	~CollidableGroup<C>() {};

	static CollidableGroup& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new CollidableGroup<C>;
			SceneAttorneyToCollidableGroup<C>::DeleteCmd();
//			SceneManager::Get()->AddDeleteCommand<C>();
		}
		return *ptrInstance;
	}

	CollidableCollection collection;

	void privRegister(C* p)
	{
		DebugMsg::out("Registered to CollidableGroup\n");
		collection.push_back(p);
	};
	void privDeregister(C* p)
	{
		DebugMsg::out("Deregistered from CollidableGroup\n");
		collection.remove(p);
	};

public:
	static CollidableGroup<C>* GetPointer() { return &Instance(); };

	/// \brief Clears the collection of registed collidables in this group.
	/// \ingroup COL-MANAGE
	void Delete()
	{
		while (!collection.empty())
		{
			collection.pop_front();
		}
		DebugMsg::out("CollidableGroup deleted\n");
	};

	/// \brief Returns the list of Collidables registered to this group.
	/// \ingroup COL-MANAGE
	static const CollidableCollection& GetColliderCollection() { return Instance().collection; };
	/// \brief Registers a new instance of Collidable type C.
	/// \ingroup COL-MANAGE
	/// \param p Instance of a collidable
	static void Register(C* p) { Instance().privRegister(p); };
	/// \brief Deregisters this instance of Collidable type C.
	/// \ingroup COL-MANAGE
	/// \param p Instance of a collidable
	static void Deregister(C* p) { Instance().privDeregister(p); };

};

template <typename C>
CollidableGroup<C>* CollidableGroup<C>::ptrInstance = nullptr;

#endif