#include <assert.h>
#include "File.h"
#include "Model.h"
#include "ModelTools.h"
#include "d3dUtil.h"
#include "AzulFileHdr.h"
#include "MeshSeparator.h"
#include "EngineAttorneyToGraphics.h"
#include <limits>

Model::Model(StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri)
	: mDevice(EngineAttorneyToGraphics::GetDevice())
{
	assert(nverts > 0);
	assert(ntri > 0);

	// Copy Data
	numVerts = nverts;
	pStdVerts = new StandardVertex[numVerts];
	pVectList = new Vect[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		pStdVerts[i] = pVerts[i];
		pVectList[i].set(pStdVerts[i].Pos);
	}
	numTris = ntri;
	pTriList = new TriangleByIndex[numTris];
	for (int i = 0; i < numTris; i++)
	{
		pTriList[i] = ptlist[i];
	}

	privLoadDataToGPU();
}

Model::Model(const char * const _modelName)
	: mDevice(EngineAttorneyToGraphics::GetDevice())
{
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	center = RitterCenterAndRadius(radius, pVectList, numVerts);
	minPointAABB = getMinOfModel(pVectList, numVerts);
	maxPointAABB = getMaxOfModel(pVectList, numVerts);

	privLoadDataFromFile(_modelName, pStdVerts, pVectList, numVerts, pTriList, numTris);
	privLoadDataToGPU();
}

Model::Model(Model::PreMadedeModels pm)
	: mDevice(EngineAttorneyToGraphics::GetDevice())
{
	pStdVerts = nullptr;
	pVectList = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	switch (pm)
	{
	case UnitBox:
		radius = ModelTools::CreateUnitBox(pStdVerts, pVectList, numVerts, pTriList, numTris, center);
		break;
	case UnitBoxRepeatedTexture:
		radius = ModelTools::CreateUnitBoxRepTexture(pStdVerts, pVectList, numVerts, pTriList, numTris, center);
		break;
	case UnitBoxSixFacesTexture:
		radius = ModelTools::CreateUnitBoxSixFacesTexture(pStdVerts, pVectList, numVerts, pTriList, numTris, center);
		break;
	case UnitPyramid:
		radius = ModelTools::CreateUnitPyramid(pStdVerts, pVectList, numVerts, pTriList, numTris, center);
		break;
	case UnitSphere:
		radius = ModelTools::CreateUnitSphere(12, 12, pStdVerts, pVectList, numVerts, pTriList, numTris, center);
		break;
	default:
		assert(false && "Invalid option");
	}

	center = RitterCenterAndRadius(radius, pVectList, numVerts);
	minPointAABB = getMinOfModel(pVectList, numVerts);
	maxPointAABB = getMaxOfModel(pVectList, numVerts);

	privLoadDataToGPU();
}



Model::~Model()
{
	delete[] pTriList;
	delete[] pStdVerts;

	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer);
}

