#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>
#include <limits>
#include "SceneAttorneyToCollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

template <typename C> 
class CollidableGroup
{
public:
	using CollidableCollection = std::list<C*>;

private:
	static CollidableGroup<C> *ptrInstance;

	CollidableGroup<C>() 
	{
		pAABB = new CollisionVolumeAABB;
	};
	CollidableGroup<C>(const CollidableGroup<C>&) = delete;
	CollidableGroup<C>& operator=(const CollidableGroup<C>&) = delete;
	~CollidableGroup<C>()
	{
		while (!collection.empty())
		{
			collection.pop_front();
		}
		delete pAABB;
		DebugMsg::out("CollidableGroup deleted\n");
	};

	static CollidableGroup& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new CollidableGroup<C>;
			SceneAttorneyToCollidableGroup<C>::DeleteCmd();
			SceneAttorneyToCollidableGroup<C>::UpdateCmd();
		}
		return *ptrInstance;
	}

	CollidableCollection collection;
	CollisionVolumeAABB* pAABB;

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
	static void Delete()
	{
		delete ptrInstance;
		ptrInstance = nullptr;
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

	/// \brief Updates the CollidableGroup's AABB based on the collidables contained in the group.
	/// \ingroup COL-MANAGE
	static void UpdateAABB() 
	{
		float inf = std::numeric_limits<float>::infinity();

		Vect min = Vect(inf, inf, inf);
		Vect max = Vect(-inf, -inf, -inf);
		const CollisionVolumeBSphere* tmp;

		for (auto const& i : Instance().collection)
		{
			tmp = i->GetCollisionBSphere();
			// Look for min...
			if (min.X() > tmp->GetCenter().X() - tmp->GetRadius())
			{
				min.X() = tmp->GetCenter().X() - tmp->GetRadius();
			}
			if (min.Y() > tmp->GetCenter().Y() - tmp->GetRadius())
			{
				min.Y() = tmp->GetCenter().Y() - tmp->GetRadius();
			}
			if (min.Z() > tmp->GetCenter().Z() - tmp->GetRadius())
			{
				min.Z() = tmp->GetCenter().Z() - tmp->GetRadius();
			}
			// Look for max...
			if (max.X() < tmp->GetCenter().X() + tmp->GetRadius())
			{
				max.X() = tmp->GetCenter().X() + tmp->GetRadius();
			}
			if (max.Y() < tmp->GetCenter().Y() + tmp->GetRadius())
			{
				max.Y() = tmp->GetCenter().Y() + tmp->GetRadius();
			}
			if (max.Z() < tmp->GetCenter().Z() + tmp->GetRadius())
			{
				max.Z() = tmp->GetCenter().Z() + tmp->GetRadius();
			}
		}

		Instance().pAABB->GiveNewMinMax(min, max);
	};

	static const CollisionVolumeAABB* GetCollidableGroupAABB()
	{
		return Instance().pAABB;
	};

};

template <typename C>
CollidableGroup<C>* CollidableGroup<C>::ptrInstance = nullptr;

#endif