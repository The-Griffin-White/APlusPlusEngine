#include "SkyBoxManager.h"
#include "SkyBox_Object.h"
#include "Texture.h"
#include "d3dUtil.h"
#include "ShaderTexLight.h"

#include "ShaderManager.h"
#include "ShaderManagerAttorneyToEngine.h"

#include "SFXManager.h"

SkyBoxManager* SkyBoxManager::ptrInstance = nullptr;
float SkyBoxManager::scale = 5000.0f;
bool SkyBoxManager::skyboxRender = false;


SkyBoxManager::SkyBoxManager()
{
	pSkybox = nullptr;
	currTex = nullptr;
	this->privInit();
}

SkyBoxManager::~SkyBoxManager()
{
	this->privDelete();
	delete pSkybox;
	currTex = nullptr;
}

void SkyBoxManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void SkyBoxManager::privInit()
{
	ShaderTexLight* pShader = ShaderManager::GetShaderTexLight();
	if (!pShader)
	{
		ShaderManagerAttorneyToEngine::Load(Shader_Type::TEX_LIGHT);
	}
	pShader = ShaderManager::GetShaderTexLight();
	pSkybox = new SkyBox_Object(scale, pShader);
	pSkybox->SetWorld(Matrix(TRANS, 0, 200, 0));
	pSkybox->SetMaterial(Colors::LightBlue, 1 * Colors::LightBlue, Vect(1, 1, 1, 100));
}
void SkyBoxManager::privDelete()
{	
	// we dont own these textures, so dont delete here
	skyboxMap.clear();
	skyboxRender = false;
}
void SkyBoxManager::privLoad(const std::string key, const std::string path)
{
	if (skyboxMap.find(key) == skyboxMap.end())
	{
		std::string fullPath = folderName + path;
		skyboxMap[key] = new Texture(fullPath.c_str());
	}
}
void SkyBoxManager::privLoad(const std::string key, Texture* tex)
{
	if (skyboxMap.find(key) == skyboxMap.end())
		skyboxMap[key] = tex;
}
void SkyBoxManager::privDraw()
{
	if (skyboxRender)
	{
		SFXManager::SetDisableFog();
		this->pSkybox->Render();
		SFXManager::ResetFogParameters();
	}
}

void SkyBoxManager::Choose(const std::string key)
{
	Instance().currTex = Instance().skyboxMap[key];
	Instance().pSkybox->SetTexture(Instance().currTex);
	skyboxRender = true;
}