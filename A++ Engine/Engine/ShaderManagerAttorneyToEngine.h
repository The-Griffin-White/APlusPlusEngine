#ifndef _ShaderManagerAttorneyToEngine
#define _ShaderManagerAttorneyToEngine

#include "ShaderManager.h"

class ShaderManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;

	static void Load(const std::string key, const std::string path) 
	{
		ShaderManager::Load(key, path);
	};

	static void Delete() { ShaderManager::Delete(); };
	static void Terminate() { ShaderManager::Terminate(); };
};

#endif