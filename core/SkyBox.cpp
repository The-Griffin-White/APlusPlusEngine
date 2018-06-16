#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"

SkyBox::SkyBox(const float &scale)
{
	int nverts = 24;
	StandardVertex *pVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex *pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(scale, scale, scale, 0.5f, 0.34f);
	pVerts[vind + 1].set(-scale, scale, scale, 0.75f, 0.34f);
	pVerts[vind + 2].set(-scale, -scale, scale, 0.75f, 0.66f);
	pVerts[vind + 3].set(scale, -scale, scale, 0.5f, 0.66f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.25f, 0.34f);
	pVerts[vind + 1].set(-scale, scale, -scale, 0, 0.34f);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 0.66f);
	pVerts[vind + 3].set(scale, -scale, -scale, 0.25f, 0.66f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.25f, 0.34f);
	pVerts[vind + 1].set(scale, scale, scale, 0.5f, 0.34f);
	pVerts[vind + 2].set(scale, -scale, scale, 0.5f, 0.66f);
	pVerts[vind + 3].set(scale, -scale, -scale, 0.25f, 0.66f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-scale, scale, scale, 0.75f, 0.34f);
	pVerts[vind + 1].set(-scale, scale, -scale, 1, 0.34f);
	pVerts[vind + 2].set(-scale, -scale, -scale, 1, 0.66f);
	pVerts[vind + 3].set(-scale, -scale, scale, 0.75f, 0.66f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.25f, 0.34f);
	pVerts[vind + 1].set(-scale, scale, -scale, 0.25f, 0);
	pVerts[vind + 2].set(-scale, scale, scale, 0.5f, 0);
	pVerts[vind + 3].set(scale, scale, scale, 0.5f, 0.34f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, -scale, scale, 0.5f, 0.67f);
	pVerts[vind + 1].set(-scale, -scale, scale, 0.5f, 1);		// Bot left
	pVerts[vind + 2].set(-scale, -scale, -scale, 0.25f, 1);			// Top left
	pVerts[vind + 3].set(scale, -scale, -scale, 0.25f, 0.67f);			// Top right
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Get normals
	for (int n = 0; n < nverts; n++)
	{
		pVerts[n].normal = pVerts[n].Pos.getNorm();
	}

	pSkyBox = new Model(pVerts, nverts, pTriList, ntri);
}

SkyBox::~SkyBox()
{
	delete pSkyBox;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pSkyBox->Render(context);
}