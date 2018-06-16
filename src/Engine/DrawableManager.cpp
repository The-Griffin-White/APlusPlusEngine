#include "DrawableManager.h"

#include "DrawableAttorneyToDrawableManager.h"

#include "APPECore.h"

DrawableManager::~DrawableManager()
{
	// We should delete the objects somewhere else, so just clear the list
	storageList.clear();
	DebugMsg::out("DrawableManager deleted\n");
}

DrawableManager::DrawableListRef DrawableManager::Register(Drawable* up)
{
	return storageList.insert(storageList.begin(), up);
}

void DrawableManager::ProcessElements()
{
	for (auto itr = storageList.begin(); itr != storageList.end(); itr++)
	{
		DrawableAttorneyToDrawableManager::Draw((*itr));
	}
}

void DrawableManager::Deregister(Drawable* up)
{
	storageList.remove(up);
}

void DrawableManager::Deregister(DrawableListRef itr)
{
	storageList.erase(itr);
}