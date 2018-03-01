#include "AzulCore.h"
#include "APlusPlusEngine.h"

#include "ModelManagerAttorneyToEngine.h"
#include "TextureManagerAttorneyToEngine.h"
#include "ShaderManagerAttorneyToEngine.h"
#include "TimeManagerAttorneyToAPlusPlusEngine.h"

#include "SceneManager.h"
#include "../User/MovementDemoScene.h"

APlusPlusEngine* APlusPlusEngine::gameInstance = nullptr;

// Global varables just for the demo:
// Note: Don't do this!
// Global vars should always be avoided in a finished product! 

// Camera vars
const Vect CamShipOffset(0, 70, -150);
const Vect CamLookAt(0, 0, 0);

//-----------------------------------------------------------------------------
// APlusPlusEngine::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void APlusPlusEngine::Initialize()
{
	// Game Window Device setup
	this->GameInitialize();

	// Use this area, for one time non-graphic creation

}

void APlusPlusEngine::TerminateGame()
{
	Instance().ClearUserContent();
	SceneManager::Terminate();
	DebugMsg::out("Deleting APlusPlusEngine\n");

	// Clean up the game instance;
	delete gameInstance;
	gameInstance = nullptr;
}

//-----------------------------------------------------------------------------
// APlusPlusEngine::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void APlusPlusEngine::LoadContent()
{
	// --------------------------------------------------------------------------------------------------------
	// Call LoadAllResources to handle this in a location the user can edit (without breaking engine files)
	// --------------------------------------------------------------------------------------------------------
	this->LoadAllResources();

	this->SetStartScene();
}

//-----------------------------------------------------------------------------
// APlusPlusEngine::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void APlusPlusEngine::Update()
{
	TimeManagerAttorneyToAPlusPlusEngine::UpdateTime( GetTimeInSeconds() );

	SceneManager::Update();
}

//-----------------------------------------------------------------------------
// APlusPlusEngine::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void APlusPlusEngine::Draw()
{
	SceneManager::Draw();
}

//-----------------------------------------------------------------------------
// APlusPlusEngine::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void APlusPlusEngine::UnLoadContent()
{
	// general clean up.
	DebugMsg::out("Unloading APlusPlusEngine\n");
	ModelManagerAttorneyToEngine::Delete();
	ModelManagerAttorneyToEngine::Terminate();
	TextureManagerAttorneyToEngine::Delete();
	TextureManagerAttorneyToEngine::Terminate();
	ShaderManagerAttorneyToEngine::Delete();
	ShaderManagerAttorneyToEngine::Terminate();
}

void APlusPlusEngine::SetClearColor(const float& red, const float& green, const float& blue, float alpha)
{
	Engine::SetClearColor(red, green, blue, alpha);
}
void APlusPlusEngine::SetClearColor(const Vect& col, float alpha)
{
	Engine::SetClearColor(col.X(), col.Y(), col.Z(), alpha);
}
