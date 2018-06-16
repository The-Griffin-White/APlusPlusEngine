#include "APPECore.h"
#include "APlusPlusEngine.h"

#include "ModelManagerAttorneyToEngine.h"
#include "TextureManagerAttorneyToEngine.h"
#include "ShaderManagerAttorneyToEngine.h"
#include "TerrainManagerAttorneyToEngine.h"
#include "SkyBoxManager.h"

#include "../User/PlaneBase.h"

void APlusPlusEngine::LoadAllResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------
	ModelManagerAttorneyToEngine::Load("Ambulance", "Ambulance");
	ModelManagerAttorneyToEngine::Load("Cottage", "Cottage");
	ModelManagerAttorneyToEngine::Load("Axis", "Axis");
	ModelManagerAttorneyToEngine::Load("space_frigate", "space_frigate");
	ModelManagerAttorneyToEngine::Load("Body", "t99body");
	ModelManagerAttorneyToEngine::Load("Turret", "t99turret");

	ModelManagerAttorneyToEngine::Load("Plane",
		FlatPlane::getFlatPlaneModel(PlaneBase::scale, PlaneBase::scale, 1, 1));

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------
	TextureManagerAttorneyToEngine::Load("Ambulance", "AmbulanceTex.tga");
	TextureManagerAttorneyToEngine::Load("Brick", "brick.tga");

	TextureManagerAttorneyToEngine::Load("CottageTex1", "brick-wall.tga");
	TextureManagerAttorneyToEngine::Load("CottageTex2", "Rooftexture.tga");
	TextureManagerAttorneyToEngine::Load("CottageTex3", "Cabintexture.tga");
	TextureManagerAttorneyToEngine::Load("CottageTex4", "Chimneytexture.tga");

	TextureManagerAttorneyToEngine::Load("space_frigate", "space_frigate.tga");
	TextureManagerAttorneyToEngine::Load("ground", "ground1.tga");
	TextureManagerAttorneyToEngine::Load("gravel", "gravel.tga");
	TextureManagerAttorneyToEngine::Load("rock", "rock.tga");
	TextureManagerAttorneyToEngine::Load("grid", "grid.tga");

	TextureManagerAttorneyToEngine::Load("Body", "body.tga");
	TextureManagerAttorneyToEngine::Load("Track", "track.tga");
	TextureManagerAttorneyToEngine::Load("Aliens", "Aliens.tga");
	TextureManagerAttorneyToEngine::Load("xhair", "crosshair.tga");
	TextureManagerAttorneyToEngine::Load("Life", "Lives.tga");

	TextureManagerAttorneyToEngine::Load("Skybox", "NightSkyBox.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------
	ShaderManagerAttorneyToEngine::Load(Shader_Type::COLOR_NOLIGHT);
	ShaderManagerAttorneyToEngine::Load(Shader_Type::COLOR_LIGHT);
	ShaderManagerAttorneyToEngine::Load(Shader_Type::TEX_LIGHT);
	ShaderManagerAttorneyToEngine::Load(Shader_Type::TEX_NOLIGHT);

	SFXManager::AddShader(ShaderManager::GetShaderColor());
	SFXManager::AddShader(ShaderManager::GetShaderColorLight());
	SFXManager::AddShader(ShaderManager::GetShaderTexLight());
	SFXManager::AddShader(ShaderManager::GetShaderTexture());

	//---------------------------------------------------------------------------------------------------------
	// Load our Terrain
	//---------------------------------------------------------------------------------------------------------
	TerrainManagerAttorneyToEngine::Load("ourTerrain", TextureManager::Get("ground"), 
		"../Assets/Textures/HMtest.tga", 10000, 1000, -8);
	TerrainManagerAttorneyToEngine::Load("terrain2", TextureManager::Get("ground"),
		"../Assets/Textures/HMtest.tga", 5000, 1000, -70);
	TerrainManagerAttorneyToEngine::Load("tankTerrain", TextureManager::Get("ground"),
		"../Assets/Textures/HMtest.tga", 15000, 500, -70);
	TerrainManagerAttorneyToEngine::Load("tankTerrain2", TextureManager::Get("gravel"),
		"../Assets/Textures/HMtest.tga", 10000, 750, -70);
	TerrainManagerAttorneyToEngine::Load("tankTerrain3", TextureManager::Get("rock"),
		"../Assets/Textures/HMtest.tga", 10000, 1000, -70);

	//---------------------------------------------------------------------------------------------------------
	// Load the SkyBoxes
	//---------------------------------------------------------------------------------------------------------
	SkyBoxManager::Load("sky", TextureManager::Get("Skybox"));
}