void Model::privLoadDataFromFile(const char * const _modelName, StandardVertex*& pVerts, Vect*& pVects, int& nverts, TriangleByIndex*& ptlist, int& ntri)
{
	// Read from file
	FileHandle fh;
	FileError  ferror;

	ferror = File::open(fh, _modelName, FILE_READ);
	assert(ferror == FILE_SUCCESS);

	// GEt the file format for the data
	AzulFileHdr  azulFileHdr;

	// **** Overly complicated detour Part 1:  The vertex data in the file is packed efficiently
	// whereas our StandardVertex is not. Something I shall fix form the start next time.
	// For time time: we will read in the data into a temp array and then manually copy the data into
	// the StandardVertex array. 

	struct VertexStride_VUN
	{
		float x;    // Vert - V
		float y;
		float z;

		float u;    // UV tex coor - U
		float v;

		float txt;	// texture trickery 

		float nx;   // Norm verts - N
		float ny;
		float nz;

		float r;
		float g;
		float b;

		void set(float _x, float _y, float _z,
			float _u, float _v,
			float _nx, float _ny, float _nz,
			float _txt = 0,
			float _r = 1, float _g = 1, float _b = 1)
		{
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
			nx = _nx;
			ny = _ny;
			nz = _nz;

			txt = _txt;
			r = _r;
			g = _g;
			b = _b;
		}

	};

	// ******************


	// Read the header
	ferror = File::read(fh, &azulFileHdr, sizeof(AzulFileHdr));
	assert(ferror == FILE_SUCCESS);

	// create the vertex buffer
	nverts = azulFileHdr.numVerts;
	VertexStride_VUN* pTmpVerts = new VertexStride_VUN[nverts];

	// load the verts
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.vertBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, pTmpVerts, nverts * sizeof(VertexStride_VUN));
	assert(ferror == FILE_SUCCESS);

	// create the triLists buffer
	ntri = azulFileHdr.numTriangles;
	ptlist = new TriangleByIndex[ntri];

	// load the triList
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.triangleListBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, ptlist, ntri * sizeof(TriangleByIndex));
	assert(ferror == FILE_SUCCESS);

	// close
	ferror = File::close(fh);
	assert(ferror == FILE_SUCCESS);

	// **** Overly complicated detour Part 2: now we copy the vertex data into our StandardVertex
	pVerts = new StandardVertex[nverts];
	pVects = new Vect[nverts];
	StandardVertex* v;
	VertexStride_VUN* tmp;
	for (int i = 0; i < nverts; i++)
	{
		tmp = &(pTmpVerts[i]);
		v = &(pVerts[i]);
		v->set(tmp->x, tmp->y, tmp->z, tmp->u, tmp->v, tmp->nx, tmp->ny, tmp->nz, tmp->r, tmp->g, tmp->b, (int) tmp->txt);
		pVects[i].set(tmp->x, tmp->y, tmp->z, 1);
	}

	delete[] pTmpVerts;

	center = RitterCenterAndRadius(radius, pVectList, numVerts);
	minPointAABB = getMinOfModel(pVectList, numVerts);
	maxPointAABB = getMaxOfModel(pVectList, numVerts);
	
	// *************************

}

void  Model::privLoadDataToGPU()
{
	// Extract mesh information
	meshes = new MeshSeparator(pStdVerts, numVerts, pTriList, numTris);

	// Vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StandardVertex) * numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pStdVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TriangleByIndex) * numTris;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = pTriList;
	hr = mDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));

}

bool Model::ValidMeshNum(int meshnum)
{
	return (meshnum >= 0) && (meshnum < GetMeshCount());
}

int Model::GetMeshCount()
{
	return meshes->GetMeshCount();
}

