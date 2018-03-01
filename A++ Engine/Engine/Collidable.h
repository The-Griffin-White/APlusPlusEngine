#ifndef _Collidable
#define _Collidable

#include "AzulCore.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"

class CollisionVolumeBSphere;

class Collidable
{
private:
	// Must keep to the base class as we don't have the derived type yet.
	SceneRegistrationCommand* pRegCmd;
	SceneRegistrationCommand* pDeregCmd;

	Model* pColModel;

	void SubmitCmd(SceneRegistrationCommand* c);

public:
	Collidable();
	virtual ~Collidable();
	/// \brief Collision with self, used for testing, defined by user
	/// \ingroup COLLISION
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Collision()
	///		{
	///			// Where Explodes() is a user defined class
	///			this->Explodes();
	///		}
	/// \endcode
	virtual void Collision() {};
	/// \brief Collision with another Collidable object, defined by user. Type should be specified by user in param
	/// \ingroup COLLISION
	///
	/// \param c The Collidable type we are hitting. Should be changed to a specific type based on user design
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Collision(OtherExampleObject* p)
	///		{
	///			// Where Explodes() is a user defined class
	///			p->Explodes();
	///			this->Explodes();
	///		}
	/// \endcode
	virtual void Collision(Collidable* c);
	const CollisionVolumeBSphere* GetBSphere();

protected:
	CollisionVolumeBSphere * BSphere;

	/// \brief Registers this Collidable for collision in the current scene
	/// \ingroup COLLISION
	///
	/// \tparam C The typename should correspond to the type of Collidable we are registering
	/// \param c The parameter should be the specific instance of the Collidable type we are registering
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Collidable::CollisionRegistration<ExampleGameObject>(this);
	///		}
	/// \endcode
	template < typename C >
	void CollisionRegistration(C* c)
	{
		DebugMsg::out("Submitting Collidable for registration\n");
		// create the command only once
		if (pRegCmd == nullptr)
		{
			pRegCmd = new CollisionRegistrationCommand<C>(c);
		}
		SubmitCmd(pRegCmd);
	};

	/// \brief Deregisters this Collidable from collision in the current scene
	/// \ingroup COLLISION
	///
	/// \tparam C The typename should correspond to the type of Collidable we are deregistering
	/// \param c The parameter should be the specific instance of the Collidable type we are deregistering
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Collidable::CollisionDeregistration<ExampleGameObject>(this);
	///		}
	/// \endcode
	template < typename C >
	void CollisionDeregistration(C* c)
	{
		DebugMsg::out("Submitting Collidable for deregistration\n");
		// create the command only once
		if (pDeregCmd == nullptr)
		{
			pDeregCmd = new CollisionDeregistrationCommand<C>(c);
		}
		SubmitCmd(pDeregCmd);
	};

	/// \brief Set the model you want to use for collision. 
	/// \ingroup COLLISION
	///
	/// \param mod The Model* used to generate a boundingsphere for collision
	/// \par EXAMPLE:
	/// \code
	///		ExampleGameObject::ExampleGameObject()
	///		{
	///			SetColliderModel(pGObj_SpaceFrigateLight->getModel());
	///		}
	/// \endcode
	void SetColliderModel(Model* mod);

	/// \brief Update the collision data to match the corresponding objects world matrix
	/// \ingroup COLLISION
	///
	/// \param mat The world matrix we want our collision volume to have
	/// \par EXAMPLE:
	/// \code
	///		ExampleGameObject::ExampleGameObject()
	///		{
	///			this->UpdateCollisionData(worldMatrix);
	///		}
	/// \endcode
	void UpdateCollisionData(Matrix& mat);

};

#endif