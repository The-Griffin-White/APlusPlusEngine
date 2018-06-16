#include "TerrainManager.h"
#include "Terrain.h"

TerrainManager* TerrainManager::ptrInstance = nullptr;

TerrainManager::~TerrainManager()
{
	DebugMsg::out("Deleted TerrainManager\n");
	this->Delete();
}

void TerrainManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}
void TerrainManager::Delete()
{
	for (auto it = terrMap.begin(); it != terrMap.end(); it++)
	{
		delete it->second;
	}
	terrMap.clear();
}

void TerrainManager::privLoad(std::string refName, Texture* texture, const char* heightmap,
	float len, float maxheight, float ytrans,
	float firstU, float secondU,
	float firstV, float secondV)
{
	Terrain* b = new Terrain;
	b->Initialize(texture, heightmap, len, maxheight, ytrans, firstU, secondU, firstV, secondV);
	terrMap[refName] = b;
}

Terrain* TerrainManager::Get(std::string refName)
{
	return Instance().terrMap[refName];
}