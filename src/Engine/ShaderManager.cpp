#include "ShaderManager.h"
#include "APPECore.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager::ShaderManager()
{
	ColorFlat = nullptr;
	ColorLight = nullptr;
	TexFlat = nullptr;
	TexLight = nullptr;
}

ShaderManager::~ShaderManager()
{
//	DebugMsg::out("Deleted ShaderManager\n");
	this->privDelete();
}

void ShaderManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void ShaderManager::privDelete()
{
	delete ColorFlat;
	delete ColorLight;
	delete TexFlat;
	delete TexLight;
}
void ShaderManager::privLoad(Shader_Type type)
{
	switch (type)
	{
	case Shader_Type::COLOR_NOLIGHT:
		if (!ColorFlat)
			ColorFlat = new ShaderColor;
		break;
	case Shader_Type::COLOR_LIGHT:
		if (!ColorLight)
			ColorLight = new ShaderColorLight;
		break;
	case Shader_Type::TEX_NOLIGHT:
		if (!TexFlat)
			TexFlat = new ShaderTexture;
		break;
	case Shader_Type::TEX_LIGHT:
		if (!TexLight)
			TexLight = new ShaderTexLight;
		break;
	}
}

ShaderColor* ShaderManager::GetShaderColor()
{
	return Instance().ColorFlat;
}
ShaderColorLight* ShaderManager::GetShaderColorLight()
{
	return Instance().ColorLight;
}
ShaderTexture* ShaderManager::GetShaderTexture()
{
	return Instance().TexFlat;
}
ShaderTexLight* ShaderManager::GetShaderTexLight()
{
	return Instance().TexLight;
}