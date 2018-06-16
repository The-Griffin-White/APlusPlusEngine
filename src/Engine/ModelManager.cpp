#include "ModelManager.h"
#include "APPECore.h"

#include "APlusPlusEngine.h"

ModelManager* ModelManager::ptrInstance = nullptr;

std::string ModelManager::UnitSphere = "Sphere";
std::string ModelManager::UnitPyramid = "Pyramid";
std::string ModelManager::UnitBox = "Box";
std::string ModelManager::SpriteModel = "Sprite";

ModelManager::ModelManager()
{
	modelMap.insert({ UnitSphere, new Model(Model::PreMadedeModels::UnitSphere) });
	modelMap.insert({ UnitPyramid, new Model(Model::PreMadedeModels::UnitPyramid) });
	modelMap.insert({ UnitBox, new Model(Model::PreMadedeModels::UnitBoxRepeatedTexture) });
	modelMap.insert({ SpriteModel, FlatPlane::getFlatPlaneModel( 
		(8.45f / (float)APlusPlusEngine::GetWindowHeight()) * 0.01f, 
		(11.45f / (float)APlusPlusEngine::GetWindowWidth()) * 0.01f,
		1, 1) });
}

ModelManager::~ModelManager()
{
//	DebugMsg::out("Deleted ModelManager\n");
	this->privDelete();
}

void ModelManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void ModelManager::privDelete()
{
	for (auto it = modelMap.begin(); it != modelMap.end(); it++)
	{
		delete it->second;
	}
	modelMap.clear();
}
Model* ModelManager::privGet(const std::string key)
{
	return modelMap[key];
}
void ModelManager::privLoad(const std::string key, const std::string path)
{
	if (modelMap.find(key) == modelMap.end())
	{
		std::string fullPath = folderName + path + extensionName;
		modelMap[key] = new Model(fullPath.c_str());
	}
}
void ModelManager::privLoad(const std::string key, Model* m)
{
	if (modelMap.find(key) == modelMap.end())
	{
		modelMap[key] = m;
	}
}