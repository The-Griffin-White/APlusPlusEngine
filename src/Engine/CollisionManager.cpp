#include "CollisionManager.h"
#include "CollidableGroupDeleteCommand.h"
#include "CollidableGroupUpdateCommand.h"

CollisionManager::~CollisionManager()
{
	this->DeleteCollidableGroups();
	while (!upList.empty())
	{
		delete upList.front();
		upList.pop_front();
	}
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

void CollisionManager::AddUpdateCmd(CommandBase* cmd)
{
	upList.push_front(cmd);
}

void CollisionManager::ProcessCollisions()
{	
	for (GroupUpItr itr = upList.begin(); itr != upList.end(); ++itr)
	{
		(*itr)->execute();
	}

	for (ColTestItr itr = colTestCmds.begin(); itr != colTestCmds.end(); ++itr)
	{
		(*itr)->execute();
	}
}

void CollisionManager::DeleteCollidableGroups()
{
	for (const auto& i : delList)
	{
		i->execute();
		delete i;
	}
	delList.clear();
}