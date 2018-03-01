#include "Plane3.h"
#include "../Engine/APlusPlusEngine.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "MovementDemoScene.h"
#include "SecondDemoScene.h"
#include "SpaceFrigate.h"

Plane3::Plane3()
{
	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"),
		ShaderManager::Get("textureFlatRender"),
		TextureManager::Get("rock"));

	mWorldArray = new Matrix[totalNum];
	for (int i = 0; i < totalNum; ++i)
	{
		mWorldArray[i] = Matrix(SCALE, scale, scale, scale);
	}
}

Plane3::~Plane3()
{
	DebugMsg::out("Deleted Axis\n");
}

void Plane3::Initialize()
{
	float xpos = float(-1 * (rowNum / 2));
	float zpos = float(-1 * (rowNum / 2));
	int count = 1;

	for (int i = 0; i < totalNum - 1; ++i)
	{
		if (count == rowNum)
		{
			count = 1;
			xpos = -3;
			zpos += 1.0f;
		}
		mWorldArray[i] *= Matrix(TRANS, xpos * scale, 0, zpos * scale);

		++count;
		xpos += 1.0f;
	}

	GameObject::SubmitEntry();
}

void Plane3::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 5.0f);

	Collidable::CollisionRegistration<Plane3>(this);
}

void Plane3::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<Plane3>(this);
}

void Plane3::Collision(SpaceFrigate* sf)
{
	sf;
	DebugMsg::out("Plane Collided with SpaceFrigate\n");
}

void Plane3::Draw()
{
	for (int i = 0; i < totalNum; ++i)
	{
		pGObj_Plane->SetWorld(mWorldArray[i]);
		pGObj_Plane->Render(SceneManager::GetCurrentCamera());
	}
}

void Plane3::Alarm0()
{
	//	SceneManager::SetNextScene(new SecondDemoScene);
}