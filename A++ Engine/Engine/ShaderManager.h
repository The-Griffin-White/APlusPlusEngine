// This will load/get shader objects and delete them all when the engine is closed
#ifndef _ShaderManager
#define _ShaderManager

#include <map>			// Replace later, STL sucks
#include <string>		// Makes things way easier. Can go back to cstrings when we replace STL

class APlusPlusEngine;
class ShaderObject;

class ShaderManager
{
private:
	static ShaderManager *ptrInstance;

	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager();

	static ShaderManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager;
		return *ptrInstance;
	}

	std::map<const std::string, ShaderObject*> shaderMap;
	std::string folderName = "Shaders/";

	void privDelete();
	ShaderObject* privGet(const std::string key);
	void privLoad(const std::string key, const std::string path);

	friend class ShaderManagerAttorneyToEngine;
	/// \brief Loads the shader given a filepath
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the shader when we want to Get() it
	/// \param path filepath used to load the shader
	static void Load(const std::string key, const std::string path) { Instance().privLoad(key, path); };

	/// \brief Used to clear the map of Shaders.
	/// \ingroup ASSET-MANAGE
	static void Delete() { Instance().privDelete(); };
	/// \brief Used to delete the Manager and all contents
	/// \ingroup ASSET-MANAGE
	static void Terminate();

public:
	/// \brief Returns the shader corresponding the given key (Crashes if the key leads nowhere...)
	/// \ingroup ASSET-INIT
	///
	/// \param key String key used to find the corresponding Shader
	static ShaderObject* Get(const std::string key) { return Instance().privGet(key); };

};

#endif