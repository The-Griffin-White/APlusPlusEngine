#include "PlaneBase.h"
#include "APlusPlusEngine.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "CameraManager.h"

#include "MovementDemoScene.h"
#include "SecondDemoScene.h"
#include "SpaceFrigate.h"

const float PlaneBase::scale = 500.0f;

PlaneBase::PlaneBase(Texture* tex)
{
	pGObj_Plane = new GraphicsObject_TextureLight(ModelManager::Get("Plane"));
	pGObj_Plane->SetTexture(tex);

	mWorldArray = new Matrix[totalNum];
	for (int i = 0; i < totalNum; ++i)
	{
		mWorldArray[i] = Matrix(ROT_X, PI * 0.5f);
	}
}

PlaneBase::~PlaneBase()
{
	DebugMsg::out("Deleted Axis\n");
}

void PlaneBase::Initialize()
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

void PlaneBase::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 5.0f);

	Collidable::CollisionRegistration<PlaneBase>(this);
}

void PlaneBase::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
	Alarmable::DeregisterAll();

	Collidable::CollisionDeregistration<PlaneBase>(this);
}

void PlaneBase::Collision(SpaceFrigate* sf)
{
	sf;
	DebugMsg::out("Plane Collided with SpaceFrigate\n");
}

void PlaneBase::Draw()
{
	for (int i = 0; i < totalNum; ++i)
	{
		pGObj_Plane->SetWorld(mWorldArray[i]);
		pGObj_Plane->Render();
	}
}

void PlaneBase::Alarm0()
{
	//	SceneManager::SetNextScene(new SecondDemoScene);
}