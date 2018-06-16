#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "APPECore.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "PWMathTools.h"

#include "Visualizer.h"

template <typename C1, typename C2>
class CollisionTestPairCommand : public CollisionTestCommandBase
{
private:
	typename const CollidableGroup<C1>::CollidableCollection& col1;
	typename const CollidableGroup<C2>::CollidableCollection& col2;

	const CollisionVolumeAABB* group1AABB;
	const CollisionVolumeAABB* group2AABB;

public:
	CollisionTestPairCommand() 
		: col1(CollidableGroup<C1>::GetColliderCollection()),
		col2(CollidableGroup<C2>::GetColliderCollection())
	{};
	~CollisionTestPairCommand() 
	{
		// Only borrowing these, so we don't delete them...
		group1AABB = nullptr;
		group2AABB = nullptr;
		DebugMsg::out("CollisionTestPairCommand deleted\n");
	};

	/// \brief Iterates through all pairs and instances of registered Collidables and tests for pair collision.
	/// \ingroup COL-MANAGE
	virtual void execute() 
	{
		group1AABB = CollidableGroup<C1>::GetCollidableGroupAABB();
		group2AABB = CollidableGroup<C2>::GetCollidableGroupAABB();

		bool test_result = PWMathTools::Intersect(*group1AABB, *group2AABB);

		// Test CollidableGroup AABB's against each others...
		if (test_result)
		{
			Visualizer::ShowCollidableGroupVolume(group1AABB, Colors::Green);
			Visualizer::ShowCollidableGroupVolume(group2AABB, Colors::Green);

			for (auto itr1 = col1.begin(); itr1 != col1.end(); itr1++)
			{
				test_result = PWMathTools::Intersect(*itr1, *group2AABB);

				// Test that Collidable in group 1 collides with group 2's AABB
				if (test_result)
				{
					Visualizer::ShowCollisionBSphere(*itr1, Colors::Orange);

					for (auto itr2 = col2.begin(); itr2 != col2.end(); itr2++)
					{
						test_result = PWMathTools::IntersectBSpheres(*itr1, *itr2);

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
				else
				{
					Visualizer::ShowCollisionBSphere(*itr1, Colors::LightGray);
				}
			}
		}
		else
		{
			Visualizer::ShowCollidableGroupVolume(group1AABB, Colors::LightGray);
			Visualizer::ShowCollidableGroupVolume(group2AABB, Colors::LightGray);
		}
//		DebugMsg::out("CollisionTestPairCommand executed\n");
	};

};

#endif