#include "TextureManager.h"
#include "APPECore.h"

#include <assert.h>

TextureManager* TextureManager::ptrInstance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
//	DebugMsg::out("Deleted TextureManager\n");
	this->privDelete();
}

void TextureManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void TextureManager::privDelete()
{
	for (auto it = textureMap.begin(); it != textureMap.end(); it++)
	{
		delete it->second;
	}
	textureMap.clear();
}
Texture* TextureManager::privGet(const std::string key)
{
	return textureMap[key];
}
void TextureManager::privLoad(const std::string key, const std::string path)
{
	if (textureMap.find(key) == textureMap.end())
	{
		std::string fullPath = folderName + path;
		textureMap[key] = new Texture(fullPath.c_str());
	}
}