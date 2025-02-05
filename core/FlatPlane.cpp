#include "FlatPlane.h"
#include "Model.h"
#include "d3dUtil.h"

Model* FlatPlane::getFlatPlaneModel(float height, float width, float hrep, float vrep)
{
	int nverts = 4;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float h = height * .5f;
	float w = width * .5f;

	pVerts[0].set(-w, -h, 0, hrep, vrep, 0, 1, 0);
	pVerts[1].set(-w, h, 0, hrep, 0, 0, 1, 0);
	pVerts[2].set(w, h, 0, 0, 0, 0, 1, 0);
	pVerts[3].set(w, -h, 0, 0, vrep, 0, 1, 0);

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	return new Model(pVerts, nverts, pTriList, ntri);
}

FlatPlane::FlatPlane(float size, float hrep, float vrep)
{
	int nverts = 4;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float c = size / 2;

	pVerts[0].set(-c, 0, -c, hrep, vrep, 0, 1, 0);
	pVerts[1].set(-c, 0,  c, hrep, 0, 0, 1, 0);
	pVerts[2].set( c, 0,  c, 0, 0, 0, 1, 0);
	pVerts[3].set( c, 0, -c, 0, vrep, 0, 1, 0);
	
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	pPlane = new Model(pVerts, nverts, pTriList, ntri);
	//pPlane = new Model( dev, Model::PreMadedeModels::UnitSphere);
}

FlatPlane::FlatPlane(float height, float width, float hrep, float vrep)
{
	int nverts = 4;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float h = height * .5f;
	float w = width * .5f;

	pVerts[0].set(-w, -h, 0, hrep, vrep, 0, 1, 0);
	pVerts[1].set(-w, h, 0, hrep, 0, 0, 1, 0);
	pVerts[2].set(w, h, 0, 0, 0, 0, 1, 0);
	pVerts[3].set(w, -h, 0, 0, vrep, 0, 1, 0);

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	pPlane = new Model(pVerts, nverts, pTriList, ntri);
}

FlatPlane::~FlatPlane()
{
	delete pPlane;
}

void FlatPlane::Render(ID3D11DeviceContext* context)
{
	pPlane->Render(context);
}