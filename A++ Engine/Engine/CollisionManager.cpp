#include "CollisionManager.h"
#include "CollidableGroupDeleteCommand.h"

CollisionManager::~CollisionManager()
{
	this->DeleteCollidableGroups();
	while (!colTestCmds.empty()) 
	{
		delete colTestCmds.front();
		colTestCmds.pop_front();
	}
	DebugMsg::out("CollisionManager deleted\n");
}

void CollisionManager::AddDeleteCmd(DeleteBaseCommand* cmd)
{
	delList.push_front(cmd);
}

void CollisionManager::ProcessCollisions()
{	
	for (ColTestItr itr = colTestCmds.begin(); itr != colTestCmds.end(); ++itr)
	{
		(*itr)->execute();
	}
}

void CollisionManager::DeleteCollidableGroups()
{
	while (!delList.empty())
	{
		delList.front()->execute();
		delete delList.front();
		delList.pop_front();
	}
}