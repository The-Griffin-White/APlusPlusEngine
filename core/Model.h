#ifndef MODEL_H
#define MODEL_H

#include <d3d11.h>
#include "Vect.h"
#include <malloc.h>
#include "Align16.h"
#include "Matrix.h"

class MeshSeparator;

struct StandardVertex : public Align16
{
	Vect Pos;
	float u;    
	float v;
	Vect normal;
	Vect Color;
	int meshNum;		// new property

	void set(float _x, float _y, float _z,
		float _u = 0, float _v = 0,
		float _nx = 0, float _ny = 0, float _nz = 0,
		float _r = 1, float _g = 1, float _b = 1, int num = 0 )
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = Vect(_nx, _ny, _nz, 0);
		Color = Vect(_r, _g, _b);
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, float _u, float _v, const Vect& n, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = _u;
		v = _v;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		Color = c;
		meshNum = num;
	}

	void set(float _x, float _y, float _z, const Vect& n, const Vect& c, int num = 0)
	{
		Pos = Vect(_x, _y, _z);
		u = 0;
		v = 0;
		normal = n;
		Color = c;
		meshNum = num;
	}

	void set(const Vect& p, const Vect& c)
	{
		Pos = p;
		Color = c;
	}
};

struct TriangleByIndex
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

	void set(int _v0, int _v1, int _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
	}
};

class Model : public Align16
{
private:
	// Model information
	TriangleByIndex * pTriList;
	StandardVertex* pStdVerts;
	Vect* pVectList;				// Converted version of the above...
	int numVerts;
	int numTris;

	MeshSeparator* meshes;

	// Bounding Sphere: bounding volume
	Vect center;
	float radius;

	// AABB: axis aligned bounding box
	// Specifies the minimum extent of this AABB in the world space x, y and z axes.
	Vect minPointAABB;
	// Specifies the maximum extent of this AABB in the world space x, y and z axes
	Vect maxPointAABB;

	// GPU connections
	ID3D11Device*			mDevice;
	ID3D11Buffer*           mpVertexBuffer;
	ID3D11Buffer*           mpIndexBuffer;

	void privLoadDataToGPU();
	void privLoadDataFromFile(const char * const _modelName, StandardVertex*& pVerts, 
		Vect*& pVects, int& nverts, TriangleByIndex*& ptlist, int& ntri);

	Vect RitterCenterAndRadius(float& returnRadius, Vect* vectList, int numVect);
	float DistanceBetween(const Vect A, const Vect B) const; 
	Vect getMinOfModel(Vect* vectList, int numVect);
	Vect getMaxOfModel(Vect* vectList, int numVect);

	Vect getXMax(Vect* vectList, int numVect);
	Vect getYMax(Vect* vectList, int numVect);
	Vect getZMax(Vect* vectList, int numVect);
	Vect getXMin(Vect* vectList, int numVect);
	Vect getYMin(Vect* vectList, int numVect);
	Vect getZMin(Vect* vectList, int numVect);

public:
	Model(const Model&) = delete;				// Copy constructor
	Model(Model&&) = delete;                    // Move constructor
	Model& operator=(const Model&) & = delete;  // Copy assignment operator
	Model& operator=(Model&&) & = delete;       // Move assignment operator

	enum PreMadedeModels {
		UnitBox,
		UnitBoxRepeatedTexture,
		UnitPyramid,
		UnitBoxSixFacesTexture,
		UnitSphere
	};

	Model() = delete;
	Model(StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri);
	Model(PreMadedeModels pm);
	Model(const char * const _modelName);

	virtual ~Model();

	void BindVertexIndexBuffers(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
	void RenderMesh(ID3D11DeviceContext* context, int meshnum);

	// Get access
	int GetMeshCount();
	bool ValidMeshNum(int i);

	// actually an array...
	Vect* getVectList();
	int getVectNum()
	{
		return numVerts;
	};

	TriangleByIndex* getTriangleList();
	int getTriNum()
	{
		return numTris;
	};

	Vect& getCenter() { return center; }
	float getRadius() { return radius; }
	Vect& getMinAABB() { return minPointAABB; }
	Vect& getMaxAABB() { return maxPointAABB; }

};



#endif