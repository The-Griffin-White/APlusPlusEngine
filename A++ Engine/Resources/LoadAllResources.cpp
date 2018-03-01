#include "AzulCore.h"
#include "../Engine/APlusPlusEngine.h"

#include "../Engine/ModelManagerAttorneyToEngine.h"
#include "../Engine/TextureManagerAttorneyToEngine.h"
#include "../Engine/ShaderManagerAttorneyToEngine.h"

void APlusPlusEngine::LoadAllResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	// Model from file ( .azul format)
	/*
	Model *pModelAxis = new Model("Axis.azul");
	Model *pModelPlane = new Model("Plane.azul");

	Model *pModelSpaceFrigate = new Model("space_frigate.azul");
	Model *PModelSphere = new Model(Model::PreMadedeModels::UnitSphere);
	//*/
	ModelManagerAttorneyToEngine::Load("Axis", "Axis");
	ModelManagerAttorneyToEngine::Load("Plane", "Plane");

	ModelManagerAttorneyToEngine::Load("space_frigate", "space_frigate");

	ModelManagerAttorneyToEngine::Load("Body", "t99body");
	ModelManagerAttorneyToEngine::Load("Turret", "t99turret");

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	// Direct loads
	/*
	Texture *pSpaceFrigateTex = new Texture("space_frigate.tga");
	Texture *pTextPlane = new Texture("grid.tga");
	//*/
	TextureManagerAttorneyToEngine::Load("space_frigate", "space_frigate.tga");
	TextureManagerAttorneyToEngine::Load("ground", "ground1.tga");
	TextureManagerAttorneyToEngine::Load("gravel", "gravel.tga");
	TextureManagerAttorneyToEngine::Load("rock", "rock.tga");
	TextureManagerAttorneyToEngine::Load("grid", "grid.tga");

	TextureManagerAttorneyToEngine::Load("Body", "body.tga");
	TextureManagerAttorneyToEngine::Load("Track", "track.tga");

	TextureManagerAttorneyToEngine::Load("Orange", 100, 0, 0);
	TextureManagerAttorneyToEngine::Load("Green", 0, 255, 0);

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------
	/*
	ShaderObject *pShaderObject_texture = new ShaderObject("textureFlatRender");
	ShaderObject *pShaderObject_textureLight = new ShaderObject("textureLightRender");
	//ShaderObject *pShaderObject_varyColor = new ShaderObject("colorVaryRender");
	ShaderObject *pShaderObject_constantColor = new ShaderObject("colorConstantRender");
	ShaderObject *pShaderObject_colorNoTexture = new ShaderObject("colorNoTextureRender");
	//ShaderObject *pShaderObject_colorNoTextureLight = new ShaderObject("colorNoTextureLightRender");
	//ShaderObject *pShaderObject_colorByPosition = new ShaderObject("colorVaryRender");
	//ShaderObject *pShaderObject_sprite = new ShaderObject("spriteRender");
	//ShaderObject *pShaderObject_spriteLine = new ShaderObject("spriteLineRender");
	//*/
	ShaderManagerAttorneyToEngine::Load("textureFlatRender", "textureFlatRender");
	ShaderManagerAttorneyToEngine::Load("textureLightRender", "textureLightRender");
	ShaderManagerAttorneyToEngine::Load("colorConstantRender", "colorConstantRender");
	ShaderManagerAttorneyToEngine::Load("colorNoTextureRender", "colorNoTextureRender");

}