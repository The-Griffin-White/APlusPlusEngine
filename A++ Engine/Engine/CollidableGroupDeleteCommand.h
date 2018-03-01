#ifndef _CollidableGroupDeleteCommand
#define _CollidableGroupDeleteCommand

#include "DeleteBaseCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollidableGroupDeleteCommand : public DeleteBaseCommand
{
public:
	CollidableGroupDeleteCommand()
		: ptrCG(CollidableGroup<C>::GetPointer())
	{};

private:
	CollidableGroup<C>* ptrCG;
	
	virtual void execute() { ptrCG->Delete(); };
	
};


#endif