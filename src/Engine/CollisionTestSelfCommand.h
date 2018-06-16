#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "APPECore.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionTestSelfCommand : public CollisionTestCommandBase
{
private:
	typename const CollidableGroup<C>::CollidableCollection& col;

public:
	CollisionTestSelfCommand()
		: col(CollidableGroup<C>::GetColliderCollection())
	{};
	~CollisionTestSelfCommand() { DebugMsg::out("CollisionTestSelfCommand deleted\n"); };

	/// \brief Iterates through all instances of registered Collidables and tests for self collision.
	/// \ingroup COL-MANAGE
	virtual void execute()
	{
		for (auto itr1 = col.begin(); itr1 != col.end(); ++itr1)
		{
			for (auto itr2 = col.begin(); itr2 != col.end(); ++itr2)
			{
				if (*itr1 != *itr2)
				{
					bool test_result = PWMathTools::IntersectBSpheres(*itr1, *itr2);

					// Test that the BSpheres collide (cheapest test)
					if (test_result)
					{
						Visualizer::ShowCollisionBSphere(*itr2, Colors::Yellow);

						test_result = PWMathTools::Intersect(*itr1, *itr2);

						if (test_result)
						{
							(*itr1)->Collision(*itr2);
							(*itr2)->Collision(*itr1);

							Visualizer::ShowCollisionVolume(*itr1, Colors::Red);
							Visualizer::ShowCollisionVolume(*itr2, Colors::Red);
							//	DebugMsg::out("Collision!\n");
						}
						else
						{
							Visualizer::ShowCollisionVolume(*itr1, Colors::LightGray);
							Visualizer::ShowCollisionVolume(*itr2, Colors::LightGray);
						}
					}
					else
					{
						Visualizer::ShowCollisionBSphere(*itr2, Colors::LightGray);
					}
				}
			}
		}
//		DebugMsg::out("CollisionTestSelfCommand executed\n");
	};

};

#endif