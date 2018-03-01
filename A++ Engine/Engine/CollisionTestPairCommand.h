#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "AzulCore.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
#include "PWMathTools.h"

#include "Visualizer.h"

template <typename C1, typename C2>
class CollisionTestPairCommand : public CollisionTestCommandBase
{
private:
	typename const CollidableGroup<C1>::CollidableCollection& col1;
	typename const CollidableGroup<C2>::CollidableCollection& col2;

public:
	CollisionTestPairCommand() 
		: col1(CollidableGroup<C1>::GetColliderCollection()),
		col2(CollidableGroup<C2>::GetColliderCollection())
	{};
	~CollisionTestPairCommand() { DebugMsg::out("CollisionTestPairCommand deleted\n"); };

	/// \brief Iterates through all pairs and instances of registered Collidables and tests for pair collision.
	/// \ingroup COL-MANAGE
	virtual void execute() 
	{
		for (auto itr1 = col1.begin(); itr1 != col1.end(); itr1++)
		{
			for (auto itr2 = col2.begin(); itr2 != col2.end(); itr2++)
			{
				const CollisionVolumeBSphere& bs1 = *(*itr1)->GetBSphere();
				const CollisionVolumeBSphere& bs2 = *(*itr2)->GetBSphere();
				bool test_result = PWMathTools::Intersect(bs1, bs2);

				if (test_result)
				{
					(*itr1)->Collision(*itr2);
					(*itr2)->Collision(*itr1);

				//	Visualizer::ShowBSphere(bs1, Colors::Red);
				//	Visualizer::ShowBSphere(bs2, Colors::Red);
				}
				else
				{
				//	Visualizer::ShowBSphere(bs1, Colors::Blue);
				//	Visualizer::ShowBSphere(bs2, Colors::Blue);
				}
			}
		}
//		DebugMsg::out("CollisionTestPairCommand executed\n");
	};

};

#endif