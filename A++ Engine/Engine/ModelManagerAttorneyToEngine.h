#ifndef _ModelManagerAttorneyToEngine
#define _ModelManagerAttorneyToEngine

#include "ModelManager.h"

class ModelManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;

	static void Load(const std::string key, const std::string path)
	{
		ModelManager::Load(key, path);
	};

	static void Delete() { ModelManager::Delete(); };
	static void Terminate() { ModelManager::Terminate(); };
};

#endif