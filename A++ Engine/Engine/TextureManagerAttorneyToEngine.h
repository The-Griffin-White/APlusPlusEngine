#ifndef _TextureManagerAttorneyToEngine
#define _TextureManagerAttorneyToEngine

#include "TextureManager.h"

class TextureManagerAttorneyToEngine
{
private:
	friend class APlusPlusEngine;

	static void Load(const std::string key, const std::string path) 
	{
		TextureManager::Load(key, path);
	};

	static void Load(const std::string key, unsigned char red, unsigned char green, 
						unsigned char blue, unsigned char alpha) 
	{
		TextureManager::Load(key, red, green, blue, alpha);
	};

	static void Load(const std::string key, unsigned char red, unsigned char green, 
						unsigned char blue) 
	{
		TextureManager::Load(key, red, green, blue);
	};

	static void Delete() { TextureManager::Delete(); };
	static void Terminate() { TextureManager::Terminate(); };
};

#endif