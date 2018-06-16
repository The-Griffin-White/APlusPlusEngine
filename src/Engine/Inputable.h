#ifndef _Inputable
#define _Inputable

#include "APPECore.h"
#include <map>
#include <list>

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
private:
	struct InputableData
	{
		InputRegistrationCommand* regCmd;
		InputDeregistrationCommand* deregCmd;
		bool registered;
	};

public:
	Inputable();
	virtual ~Inputable();

	enum INPUT_EVENT_TYPE
	{
		KEY_PRESS,
		KEY_RELEASE
	};

	using RegMap = std::map<std::pair<APPE_KEY, INPUT_EVENT_TYPE>, InputableData>;
	using RegMapRef = RegMap::iterator;
	using KeyMgrRef = std::list<Inputable*>::iterator;

protected:
	/// \brief Allows the user to define a KEY_PRESS or KEY_RELEASE function for key k
	/// \ingroup INPUT
	///
	/// \param k The APPE_KEY we want to register for use
	/// \param e Either KEY_PRESS or KEY_RELEASE depending on which key function we are looking for
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Inputable::SubmitKeyRegistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	///		}
	/// \endcode
	void SubmitKeyRegistration(APPE_KEY k, INPUT_EVENT_TYPE e);
	/// \brief Deregisters a key k from the KEY_PRESS or KEY_RELEASE function
	/// \ingroup INPUT
	///
	/// \param k The APPE_KEY we want to register for use
	/// \param e Either KEY_PRESS or KEY_RELEASE depending on which key function we are looking for
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Inputable::SubmitKeyDeregistration(APPE_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	///		}
	/// \endcode
	void SubmitKeyDeregistration(APPE_KEY k, INPUT_EVENT_TYPE e);

private:
	friend class InputableAttorneyToSKManager;
	friend class InputableAttorneyToCommand;
	void SceneRegistration(RegMapRef ref, APPE_KEY k, INPUT_EVENT_TYPE e);
	void SceneDeregistration(RegMapRef ref, KeyMgrRef keyRef, APPE_KEY k, INPUT_EVENT_TYPE e);

	/// \brief Defined by the user as a switch statement for every registered key.
	/// \ingroup INPUT
	///
	/// \param k The APPE_KEY passed in to select which key function we will use
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::KeyPressed(APPE_KEY k)
	///		{
	///			switch(k)
	///			{
	///				case APPE_KEY::KEY_E:
	///					this->ShootGun();
	///					break;
	///				case APPE_KEY::KEY_SHIFT:
	///					this->Sprint();
	///					break;
	///			}
	///		}
	/// \endcode
	virtual void KeyPressed(APPE_KEY k) { k; };
	/// \brief Defined by the user as a switch statement for every registered key.
	/// \ingroup INPUT
	///
	/// \param k The APPE_KEY passed in to select which key function we will use
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::KeyReleased(APPE_KEY k)
	///		{
	///			switch(k)
	///			{
	///				case APPE_KEY::KEY_P:
	///					this->ShowCollision = false;
	///					break;
	///				case APPE_KEY::KEY_O:
	///					this->Pause = false;
	///					break;
	///			}
	///		}
	/// \endcode
	virtual void KeyReleased(APPE_KEY k) { k; };

	RegMap regMap;

	InputRegistrationCommand* pRegistrationCmd;
	InputDeregistrationCommand* pDeregistrationCmd;
};

#endif