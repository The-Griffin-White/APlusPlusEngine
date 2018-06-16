#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include <list>
#include "Inputable.h"

class SingleKeyEventManager
{
public:
	SingleKeyEventManager();
	SingleKeyEventManager(APPE_KEY k);
	~SingleKeyEventManager();

	using KeyMgrRef = std::list<Inputable*>::iterator;

	/// \brief Register an Inputable to use a certain key as either press or release.
	/// \ingroup INPUT-MANAGE
	/// \param p Pointer to the Inputable
	/// \param e Either Press or Release
	KeyMgrRef Register(Inputable* p, Inputable::INPUT_EVENT_TYPE e);
	/// \brief Deregister an Inputable from using a certain key as either press or release.
	/// \ingroup INPUT-MANAGE
	/// \param p Pointer to the Inputable
	/// \param e Either Press or Release
	void Deregister(Inputable::KeyMgrRef keyRef, Inputable::INPUT_EVENT_TYPE e);

	/// \brief Check each registered Inputable and see if the key for this manager is being pressed or released, then trigger the Inputable's call.
	/// \ingroup INPUT-MANAGE
	void ProcessKeyEvent();

private:
	APPE_KEY key;
	std::list<Inputable*> keyPressCol;
	std::list<Inputable*> keyReleaseCol;

};

#endif