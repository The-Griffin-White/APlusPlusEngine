#include "Plane.h"
#include "../Engine/APlusPlusEngine.h"
#include "../Engine/SceneManager.h"
#include "../Engine/ModelManager.h"
#include "../Engine/ShaderManager.h"
#include "../Engine/TextureManager.h"
#include "../Engine/CameraManager.h"

#include "MovementDemoScene.h"
#include "SecondDemoScene.h"
#include "SpaceFrigate.h"

Plane::Plane()
{
	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"),
		ShaderManager::Get("textureFlatRender"),
		TextureManager::Get("ground"));

	mWorldArray = new Matrix[totalNum];
	for (int i = 0; i < totalNum; ++i)
	{
		mWorldArray[i] = Matrix(SCALE, scale, scale, scale);
	}
}

Plane::~Plane()
{
	DebugMsg::out("Deleted Axis\n");
}

void Plane::Initialize()
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

void Plane::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 5.0f);

	Collidable::CollisionRegistration<Plane>(this);
}

void Plane::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<Plane>(this);
}

void Plane::Collision(SpaceFrigate* sf)
{
	sf;
	DebugMsg::out("Plane Collided with SpaceFrigate\n");
}

void Plane::Draw()
{
	for (int i = 0; i < totalNum; ++i)
	{
		pGObj_Plane->SetWorld(mWorldArray[i]);
		pGObj_Plane->Render(SceneManager::GetCurrentCamera());
	}
}

void Plane::Alarm0()
{
//	SceneManager::SetNextScene(new SecondDemoScene);
}