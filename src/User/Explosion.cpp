#include "Explosion.h"
#include "ExplosionFactory.h"

#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "SceneManager.h"

Explosion::Explosion()
{
	Explode = new GraphicsObject_ColorNoTexture(ModelManager::Get("Sphere"));
	Explode->SetColor(Colors::Red);
}

Explosion::~Explosion()
{
	delete Explode;
}

void Explosion::Initialize(const Vect& p)
{
	pos = p;
	scale = 3.0f;
	Matrix world = Matrix(SCALE, scale, scale, scale) * Matrix(IDENTITY) * Matrix(TRANS, pos);
	Explode->SetWorld(world);

	this->SubmitEntry();
}

void Explosion::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_0, 0.75f);
}
void Explosion::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Alarmable::DeregisterAll();

	ExplosionFactory::RecycleExplosion(this);
}

void Explosion::Update()
{
	scale += 0.3f;
	Matrix world = Matrix(SCALE, scale, scale, scale) * Matrix(IDENTITY) * Matrix(TRANS, pos);
	Explode->SetWorld(world);
}
void Explosion::Draw()
{
	Explode->Render();
}

void Explosion::Alarm0()
{
	this->SubmitExit();
}