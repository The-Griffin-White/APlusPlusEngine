#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "SceneAttorneyToCollidable.h"

#include "CollidableGroup.h"
#include "SceneAttorneyToCollidable.h"
#include "CollisionVolumeBSphere.h"

Collidable::Collidable()
{
	pRegCmd = nullptr;
	pDeregCmd = nullptr;

	pColModel = nullptr;
	BSphere = new CollisionVolumeBSphere;
}

Collidable::~Collidable()
{
	DebugMsg::out("Collidable deleted\n");
	delete BSphere;
}

const CollisionVolumeBSphere* Collidable::GetBSphere()
{
	return BSphere;
}

void Collidable::SetColliderModel(Model* mod)
{
	pColModel = mod;
}

void Collidable::UpdateCollisionData(Matrix& mat)
{
	BSphere->ComputeData(pColModel, mat);
}

void Collidable::Collision(Collidable* c)
{
	c;
	DebugMsg::out("Collidable Collision\n");
}

void Collidable::SubmitCmd(SceneRegistrationCommand* c)
{
	SceneAttorneyToCollidable::SubmitCommand(c);
}