// This will load/get texture objects and delete them all when the engine is closed
#ifndef _TextureManager
#define _TextureManager

#include <map>			// Replace later, STL sucks
#include <string>
#include "AzulCore.h"

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
	std::string folderName = "Textures/";

	void privDelete();
	Texture* privGet(const std::string key);
	void privLoad(const std::string key, const std::string path);
	void privLoad(const std::string key, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	void privLoad(const std::string key, unsigned char red, unsigned char green, unsigned char blue);

	friend class TextureManagerAttorneyToEngine;
	/// \brief Loads the texture given a filepath
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the texture when we want to Get() it
	/// \param path filepath used to load the texture
	static void Load(const std::string key, const std::string path) { Instance().privLoad(key, path); };
	/// \brief Loads the texture given color and alpha paramaters
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the texture when we want to Get() it
	/// \param red Red value for the texture
	/// \param green Green value for the texture
	/// \param blue Blue value for the texture
	/// \param alpha Alpha value for the texture
	static void Load(const std::string key, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) { Instance().privLoad(key, red, green, blue, alpha); };
	/// \brief Loads the texture given color paramaters
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the texture when we want to Get() it
	/// \param red Red value for the texture
	/// \param green Green value for the texture
	/// \param blue Blue value for the texture
	static void Load(const std::string key, unsigned char red, unsigned char green, unsigned char blue) { Instance().privLoad(key, red, green, blue); };

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