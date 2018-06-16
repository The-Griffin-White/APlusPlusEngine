#ifndef _DrawableManager
#define _DrawableManager

#include <list>

class Drawable;

class DrawableManager
{
public:
	using DrawableList = std::list<Drawable*>;
	using DrawableListRef = DrawableList::iterator;

	DrawableManager() {};
	~DrawableManager();

	/// \brief Registers a Drawable to the manager.
	/// \ingroup DRAW-MANAGE
	/// \param up Pointer to our Drawable.
	DrawableListRef Register(Drawable* up);
	/// \brief Calls Draw on all registered Drawables.
	/// \ingroup DRAW-MANAGE
	void ProcessElements();
	/// \brief Deregisters a Drawable using a given pointer (deprecated).
	/// \ingroup DRAW-MANAGE
	/// \param up Pointer to Drawable.
	void Deregister(Drawable* up);
	/// \brief Deregisters a Drawable using a given iterator to the Drawable on our list.
	/// \ingroup DRAW-MANAGE
	/// \param itr Iterator to the Drawable's position on our list.
	void Deregister(DrawableListRef itr);


private:
	DrawableList storageList;

};

#endif