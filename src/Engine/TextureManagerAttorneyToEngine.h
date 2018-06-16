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

	static void Delete() { TextureManager::Delete(); };
	static void Terminate() { TextureManager::Terminate(); };
};

#endif