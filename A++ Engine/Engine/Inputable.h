#ifndef _Inputable
#define _Inputable

#include "AzulCore.h"
#include <map>

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
public:
	Inputable();
	virtual ~Inputable();

	enum INPUT_EVENT_TYPE
	{
		KEY_PRESS,
		KEY_RELEASE
	};

	void SceneRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e);
	void SceneDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e);

protected:
	/// \brief Allows the user to define a KEY_PRESS or KEY_RELEASE function for key k
	/// \ingroup INPUT
	///
	/// \param k The AZUL_KEY we want to register for use
	/// \param e Either KEY_PRESS or KEY_RELEASE depending on which key function we are looking for
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneEntry()
	///		{
	///			Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	///		}
	/// \endcode
	void SubmitKeyRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e);
	/// \brief Deregisters a key k from the KEY_PRESS or KEY_RELEASE function
	/// \ingroup INPUT
	///
	/// \param k The AZUL_KEY we want to register for use
	/// \param e Either KEY_PRESS or KEY_RELEASE depending on which key function we are looking for
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::SceneExit()
	///		{
	///			Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_O, Inputable::INPUT_EVENT_TYPE::KEY_PRESS)
	///		}
	/// \endcode
	void SubmitKeyDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e);

private:
	friend class InputableAttorneyToSKManager;

	/// \brief Defined by the user as a switch statement for every registered key.
	/// \ingroup INPUT
	///
	/// \param k The AZUL_KEY passed in to select which key function we will use
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::KeyPressed(AZUL_KEY k)
	///		{
	///			switch(k)
	///			{
	///				case AZUL_KEY::KEY_E:
	///					this->ShootGun();
	///					break;
	///				case AZUL_KEY::KEY_SHIFT:
	///					this->Sprint();
	///					break;
	///			}
	///		}
	/// \endcode
	virtual void KeyPressed(AZUL_KEY k) { k; };
	/// \brief Defined by the user as a switch statement for every registered key.
	/// \ingroup INPUT
	///
	/// \param k The AZUL_KEY passed in to select which key function we will use
	/// \par EXAMPLE
	/// \code
	///		void ExampleGameObject::KeyReleased(AZUL_KEY k)
	///		{
	///			switch(k)
	///			{
	///				case AZUL_KEY::KEY_P:
	///					this->ShowCollision = false;
	///					break;
	///				case AZUL_KEY::KEY_O:
	///					this->Pause = false;
	///					break;
	///			}
	///		}
	/// \endcode
	virtual void KeyReleased(AZUL_KEY k) { k; };

	using CurrentlyRegMap = std::map<std::pair<AZUL_KEY, INPUT_EVENT_TYPE>, bool>;
	using RegMap = std::map<std::pair<AZUL_KEY, INPUT_EVENT_TYPE>, InputRegistrationCommand*>;
	using DeregMap = std::map<std::pair<AZUL_KEY, INPUT_EVENT_TYPE>, InputDeregistrationCommand*>;

	CurrentlyRegMap currentlyRegistered;
	RegMap regCmdMap;
	DeregMap deregCmdMap;

	InputRegistrationCommand* pRegistrationCmd;
	InputDeregistrationCommand* pDeregistrationCmd;
};

#endif