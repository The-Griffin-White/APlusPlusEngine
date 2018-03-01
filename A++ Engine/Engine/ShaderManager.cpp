#include "ShaderManager.h"
#include "AzulCore.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	DebugMsg::out("Deleted ShaderManager\n");
}

void ShaderManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void ShaderManager::privDelete()
{
	for (auto it = shaderMap.begin(); it != shaderMap.end(); it++)
	{
		delete it->second;
	}
	shaderMap.clear();
}
ShaderObject* ShaderManager::privGet(const std::string key)
{
	return shaderMap[key];
}
void ShaderManager::privLoad(const std::string key, const std::string path)
{
	std::string fullPath = folderName + path;
	shaderMap[key] = new ShaderObject(fullPath.c_str());
}