#ifndef _UpdateableManager
#define _UpdateableManager

#include <list>

class Updateable;

class UpdateableManager
{
public:
	using UpdateableList = std::list<Updateable*>;
	using UpdateableListRef = UpdateableList::iterator;

	UpdateableManager() {};
	~UpdateableManager();

	/// \brief Registers a Updateable to the manager.
	/// \ingroup UPDATE-MANAGE
	/// \param up Pointer to our Updateable.
	UpdateableListRef Register(Updateable* up);
	/// \brief Calls Update on all registered Updateable.
	/// \ingroup UPDATE-MANAGE
	void ProcessElements();
	/// \brief Deregisters a Updateable using a given pointer (deprecated).
	/// \ingroup UPDATE-MANAGE
	/// \param up Pointer to Updateable.
	void Deregister(Updateable* up);
	/// \brief Deregisters a Updateable using a given iterator to the Updateable on our list.
	/// \ingroup UPDATE-MANAGE
	/// \param itr Iterator to the Updateable's position on our list.
	void Deregister(UpdateableListRef itr);

private:
	UpdateableList storageList;

};

#endif