#include "TextureManager.h"
#include "AzulCore.h"

TextureManager* TextureManager::ptrInstance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	DebugMsg::out("Deleted TextureManager\n");
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
	std::string fullPath = folderName + path;
	textureMap[key] = new Texture(fullPath.c_str());
}
void TextureManager::privLoad(const std::string key, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	textureMap[key] = new Texture(red, green, blue, alpha);
}
void TextureManager::privLoad(const std::string key, unsigned char red, unsigned char green, unsigned char blue)
{
	textureMap[key] = new Texture(red, green, blue);
}