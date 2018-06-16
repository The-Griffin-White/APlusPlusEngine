// This will load/get shader objects and delete them all when the engine is closed
#ifndef _ShaderManager
#define _ShaderManager

#include <map>			// Replace later, STL sucks
#include <string>		// Makes things way easier. Can go back to cstrings when we replace STL

class APlusPlusEngine;
class ShaderBase;
class ShaderColor;
class ShaderColorLight;
class ShaderTexture;
class ShaderTexLight;

enum class Shader_Type
{
	COLOR_NOLIGHT,
	COLOR_LIGHT,
	TEX_NOLIGHT,
	TEX_LIGHT
};

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

	ShaderColor* ColorFlat;
	ShaderColorLight* ColorLight;
	ShaderTexture* TexFlat;
	ShaderTexLight* TexLight;

	void privDelete();
	void privLoad(Shader_Type type);

	friend class ShaderManagerAttorneyToEngine;
	/// \brief Loads the shader given a filepath
	/// \ingroup ASSET-INIT
	///
	/// \param key Key used to find the shader when we want to Get() it
	/// \param path filepath used to load the shader
	static void Load(Shader_Type type) { Instance().privLoad(type); };

	/// \brief Used to clear the map of Shaders.
	/// \ingroup ASSET-MANAGE
	static void Delete() { Instance().privDelete(); };
	/// \brief Used to delete the Manager and all contents
	/// \ingroup ASSET-MANAGE
	static void Terminate();

public:
	static ShaderColor* GetShaderColor();
	static ShaderColorLight* GetShaderColorLight();
	static ShaderTexture* GetShaderTexture();
	static ShaderTexLight* GetShaderTexLight();
};

#endif