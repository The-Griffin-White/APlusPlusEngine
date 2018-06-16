#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include <map>
#include <list>
#include "Inputable.h"

class SingleKeyEventManager;

class KeyboardEventManager
{
public:
	~KeyboardEventManager();
	
	using KeyMgrRef = std::list<Inputable*>::iterator;

	/// \brief Register an Inputable to use a certain key as either press or release.
	/// \ingroup INPUT-MANAGE
	/// \param p Pointer to the Inputable
	/// \param k The specific key
	/// \param e Either Press or Release
	KeyMgrRef Register(Inputable* p, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);
	/// \brief Deregister an Inputable from using a certain key as either press or release.
	/// \ingroup INPUT-MANAGE
	/// \param p Pointer to the Inputable
	/// \param k The specific key
	/// \param e Either Press or Release
	void Deregister(Inputable::KeyMgrRef keyRef, APPE_KEY k, Inputable::INPUT_EVENT_TYPE e);
	/// \brief Every frame - go through the SingleKeyEventManagers and process each.
	/// \ingroup INPUT-MANAGE
	void ProcessKeyEvents();

private:
	using keyMgrMap = std::map<APPE_KEY, SingleKeyEventManager*>;
	using keyMgrPair = std::pair<std::map<APPE_KEY, SingleKeyEventManager*>::iterator, bool>;

	keyMgrMap mapSKMgrs;

};

#endif