void  Model::BindVertexIndexBuffers(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(StandardVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void Model::Render(ID3D11DeviceContext* context)
{
	BindVertexIndexBuffers(context);
	context->DrawIndexed(numTris * 3, 0, 0); 
}

void Model::RenderMesh(ID3D11DeviceContext* context, int meshnum)
{
	assert(ValidMeshNum(meshnum));

	int tricount, trioffset;
	meshes->GetMeshTriCountAndOffset(meshnum, tricount, trioffset);

	context->DrawIndexed(tricount * 3, trioffset * 3, 0);
}

Vect* Model::getVectList()
{
	return pVectList;
}

TriangleByIndex* Model::getTriangleList()
{
	return pTriList;
}

Vect Model::RitterCenterAndRadius(float& returnRadius, Vect* vectList, int numVect)
{
	// Get two far points...
	Vect Xmax = getXMax(vectList, numVect);
	Vect Xmin = getXMin(vectList, numVect);
	Vect Ymax = getYMax(vectList, numVect);
	Vect Ymin = getYMin(vectList, numVect);
	Vect Zmax = getZMax(vectList, numVect);
	Vect Zmin = getZMin(vectList, numVect);

	// pick the farthest apart points, then set up the center and radius
	float Xdiam = DistanceBetween(Xmax, Xmin);
	float Ydiam = DistanceBetween(Ymax, Ymin);
	float Zdiam = DistanceBetween(Zmax, Zmin);
	float diam;
	Vect cntr;

	if (Xdiam > Ydiam && Xdiam > Zdiam)
	{
		diam = Xdiam;
		cntr = Vect((Xmax.X() + Xmin.X()) * 0.5f, (Xmax.Y() + Xmin.Y()) * 0.5f, (Xmax.Z() + Xmin.Z())  * 0.5f);
	}
	else if (Ydiam > Xdiam && Ydiam > Zdiam)
	{
		diam = Ydiam;
		cntr = Vect((Ymax.X() + Ymin.X()) * 0.5f, (Ymax.Y() + Ymin.Y()) * 0.5f, (Ymax.Z() + Ymin.Z())  * 0.5f);
	}
	else if (Zdiam > Xdiam && Zdiam > Ydiam)
	{
		diam = Zdiam;
		cntr = Vect((Zmax.X() + Zmin.X()) * 0.5f, (Zmax.Y() + Zmin.Y()) * 0.5f, (Zmax.Z() + Zmin.Z())  * 0.5f);
	}
	else
	{
		diam = Xdiam;
		cntr = Vect((Xmax.X() + Xmin.X()) * 0.5f, (Xmax.Y() + Xmin.Y()) * 0.5f, (Xmax.Z() + Xmin.Z())  * 0.5f);
	}

	float rad = diam * 0.5f;

	float dist;
	for (int i = 0; i < numVect; ++i)
	{
		dist = DistanceBetween(vectList[i], cntr);
		if (dist > rad)
		{
			// draw a line through the current center and to the edge
			rad = (dist + rad) * 0.5f;
			cntr = cntr + ((dist - rad) / dist) * (vectList[i] - cntr);
		}
	}

	returnRadius = rad;
	return cntr;
}

float Model::DistanceBetween(const Vect A, const Vect B) const
{
	return
		fabs
		(
			sqrtf(
			((A.X() - B.X()) * (A.X() - B.X()))
				+ ((A.Y() - B.Y()) * (A.Y() - B.Y()))
				+ ((A.Z() - B.Z()) * (A.Z() - B.Z()))
			)
		);
}

Vect Model::getXMax(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect max = Vect(-inf, -inf, -inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if above max
		if (tmp.X() > max.X())
		{
			max = tmp;
		}
	}

	return max;
}
Vect Model::getYMax(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect max = Vect(-inf, -inf, -inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if above max
		if (tmp.Y() > max.Y())
		{
			max = tmp;
		}
	}

	return max;
}
Vect Model::getZMax(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect max = Vect(-inf, -inf, -inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if above max
		if (tmp.Z() > max.Z())
		{
			max = tmp;
		}
	}

	return max;
}
Vect Model::getXMin(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect min = Vect(inf, inf, inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if below min
		if (tmp.X() < min.X())
		{
			min = tmp;
		}
	}

	return min;
}
Vect Model::getYMin(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect min = Vect(inf, inf, inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if below min
		if (tmp.Y() < min.Y())
		{
			min = tmp;
		}
	}

	return min;
}
Vect Model::getZMin(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect min = Vect(inf, inf, inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if below min
		if (tmp.Z() < min.Z())
		{
			min = tmp;
		}
	}

	return min;
}

Vect Model::getMinOfModel(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect min = Vect(inf, inf, inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if below min
		if (tmp.X() < min.X())
		{
			min.X() = tmp.X();
		}
		if (tmp.Y() < min.Y())
		{
			min.Y() = tmp.Y();
		}
		if (tmp.Z() < min.Z())
		{
			min.Z() = tmp.Z();
		}
	}

	return min;
}
Vect Model::getMaxOfModel(Vect* vectList, int numVect)
{
	float inf = std::numeric_limits<float>::infinity();

	Vect max = Vect(-inf, -inf, -inf);

	Vect tmp;

	for (int i = 0; i < numVect; ++i)
	{
		tmp = vectList[i];
		// if statements galore, i guess...
		// check if above max
		if (tmp.X() > max.X())
		{
			max.X() = tmp.X();
		}
		if (tmp.Y() > max.Y())
		{
			max.Y() = tmp.Y();
		}
		if (tmp.Z() > max.Z())
		{
			max.Z() = tmp.Z();
		}
	}

	return max;
}
