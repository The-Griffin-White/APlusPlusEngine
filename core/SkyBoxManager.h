#ifndef _SkyBoxManager
#define _SkyBoxManager

#include <map>
#include <d3d11.h>

class SkyBox_Object;
class Texture;
class ShaderTexLight;

class SkyBoxManager
{
private:
	static SkyBoxManager *ptrInstance;

	SkyBoxManager();
	SkyBoxManager(const SkyBoxManager&) = delete;
	SkyBoxManager& operator=(const SkyBoxManager&) = delete;
	~SkyBoxManager();

	static SkyBoxManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SkyBoxManager;
		return *ptrInstance;
	}

	static float scale;
	static bool skyboxRender;

	std::string folderName = "../Assets/Textures/";

	std::map<const std::string, Texture*> skyboxMap;
	SkyBox_Object* pSkybox;
	Texture* currTex;

	void privInit();
	void privDelete();
	void privLoad(const std::string key, Texture* tex);
	void privLoad(const std::string key, const std::string path);
	void privDraw();

public:
	static void Delete() { Instance().privDelete(); };
	/// \brief Loads a new skybox given a previously defined texture
	/// \ingroup EFFECTS
	///
	/// \param key The key used to grab this skybox later
	/// \param tex The texture to use on the skybox model
	static void Load(const std::string key, Texture* tex) { Instance().privLoad(key, tex); };
	/// \brief Draws the currently selected skybox. Does not need to be called by user
	/// \ingroup EFFECTS
	static void Draw() { Instance().privDraw(); };
	/// \brief Selects the skybox to draw
	/// \ingroup EFFECTS
	///
	/// \param key The key of the skybox we want to draw
	static void Choose(const std::string key);
	static void Terminate();
};

#endif