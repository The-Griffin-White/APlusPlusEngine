#ifndef _CollidableGroupUpdateCommand
#define _CollidableGroupUpdateCommand

#include "CommandBase.h"
#include "CollidableGroup.h"

template <typename C>
class CollidableGroupUpdateCommand : public CommandBase
{
public:
	CollidableGroupUpdateCommand()
		: ptrCG(CollidableGroup<C>::GetPointer())
	{};

	~CollidableGroupUpdateCommand()
	{
	}

private:
	CollidableGroup<C>* ptrCG;

	virtual void execute() { CollidableGroup<C>::UpdateAABB(); };

};


#endif