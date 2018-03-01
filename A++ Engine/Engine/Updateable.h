#ifndef _Updateable
#define _Updateable

#include "UpdateableManager.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

enum class RegistrationState;

class Updateable
{
public:
	Updateable();
	virtual ~Updateable();

protected:
	/// \brief The scene will call the objects Update() function every frame
	/// \ingroup UPDATE
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Updateable::SubmitUpdateRegistration();
	///		}
	/// \endcode
	void SubmitUpdateRegistration();
	/// \brief Deregisters the object so that it's Update() function is not called
	/// \ingroup UPDATE
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Updateable::SubmitUpdateDeregistration();
	///		}
	/// \endcode
	void SubmitUpdateDeregistration();

private:
	friend class UpdateableAttorneyToUpdateableManager;
	friend class UpdateableAttorneyToUpdateRegCmd;
	friend class UpdateableAttorneyToUpdateDeregCmd;
	/// \brief Called every frame and used to update object data such as position or rotation
	/// \ingroup UPDATE
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::Update()
	///		{
	///			ObjectPosition += Vect(0, 0, 1);
	///		}
	/// \endcode
	virtual void Update() {};

	void SceneRegistration();
	void SceneDeregistration();

	RegistrationState RegStateCurr;
	UpdateableManager::UpdateableListRef storageRef;
	UpdateRegistrationCommand* pRegistrationCmd;
	UpdateDeregistrationCommand* pDeregistrationCmd;
};

#endif