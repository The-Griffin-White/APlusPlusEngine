// ModelTools
// Support tools to compute bounding volumes on models
// Ported/adapted from Keenan's FBX Converter code
// Andre Berthiaume, June 2016

#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

class ModelTools
{

public:
	static float CreateUnitBox(StandardVertex *&pVerts, Vect*& pVects, int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center);
	static float CreateUnitBoxRepTexture(StandardVertex *&pVerts, Vect*& pVects, int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center);
	static float CreateUnitBoxSixFacesTexture(StandardVertex *&pVerts, Vect*& pVects, int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center);
	static float CreateUnitPyramid(StandardVertex *&pVerts, Vect*& pVects, int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center);
	static float CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, Vect*& pVects, int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center);
};



#endif _ModelTools