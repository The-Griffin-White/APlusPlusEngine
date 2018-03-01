#include "GodCam.h"
#include "../Engine/SceneManager.h"

GodCam::GodCam()
{
	camspeed = 0.5f;
	rotspeed = 0.005f;
	registered = false;
}
GodCam::~GodCam()
{
	// nada
}
void GodCam::Initialize()
{
	SceneEntry();
}

void GodCam::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();

	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);

	RegisterKeys();
}
void GodCam::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();

	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_P, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);

	DeregisterKeys();
}

void GodCam::RegisterKeys()
{
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = true;
}
void GodCam::DeregisterKeys()
{
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_Q, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_E, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, Inputable::INPUT_EVENT_TYPE::KEY_PRESS);
	registered = false;
}

void GodCam::Update()
{
	SceneManager::GetCurrentCamera()->updateCamera();
}

void GodCam::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_O:
		if (!registered)
			RegisterKeys();
		break;
	case AZUL_KEY::KEY_P:
		if (registered)
			DeregisterKeys();
		break;
	case AZUL_KEY::KEY_Q:
		SceneManager::GetCurrentCamera()->TranslateUpDown(camspeed);
		break;
	case AZUL_KEY::KEY_E:
		SceneManager::GetCurrentCamera()->TranslateUpDown(-camspeed);
		break;
	case AZUL_KEY::KEY_W:
		SceneManager::GetCurrentCamera()->TranslateFwdBack(camspeed);
		break;
	case AZUL_KEY::KEY_A:
		SceneManager::GetCurrentCamera()->TranslateLeftRight(-camspeed);
		break;
	case AZUL_KEY::KEY_S:
		SceneManager::GetCurrentCamera()->TranslateFwdBack(-camspeed);
		break;
	case AZUL_KEY::KEY_D:
		SceneManager::GetCurrentCamera()->TranslateLeftRight(camspeed);
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		SceneManager::GetCurrentCamera()->TiltUpDown(rotspeed);
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		SceneManager::GetCurrentCamera()->TurnLeftRight(rotspeed);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		SceneManager::GetCurrentCamera()->TiltUpDown(-rotspeed);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		SceneManager::GetCurrentCamera()->TurnLeftRight(-rotspeed);
		break;
	}
}