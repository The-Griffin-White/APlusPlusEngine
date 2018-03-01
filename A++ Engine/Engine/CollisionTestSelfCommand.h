#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "AzulCore.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionTestSelfCommand : public CollisionTestCommandBase
{
private:
	typename const CollidableGroup<C>::CollidableCollection& col;

public:
	CollisionTestSelfCommand()
		: col(CollidableGroup<C>::GetColliderCollection())
	{};
	~CollisionTestSelfCommand() { DebugMsg::out("CollisionTestSelfCommand deleted\n"); };

	/// \brief Iterates through all instances of registered Collidables and tests for self collision.
	/// \ingroup COL-MANAGE
	virtual void execute()
	{
		for (auto itr = col.begin(); itr != col.end(); itr++)
		{
			if (true)
			{
				(*itr)->Collision();
			}
		}
//		DebugMsg::out("CollisionTestSelfCommand executed\n");
	};

};

#endif