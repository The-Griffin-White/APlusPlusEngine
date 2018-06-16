#ifndef _Terrain
#define _Terrain

#include "GameObject.h"
#include <string>

class Texture;
class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;

class Terrain : public GameObject
{
public:
	Terrain();
	void Initialize(Texture* tex, const char* heightMap, float len, float maxheight, 
		float ytrans, float firstU, float secondU, float firstV, float secondV);
	virtual ~Terrain();

	bool GetNormal(Collidable*, Vect&);
	bool GetHeight(Collidable*, float&);
	bool PointUnderCollidable(Collidable*, Vect&);

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

	virtual void Draw();

	int TerrainWidth();

	float cellMinHeight(const int& x, const int& z);
	float cellMaxHeight(const int& x, const int& z);
	Vect cellMin(const int& x, const int& z);
	Vect cellMax(const int& x, const int& z);

	void SetMaterial(const Vect amb, const Vect dif, const Vect spec);

private:
	friend struct TerrainAreaIterator;
	
	static const int CELLARRAY_WIDTH = 2;
	static const int VECTARRAY_WIDTH = 4;

	TerrainObject * pTerrain;
	TerrainModel * pModel;
};

// Used in collision
struct TerrainAreaIterator
{
	// Constructors
	TerrainAreaIterator() = delete;
	TerrainAreaIterator(Terrain*, Collidable*);
	// Incrementers
	TerrainAreaIterator& operator++();
	TerrainAreaIterator operator++(int);
	// Test if at the end of rectangle
	bool End();
	bool end;
	// Operations
	Vect GetMin();
	Vect GetMax();
	// Variables
	Terrain* tr;
	Collidable* col;
	int startX;
	int startZ;
	int x;
	int z;
	int endX;
	int endZ;
};

#endif _Terrain