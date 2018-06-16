#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "SceneAttorneyToCollidable.h"

#include "CollidableGroup.h"
#include "SceneAttorneyToCollidable.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

Collidable::Collidable()
{
	pRegCmd = nullptr;
	pDeregCmd = nullptr;

	pBSphere = new CollisionVolumeBSphere;

	pColModel = nullptr;
	ColVolume = nullptr;
}

Collidable::~Collidable()
{
	DebugMsg::out("Collidable deleted\n");
	delete ColVolume;
	delete pBSphere;
	if (pRegCmd) delete pRegCmd;
	if (pDeregCmd) delete pDeregCmd;
}

const CollisionVolume& Collidable::GetCollisionVolume() const
{
	return *ColVolume;
}

const CollisionVolumeBSphere* Collidable::GetCollisionBSphere() const
{
	return pBSphere;
}

void Collidable::SetColliderModel(Model* mod, CollisionModels type)
{
	if (ColVolume) delete ColVolume;

	if (type == CollisionModels::BSphere)
	{
		ColVolume = new CollisionVolumeBSphere;
	}
	else if (type == CollisionModels::AABB)
	{
		ColVolume = new CollisionVolumeAABB;
	}
	else if (type == CollisionModels::OBB)
	{
		ColVolume = new CollisionVolumeOBB(mod);
	}
	else
	{
		assert(false && "Don't have that collision model yet");
	}
	
	pColModel = mod;
}

void Collidable::UpdateCollisionData(Matrix& mat)
{
	pBSphere->ComputeData(pColModel, mat);
	ColVolume->ComputeData(pColModel, mat);
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