#include "Axis.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

Axis::Axis()
{
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"),
		ShaderManager::Get("colorNoTextureRender"));
}

Axis::~Axis()
{
	DebugMsg::out("Deleted Axis\n");
}

void Axis::Initialize()
{
	Matrix world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	GameObject::SubmitEntry();
}

void Axis::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
}

void Axis::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
}

void Axis::Draw()
{
	pGObj_Axis->Render(SceneManager::GetCurrentCamera());
}