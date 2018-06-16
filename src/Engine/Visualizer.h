#ifndef _Visualizer
#define _Visualizer

#include <malloc.h>

#include "APPECore.h"
#include "Align16.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizerCommandBroker;
class Collidable;

class Visualizer : public Align16
{
private:
	static Visualizer *ptrInstance;

	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer& operator=(const Visualizer&) = delete;
	~Visualizer();

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	}
	static void Delete();

	VisualizerCommandBroker* cmdBroker;

	static Vect DEFAULT_COLOR;
	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	friend class VisualizerAttorneyToCommand;
	void privRenderBSphere(Matrix& S, const Vect& col);
	void privRenderAABB(Matrix& S, Vect& c, const Vect& col);
	void privRenderOBB(Matrix& S, Vect& c, const Vect& col);

	void privDraw();

	friend class VisualizerAttorneyToEngine;
	static void Terminate();

	friend class VisualizerAttorneyToCollisionVolume;
	static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);
	static void ShowAABB(const CollisionVolumeAABB& S, const Vect& col);
	static void ShowAABB(const Vect& min, const Vect& max, const Vect& col);
	static void ShowOBB(const CollisionVolumeOBB& S, const Vect& col);

public:

	/// \brief Called to create a collision model next frame.
	/// \ingroup VISUALIZE
	/// \param C The collidable we're modeling
	/// \param col Color the collision volume will be when rendered
	static void ShowCollisionVolume(const Collidable* c, const Vect& col = DEFAULT_COLOR);

	/// \brief Called to create a collision model using a Collidable's BSphere next frame.
	/// \ingroup VISUALIZE
	/// \param C The collidable we're modeling
	/// \param col Color the collision volume will be when rendered
	static void ShowCollisionBSphere(const Collidable* c, const Vect& col = DEFAULT_COLOR);

	/// \brief Called to create a collision model for a CollidableGroup next frame.
	/// \ingroup VISUALIZE
	/// \param C The AABB from the CollidableGroup.
	/// \param col Color the collision volume will be when rendered
	static void ShowCollidableGroupVolume(const CollisionVolumeAABB* c, const Vect& col = DEFAULT_COLOR)
	{
		Visualizer::ShowAABB(*c, col);
	};

	/// \brief Called to create an AABB model given a min and max point.
	/// \ingroup VISUALIZE
	/// \param min The minimum point of the AABB
	/// \param max The maximum point of the AABB
	/// \param col Color the AABB will be when rendered
	static void ShowAABBMinMax(const Vect& min, const Vect& max, const Vect& col = DEFAULT_COLOR)
	{
		Visualizer::ShowAABB(min, max, col);
	};

	static void Draw() { Instance().privDraw(); };

};

#endif