#ifndef _TerrainManager
#define _TerrainManager

#include <map>

class Terrain;
class Texture;

class TerrainManager
{
private:
	static TerrainManager *ptrInstance;

	TerrainManager() {};
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	~TerrainManager();

	static TerrainManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TerrainManager;
		return *ptrInstance;
	}

	std::map<std::string, Terrain*> terrMap;

	friend class TerrainManagerAttorneyToEngine;
	static void Terminate();
	void Delete();

	void privLoad(std::string refName, 
		Texture* texture, const char* heightmap,
		float len, float maxheight, float ytrans,
		float firstU, float secondU,
		float firstV, float secondV);

public:
	/// \brief Initialized terrain with given values.
	/// \ingroup TERRAIN
	///
	/// \param referenceName The name used to grab the terrain for later use
	/// \param texture The texture applied to the terrain
	/// \param heightmap The black and white image used to determine the structure of the terrain
	/// \param len The length or width of the terrain
	/// \param maxheight The maximum height of any point on the terrain (your terrain map may not reach this height)
	/// \param ytrans The "Starting height" of the terrain, a terrain with height zero but ytrans of 10 will be at height 10
	/// \param firstU the u value of the top left corner
	/// \param secondU the u value of the bottom right corner
	/// \param firstV the v value of the top left corner
	/// \param secondV the v value of the bottom right corner
	/// \par EXAMPLE
	/// \code
	///	TerrainManagerAttorneyToEngine::Load("ourTerrain", TextureManager::Get("ground"),
	///		"../Assets/Textures/HMtest.tga", 10000, 1000, -8);
	///	TerrainManagerAttorneyToEngine::Load("terrain2", TextureManager::Get("ground"),
	///		"../Assets/Textures/HMtest.tga", 5000, 1000, -8);
	///	TerrainManagerAttorneyToEngine::Load("tankTerrain", TextureManager::Get("ground"),
	///		"../Assets/Textures/HMtest.tga", 10000, 1000, -70);
	/// \endcode
	static void Load(std::string referenceName, 
		Texture* texture, const char* heightmap,
		float len, float maxheight, float ytrans = 0.0f, 
		float firstU = 0.0f, float secondU = 1.0f, 
		float firstV = 0.0f, float secondV = 1.0f) 
	{ 
		return Instance().privLoad
		(
			referenceName, texture, heightmap, len, 
			maxheight, ytrans, firstU, secondU, 
			firstV, secondV
		); 
	};

	static Terrain* Get(std::string referenceName);
};

#endif