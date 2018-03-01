#include "ModelManager.h"
#include "AzulCore.h"

ModelManager* ModelManager::ptrInstance = nullptr;

std::string ModelManager::UnitSphere = "Sphere";
std::string ModelManager::UnitSquare = "Square";
std::string ModelManager::UnitBox = "Box";

ModelManager::ModelManager()
{
	modelMap.insert({ UnitSphere, new Model(Model::PreMadedeModels::UnitSphere) });
	modelMap.insert({ UnitSquare, new Model(Model::PreMadedeModels::UnitSquareXY) });
	modelMap.insert({ UnitBox, new Model(Model::PreMadedeModels::UnitBox_WF) });
}

ModelManager::~ModelManager()
{
	DebugMsg::out("Deleted ModelManager\n");
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
	std::string fullPath = folderName + path + extensionName;
	modelMap[key] = new Model(fullPath.c_str());
}