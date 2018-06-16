#include "Axis.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

Axis::Axis()
{
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"));
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
	pGObj_Axis->Render();
}