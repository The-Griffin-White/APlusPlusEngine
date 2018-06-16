#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include "Model.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{
	friend class TerrainObject;

private:
	struct CellIndex : public Align16
	{
		StandardVertex topleft;
		StandardVertex botleft;
		StandardVertex botright;
		StandardVertex topright;
	};

	Model* pModTerrain;

	float PixelHeight(int x, int z, float maxheight,
		const DirectX::Image* hgtmap, size_t pixel_width, size_t side);

public:
	TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, 
		float firstU, float secondU, float firstV, float secondV);
	~TerrainModel();
	void FindMatchingPoint(int& x, int& z, const Vect& otherPos) const;
	float GetMaxHeight(const int& x, const int& z) const;
	float GetMinHeight(const int& x, const int& z) const;
	Vect GetCellMax(const int& x, const int& z) const;
	Vect GetCellMin(const int& x, const int& z) const;

	void Render(ID3D11DeviceContext* context);

	CellIndex* cellArray;
	int numberOfCells;
	int imgWidth;
	float totalWidth;
	float cellWidth;
	float startX;
	float startZ;
};



#endif _TerrainModel