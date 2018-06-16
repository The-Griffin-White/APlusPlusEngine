// This will load/get texture objects and delete them all when the engine is closed
#ifndef _TextureManager
#define _TextureManager

#include <map>			// Replace later, STL sucks
#include <string>
#include "APPECore.h"

class APlusPlusEngine;
class Texture;

class TextureManager
{
private:
	static TextureManager *ptrInstance;

	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager();

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager;
		return *ptrInstance;
	}

	std::map<const std::string, Texture*> textureMap;
	std::string folderName = "../Assets/Textures/";

	void privDelete();
	Texture* privGet(const std::string key);
	void privLoad(const std::string key, const std::string path);

	friend class TextureManagerAttorneyToEngine;
	/// \brief Loads the texture given a filepath
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the texture when we want to Get() it
	/// \param path filepath used to load the texture
	static void Load(const std::string key, const std::string path) { Instance().privLoad(key, path); };

	/// \brief Used to clear the map of Textures.
	/// \ingroup ASSET-MANAGE
	static void Delete() { Instance().privDelete(); };
	/// \brief Used to delete the Manager and all contents
	/// \ingroup ASSET-MANAGE
	static void Terminate();

public:
	/// \brief Returns the texture corresponding the given key (Crashes if the key leads nowhere...)
	/// \ingroup ASSET-INIT
	///
	/// \param key String key used to find the corresponding Texture
	static Texture* Get(const std::string key) { return Instance().privGet(key); };

};

#endif