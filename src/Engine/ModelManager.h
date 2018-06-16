// This will load/get model objects and delete them all when the engine is closed
#ifndef _ModelManager
#define _ModelManager

#include <map>			// Replace later, STL sucks
#include <string>

class APlusPlusEngine;
class Model;

class ModelManager
{
private:
	static ModelManager *ptrInstance;

	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager();

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager;
		return *ptrInstance;
	}

	std::map<const std::string, Model*> modelMap;
	std::string folderName = "../Assets/Models/";
	std::string extensionName = ".azul";

	void privDelete();
	Model* privGet(const std::string key);
	void privLoad(const std::string key, const std::string path);
	void privLoad(const std::string key, Model* m);

	friend class ModelManagerAttorneyToEngine;
	/// \brief Loads the model given a filepath
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the model when we want to Get() it
	/// \param path filepath used to load the model
	static void Load(const std::string key, const std::string path) { Instance().privLoad(key, path); };
	/// \brief Loads the model given a previously created model
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the model when we want to Get() it
	/// \param m The model being added to the manager
	static void Load(const std::string key, Model* m) { Instance().privLoad(key, m); };

	/// \brief Used to clear the map of Models.
	/// \ingroup ASSET-MANAGE
	static void Delete() { Instance().privDelete(); };
	/// \brief Used to delete the Manager and all contents
	/// \ingroup ASSET-MANAGE
	static void Terminate();

	static std::string UnitSphere;
	static std::string UnitPyramid;
	static std::string UnitBox;
	static std::string SpriteModel;

public:
	/// \brief Returns the model corresponding the given key (Crashes if the key leads nowhere...)
	/// \ingroup ASSET-INIT
	///
	/// \param key String key used to find the corresponding Model
	/**
	  Default Models, use private static variables:
	  "Sphere" is a sphere
	  "Pyramid" is a pyramid
	  "Box" is a box
	**/
	static Model* Get(const std::string key) { return Instance().privGet(key); };

};

#endif