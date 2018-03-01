#ifndef _CollisionManager
#define _CollisionManager

#include <list>
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "DeleteBaseCommand.h"

class CollisionManager
{
public:
	CollisionManager() {};
	~CollisionManager();

	/// \brief Process all the collision pairs.
	/// \ingroup COL-MANAGE
	void ProcessCollisions();

	/// \brief Deletes all the collidable groups.
	/// \ingroup COL-MANAGE
	void DeleteCollidableGroups();

	/// \brief Sets a collision pair (Called from Scene).
	/// \ingroup COL-MANAGE
	template< typename C1, typename C2 >
	void SetCollisionPair()
	{
		colTestCmds.push_front(new CollisionTestPairCommand<C1, C2>());
	};

	/// \brief Sets a collision self (Called from Scene).
	/// \ingroup COL-MANAGE
	template< typename C >
	void SetCollisionSelf()
	{
		colTestCmds.push_front(new CollisionTestSelfCommand<C>());
	};

	/// \brief Adds a command to delete a CollidableGroup (Called from Scene).
	/// \ingroup COL-MANAGE
	void AddDeleteCmd(DeleteBaseCommand* cmd);

private:
	using GroupDelList = std::list<DeleteBaseCommand*>;
	using GroupDelItr = GroupDelList::iterator;
	GroupDelList delList;

	using ColTestList = std::list<CollisionTestCommandBase*>;
	using ColTestItr = ColTestList::iterator;
	ColTestList colTestCmds;

	

};

#endif