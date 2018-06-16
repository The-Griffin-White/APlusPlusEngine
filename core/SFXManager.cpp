#include "SFXManager.h"
#include "ShaderBase.h"

#include <assert.h>

SFXManager* SFXManager::ptrInstance = nullptr;

SFXManager::SFXManager()
{
	numPointLights = 0;
	numSpotLights = 0;
}


SFXManager::~SFXManager()
{
	shaderList.clear();
}

void SFXManager::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void SFXManager::privSetFogParameters(const float& fogstart, const float& fogrange, const Vect& fogcolor)
{
	fogStart = fogstart;
	fogRange = fogrange;
	fogColor = fogcolor;
	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->SetFogParameters(fogstart, fogrange, fogcolor);
	}
}
void SFXManager::privResetFogParameters()
{
	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->SetFogParameters(fogStart, fogRange, fogColor);
	}
}
void SFXManager::privSetDisableFog()
{
	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->SetDisableFog();
	}
}
void SFXManager::AddShader(ShaderBase* s)
{
	Instance().shaderList.push_back(s);
}

void SFXManager::privChangeDirectionalLighting(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Direction = dir;
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->ChangeDirectionalLighting();
	}
}
void SFXManager::privChangePointLighting(int n, const Vect& pos, float r, const Vect& att,
	const Vect& amb, const Vect& dif, const Vect& sp)
{
	if (n >= 0 && n < POINTARRAY_SIZE)
	{
		PointLightData[n].Position = pos;
		PointLightData[n].Range = r;
		PointLightData[n].Attenuation = att;
		PointLightData[n].Light.Ambient = amb;
		PointLightData[n].Light.Diffuse = dif;
		PointLightData[n].Light.Specular = sp;

		for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
		{
			(*itr)->ChangePointLighting(n);
		}
	}
}
void SFXManager::privChangeSpotLighting(int n, const Vect& pos, float r, const Vect& att,
	const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	if (n >= 0 && n < SPOTARRAY_SIZE)
	{
		SpotLightData[n].Direction = dir;
		SpotLightData[n].SpotExp = spotExp;
		SpotLightData[n].Position = pos;
		SpotLightData[n].Range = r;
		SpotLightData[n].Attenuation = att;
		SpotLightData[n].Light.Ambient = amb;
		SpotLightData[n].Light.Diffuse = dif;
		SpotLightData[n].Light.Specular = sp;

		for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
		{
			(*itr)->ChangeSpotLighting(n);
		}
	}
}

void SFXManager::privDeactivatePointLight(int n)
{
	if (n >= 0 && n < SPOTARRAY_SIZE)
	{
		PointLightData[n].Position = Vect(0, 0, 0);
		PointLightData[n].Range = 0;
		PointLightData[n].Attenuation = Vect(0, 0, 0);
		PointLightData[n].Light.Ambient = Vect(0, 0, 0);
		PointLightData[n].Light.Diffuse = Vect(0, 0, 0);
		PointLightData[n].Light.Specular = Vect(0, 0, 0);

		for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
		{
			(*itr)->ChangePointLighting(n);
		}
	}
}

void SFXManager::privDeactivateSpotLight(int n)
{
	if (n >= 0 && n < SPOTARRAY_SIZE)
	{
		SpotLightData[n].Direction = Vect(0, 0, 0);
		SpotLightData[n].SpotExp = 0;
		SpotLightData[n].Position = Vect(0, 0, 0);
		SpotLightData[n].Range = 0;
		SpotLightData[n].Attenuation = Vect(0, 0, 0);
		SpotLightData[n].Light.Ambient = Vect(0, 0, 0);
		SpotLightData[n].Light.Diffuse = Vect(0, 0, 0);
		SpotLightData[n].Light.Specular = Vect(0, 0, 0);

		for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
		{
			(*itr)->ChangeSpotLighting(n);
		}
	}
}

int SFXManager::privAssignPointLighting(const Vect& pos, float r, const Vect& att,
	const Vect& amb, const Vect& dif, const Vect& sp)
{
	int n = numPointLights;
	++numPointLights;
	if (numPointLights >= POINTARRAY_SIZE)
	{
		numPointLights = 0;
	}

	PointLightData[n].Position = pos;
	PointLightData[n].Range = r;
	PointLightData[n].Attenuation = att;
	PointLightData[n].Light.Ambient = amb;
	PointLightData[n].Light.Diffuse = dif;
	PointLightData[n].Light.Specular = sp;

	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->ChangePointLighting(n);
	}

	return n;
}
int SFXManager::privAssignSpotLighting(const Vect& pos, float r, const Vect& att,
	const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	int n = numSpotLights;
	++numSpotLights;
	if (numSpotLights >= POINTARRAY_SIZE)
	{
		numSpotLights = 0;
	}

	SpotLightData[n].Direction = dir;
	SpotLightData[n].SpotExp = spotExp;
	SpotLightData[n].Position = pos;
	SpotLightData[n].Range = r;
	SpotLightData[n].Attenuation = att;
	SpotLightData[n].Light.Ambient = amb;
	SpotLightData[n].Light.Diffuse = dif;
	SpotLightData[n].Light.Specular = sp;

	for (auto itr = shaderList.begin(); itr != shaderList.end(); itr++)
	{
		(*itr)->ChangeSpotLighting(n);
	}

	return n;
}

DirectionalLight SFXManager::privGetDirectionalLighting()
{
	return DirLightData;
}
PointLight SFXManager::privGetPointLighting(int n)
{
	if (n >= 0 && n <= POINTARRAY_SIZE)
	{
		return PointLightData[n];
	}
	assert(false && "Point light number is out of bounds " && n);
	return PointLightData[0];
}
SpotLight SFXManager::privGetSpotLighting(int n)
{
	if (n >= 0 && n <= SPOTARRAY_SIZE)
	{
		return SpotLightData[n];
	}
	assert(false && "Spot light number is out of bounds " && n);
	return SpotLightData[0];
}