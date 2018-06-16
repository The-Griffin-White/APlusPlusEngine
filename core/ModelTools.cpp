#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"

#include <cmath>
#include "MathTools.h"

/// Creates the unit box centered at the origin
float ModelTools::CreateUnitBox(StandardVertex *&pVerts, Vect*& pVects, int& nverts, 
	TriangleByIndex *&pTriList, int& ntri, Vect& center)
{
	center = Vect(0, 0, 0, 1);

	nverts = 8;
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	pVects[0].set(-0.5f, -0.5f, -0.5f);
	pVects[1].set(-0.5f, +0.5f, -0.5f);
	pVects[2].set(+0.5f, +0.5f, -0.5f);
	pVects[3].set(+0.5f, -0.5f, -0.5f);
	pVects[4].set(-0.5f, -0.5f, +0.5f);
	pVects[5].set(-0.5f, +0.5f, +0.5f);
	pVects[6].set(+0.5f, +0.5f, +0.5f);
	pVects[7].set(+0.5f, -0.5f, +0.5f);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);

	return 0.5f;
}

float ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, Vect*& pVects, int& nverts, 
	TriangleByIndex *&pTriList, int& ntri, Vect& center)
{
	center = Vect(0, 0, 0, 1);

	nverts = 24;
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, 0.5f);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(0.5f, 0.5f, 0.5f);
	pVects[vind + 2].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(-0.5f, -0.5f, 0.5f);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, 0.5f, 0.5f);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	return 0.5f;
}

float ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex *&pVerts, Vect*& pVects, int& nverts, 
	TriangleByIndex *&pTriList, int& ntri, Vect& center)
{
	center = Vect(0, 0, 0, 1);

	nverts = 24;
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];


	/*
	Coordinates
	:
	//	Fwd: Topleft = [0.25f, 0.375f] TopRight = [0.25f, 0.625f] BotLeft = [0, 0.375f] BotRight = [0, 0.625f]
	*/


	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, 0.5f);

	//	bck: Topleft = [0.25f, 0.625f] TopRight = [0.25f, 0.375f] BotLeft = [0.5f, 0.625f] BotRight = [0.5f, 0.375f]
	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	//	lft: Topleft = [0.25f, 0.625f] TopRight = [0.5f, 0.625f] BotLeft = [0.25f, 0.875f] BotRight = [0.5f, 0.875f]
	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(0.5f, 0.5f, 0.5f);
	pVects[vind + 2].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	//	rht: Topleft = [0.5f, 0.375f] TopRight = [0.25f, 0.375f] BotLeft = [0.5f, 0.125f] BotRight = [0.25f, 0.125f]
	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(-0.5f, -0.5f, 0.5f);

	//	top: Topleft = [0.5f, 0.375f] TopRight = [0.5f, 0.625f] BotLeft = [0.25f, 0.375f] BotRight = [0.25f, 0.625f]
	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.375f, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.625f, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.625f, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.375f, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, 0.5f, -0.5f);
	pVects[vind + 1].set(-0.5f, 0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, 0.5f, 0.5f);
	pVects[vind + 3].set(0.5f, 0.5f, 0.5f);

	//	bot: Topleft = [1.0f, 0.375f] TopRight = [1.0f, 0.625f] BotLeft = [0.75f, 0.375f] BotRight = [0.75f, 0.625f]
	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1.0f, 0.625f, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1.0f, 0.375f, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	return 0.5f;
}

float ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, Vect*& pVects, int& nverts, 
	TriangleByIndex *&pTriList, int& ntri, Vect& center)
{
	center = Vect(0, 0, 0, 1);

	nverts = 18;
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	float nx;
	float ny;
	float nz;

	// Front
	int vind = 0;
	int tind = 0;
	MathTools::TriangleNormal(0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, nx, ny, nz);

	pVerts[vind].set(0.0f, 0.5f, 0.0f, 0.5f, 0, nx, ny, nz);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 1, nx, ny, nz);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 1, 1, nx, ny, nz);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	pVects[vind].set(0.0f, 0.5f, 0.0f);
	pVects[vind + 1].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 2].set(0.5f, -0.5f, 0.5f);

	// Back
	vind += 3;
	tind += 1;
	MathTools::TriangleNormal(0.0f, 0.5f, 0.0f, 0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, nx, ny, nz);

	pVerts[vind].set(0.0f, 0.5f, 0.0f, 0.5f, 0, nx, ny, nz);
	pVerts[vind + 1].set(0.5f, -0.5f, -0.5f, 0, 1, nx, ny, nz);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, nx, ny, nz);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	pVects[vind].set(0.0f, 0.5f, 0.0f);
	pVects[vind + 1].set(0.5f, -0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);

	// Left
	vind += 3;
	tind += 1;
	MathTools::TriangleNormal(0.0f, 0.5f, 0.0f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, nx, ny, nz);

	pVerts[vind].set(0.0f, 0.5f, 0.0f, 0.5f, 0, nx, ny, nz);
	pVerts[vind + 1].set(-0.5f, -0.5f, -0.5f, 0, 1, nx, ny, nz);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 1, 1, nx, ny, nz);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	pVects[vind].set(0.0f, 0.5f, 0.0f);
	pVects[vind + 1].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, 0.5f);

	// Right
	vind += 3;
	tind += 1;
	MathTools::TriangleNormal(0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, nx, ny, nz);

	pVerts[vind].set(0.0f, 0.5f, 0.0f, 0.5f, 0, nx, ny, nz);
	pVerts[vind + 1].set(0.5f, -0.5f, 0.5f, 0, 1, nx, ny, nz);
	pVerts[vind + 2].set(0.5f, -0.5f, -0.5f, 1, 1, nx, ny, nz);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	pVects[vind].set(0.0f, 0.5f, 0.0f);
	pVects[vind + 1].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 2].set(0.5f, -0.5f, -0.5f);

	// Bottom
	vind += 3;
	tind += 1;
	MathTools::TriangleNormal(0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, nx, ny, nz);

	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, nx, ny, nz);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, nx, ny, nz);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, nx, ny, nz);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, nx, ny, nz);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	pVects[vind].set(0.5f, -0.5f, 0.5f);
	pVects[vind + 1].set(-0.5f, -0.5f, 0.5f);
	pVects[vind + 2].set(-0.5f, -0.5f, -0.5f);
	pVects[vind + 3].set(0.5f, -0.5f, -0.5f);

	return 0.5f;
}

float ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, Vect*& pVects, 
	int& nverts, TriangleByIndex *&pTriList, int& ntri, Vect& center)
{
	center = Vect(0, 0, 0, 1);
	//  first vertices

	nverts = (hslice + 1) * vslice + 2;
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];

	const float _pi = 3.1415927f;
	const float _2pi = _pi * 2.0f;

	const Vect poleColor = Colors::White;
	const Vect equatorColor = Colors::Blue;
	float radius = 1.0f;

	float a1, a2, sin1, sin2, cos1, cos2;

	pVerts[0].set(0.0f, radius, 0.0f, 0, 0);
	pVects[0].set(0.0f, radius, 0.0f);
	for (int lat = 0; lat < hslice; lat++)
	{
		a1 = _pi * (float)(lat + 1) / (float)(hslice + 1);
		sin1 = sinf(a1);
		cos1 = cosf(a1);

		for (int lon = 0; lon <= vslice; lon++)
		{
			a2 = _2pi * (float)(lon == vslice ? 0 : lon) / vslice;
			sin2 = sinf(a2);
			cos2 = cosf(a2);

			pVerts[lon + lat * (vslice + 1) + 1].set(radius * (sin1 * cos2), radius * cos1, radius * (sin1 * sin2), 0, 0);
			pVects[lon + lat * (vslice + 1) + 1].set(radius * (sin1 * cos2), radius * cos1, radius * (sin1 * sin2));
		}
	}
	pVerts[nverts - 1].set(0.0f, -radius, 0.0f, 0, 0);
	pVects[nverts - 1].set(0.0f, -radius, 0.0f);

	// Get normals
	for (int n = 0; n < nverts; n++)
	{
		pVerts[n].normal = pVerts[n].Pos.getNorm();
	}

	// Get UVs
	pVerts[0].u = 1;
	pVerts[0].v = 0;
	pVerts[nverts - 1].u = 0;
	pVerts[nverts - 1].v = 0;
	for (int lat = 0; lat < hslice; lat++)
	{
		for (int lon = 0; lon <= vslice; lon++)
		{
			pVerts[lon + lat * (vslice + 1) + 1].u = (float)lon / vslice;
			pVerts[lon + lat * (vslice + 1) + 1].v = 1.0f - (float)(lat + 1) / (hslice + 1);
		}
	}

	//  now triangles
//	ntri = nverts * 2;
	ntri = (vslice * 2) + ((vslice * 2) * (hslice - 1));
	pTriList = new TriangleByIndex[ntri];
	//*
	//Top Cap
	int i = 0;
	for (int lon = 0; lon < vslice; lon++)
	{
		pTriList[i++].set(lon + 2, lon + 1, 0);
	}

	//Middle
	for (int lat = 0; lat < hslice - 1; lat++)
	{
		for (int lon = 0; lon < vslice; lon++)
		{
			int current = lon + lat * (vslice + 1) + 1;
			int next = current + vslice + 1;

			pTriList[i++].set(current, current + 1, next + 1);

			pTriList[i++].set(current, next + 1, next);
		}
	}

	//Bottom Cap
	for (int lon = 0; lon < vslice; lon++)
	{
		pTriList[i++].set(nverts - 1, nverts - (lon + 2) - 1, nverts - (lon + 1) - 1);
	}
	//*/

	return radius;
}
