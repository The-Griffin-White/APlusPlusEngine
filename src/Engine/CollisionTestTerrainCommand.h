#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "APPECore.h"
#include "Terrain.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"
#include "PWMathTools.h"

#include "Visualizer.h"

template<typename C>
class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
private:
	typename const CollidableGroup<C>::CollidableCollection& col;

public:
	CollisionTestTerrainCommand()
		: col(CollidableGroup<C>::GetColliderCollection())
	{};
	~CollisionTestTerrainCommand()
	{
		DebugMsg::out("CollisionTestTerrainCommand deleted\n");
	};

	/// \brief Iterates through all instances of registered Collidables and tests for collision with current terrain.
	/// \ingroup COL-MANAGE
	virtual void execute()
	{
		Terrain* t;
		// if false, do nothing. otherwise continue
		if (SceneManager::GetTerrain(t))
		{
			for (auto itr = col.begin(); itr != col.end(); ++itr)
			{
				TerrainAreaIterator TRIterator(t, *itr);
				
				while (!TRIterator.End())
				{
					// test if we collide with the bsphere
					// Find our "aabb" in the cellArray
					Vect min = TRIterator.GetMin();
					Vect max = TRIterator.GetMax();

					bool result = PWMathTools::Intersect(min, max, *((*itr)->GetCollisionBSphere()));
					if (result)
					{
						result = PWMathTools::Intersect(min, max, *itr);

						if (result)
						{
							Visualizer::ShowAABBMinMax(min, max, Colors::Red);
							(*itr)->TerrainCollision();
						}
						else
						{
							Visualizer::ShowAABBMinMax(min, max, Colors::Yellow);
						}
					}
					else
					{
						Visualizer::ShowAABBMinMax(min, max, Colors::Blue);
					}
					++TRIterator;
				}
			}
		}
	};

};

#endif _CollisionTestTerrainCommand