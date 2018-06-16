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

	virtual ~CollidableGroupDeleteCommand()
	{
	}

private:
	CollidableGroup<C>* ptrCG;
	
	virtual void execute() { CollidableGroup<C>::Delete(); };
	
};


#endif