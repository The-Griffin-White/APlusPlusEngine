#ifndef _TerrainManagerAttorneyToEngine
#define _TerrainManagerAttorneyToEngine

#include "TerrainManager.h"

class TerrainManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;
	static void Delete() { TerrainManager::Instance().Delete(); };
	static void Terminate() { TerrainManager::Terminate(); };
	static void Load(std::string referenceName,
		Texture* texture, const char* heightmap,
		float len, float maxheight, float ytrans = 0.0f,
		float firstU = 0.0f, float secondU = 1.0f,
		float firstV = 0.0f, float secondV = 1.0f)
	{
		TerrainManager::Load(referenceName, texture, heightmap, len, 
			maxheight, ytrans, firstU, secondU, firstV, secondV);
	};
};

#endif _SpriteFactoryAttorneyToEngine
