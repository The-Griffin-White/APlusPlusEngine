#ifndef _ShaderManagerAttorneyToEngine
#define _ShaderManagerAttorneyToEngine

#include "ShaderManager.h"

class ShaderManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;
	friend class SkyBoxManager;

	static void Load(Shader_Type type) 
	{
		ShaderManager::Load(type);
	};

	static void Delete() { ShaderManager::Delete(); };
	static void Terminate() { ShaderManager::Terminate(); };
};

#endif