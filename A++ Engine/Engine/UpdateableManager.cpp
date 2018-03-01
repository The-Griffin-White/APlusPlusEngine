#include "UpdateableManager.h"

#include "UpdateableAttorneyToUpdateableManager.h"

#include "AzulCore.h"

UpdateableManager::~UpdateableManager()
{
	// We should delete the objects somewhere else, so just clear the list
	storageList.clear();
	DebugMsg::out("UpdateableManager deleted\n");
}

UpdateableManager::UpdateableListRef UpdateableManager::Register(Updateable* up)
{
	return storageList.insert(storageList.begin(), up);
}

void UpdateableManager::ProcessElements()
{
	for (auto itr = storageList.begin(); itr != storageList.end(); itr++)
	{
		UpdateableAttorneyToUpdateableManager::Update((*itr));
	}
}

void UpdateableManager::Deregister(Updateable* up)
{
	storageList.remove(up);
}

void UpdateableManager::Deregister(UpdateableListRef itr)
{
	storageList.erase(itr);
}