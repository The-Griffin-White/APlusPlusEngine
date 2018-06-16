#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>

#include "MathTools.h"

TerrainModel::TerrainModel(LPCWSTR heightmapFile, float len, float maxheight, float ytrans,
	float firstU, float secondU, float firstV, float secondV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width );	// the image should be square

	size_t side = hgtmap->height;	// number of pixels wide/long
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel

	// ** much work to add below **
	totalWidth = len;
	imgWidth = (int)side;
	numberOfCells = imgWidth * imgWidth;

	int ntri = numberOfCells * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	int nverts = ntri * 3;
	StandardVertex* pVerts = new StandardVertex[nverts];

	cellArray = new CellIndex[numberOfCells];

	float start = -1 * (len / 2);
	startX = start;
	startZ = start;
	cellWidth = (len / imgWidth);
	int vertItr = 0;
	int triItr = 0;

	int cellCounter = 0;

	float nx, ny, nz;

	for (int row = 0; row < imgWidth; ++row)
	{
		for (int col = 0; col < imgWidth; ++col)
		{
			MathTools::TriangleNormal
			(
				start + col * cellWidth,			// topleft
				this->PixelHeight((int)col, (int)row, maxheight, hgtmap, pixel_width, side),
				start + row * cellWidth,
				start + col * cellWidth,			// botleft
				this->PixelHeight((int)col, (int)(row + 1), maxheight, hgtmap, pixel_width, side),
				start + (row + 1) * cellWidth,
				start + (col + 1) * cellWidth,	// botright
				this->PixelHeight((int)(col + 1), (int)(row + 1), maxheight, hgtmap, pixel_width, side),
				start + (row + 1) * cellWidth,
				nx, ny, nz
			);

			pVerts[vertItr].set(start + col * cellWidth,			// topleft
				ytrans + this->PixelHeight((int)col, (int)row, maxheight, hgtmap, pixel_width, side),
				start + row * cellWidth,
				secondU, secondV,
				nx, ny, nz);
			cellArray[cellCounter].topleft = pVerts[vertItr];

			pVerts[vertItr + 1].set(start + col * cellWidth,		// botleft
				ytrans + this->PixelHeight((int)col, (int)(row + 1), maxheight, hgtmap, pixel_width, side),
				start + (row + 1) * cellWidth,
				secondU, firstV,
				nx, ny, nz);
			cellArray[cellCounter].botleft = pVerts[vertItr + 1];

			pVerts[vertItr + 2].set(start + (col + 1) * cellWidth,	// botright
				ytrans + this->PixelHeight((int)(col + 1), (int)(row + 1), maxheight, hgtmap, pixel_width, side),
				start + (row + 1) * cellWidth,
				firstU, firstV,
				nx, ny, nz);
			cellArray[cellCounter].botright = pVerts[vertItr + 2];

			pVerts[vertItr + 3].set(start + (col + 1) * cellWidth,	// topright
				ytrans + this->PixelHeight((int)(col + 1), (int)row, maxheight, hgtmap, pixel_width, side),
				start + row * cellWidth,
				firstU, secondV,
				nx, ny, nz);
			cellArray[cellCounter].topright = pVerts[vertItr + 3];

			++cellCounter;

			pTriList[triItr].set(vertItr, vertItr + 1, vertItr + 2);
			pTriList[triItr + 1].set(vertItr, vertItr + 2, vertItr + 3);

			vertItr += 4;
			triItr += 2;
		}
	}

	//*
	cellCounter = imgWidth;
	vertItr = imgWidth * 4;
	for (int row = 1; row < imgWidth - 1; ++row)
	{
		++cellCounter;
		vertItr += 4;

		for (int col = 1; col < imgWidth - 1; ++col)
		{
			// iterate through each cell to get the 4 vertices
			// get proper cell with cellArray[row * sideInt + col]
				// then use the average of their norm and the surrounding norms
				
			Vect newTopLeftNorm, newBotLeftNorm, newBotRightNorm, newTopRightNorm;

			// put these in their own scope for convenience...
			// vert 1 == topleft
			{
				Vect tlNorm = cellArray[row * imgWidth + col].topleft.normal;
				Vect aboveblNorm = cellArray[(row - 1) * imgWidth + col].botleft.normal;
				Vect lefttrNorm = cellArray[row * imgWidth + (col - 1)].topright.normal;
				Vect aboveleftbrNorm = cellArray[(row - 1) * imgWidth + (col - 1)].botright.normal;

				newTopLeftNorm = tlNorm + aboveblNorm + lefttrNorm + aboveleftbrNorm;
				newTopLeftNorm *= 0.25;
				newTopLeftNorm.set(newTopLeftNorm.X(), newTopLeftNorm.Y(), newTopLeftNorm.Z(), 0);
			}
			// vert 2 == botleft
			{
				Vect blNorm = cellArray[row * imgWidth + col].botleft.normal;
				Vect leftbrNorm = cellArray[row * imgWidth + (col - 1)].botright.normal;
				Vect belowtlNorm = cellArray[(row + 1) * imgWidth + col].topleft.normal;
				Vect belowlefttrNorm = cellArray[(row + 1) * imgWidth + (col - 1)].topright.normal;

				newBotLeftNorm = blNorm + leftbrNorm + belowtlNorm + belowlefttrNorm;
				newBotLeftNorm *= 0.25;
				newBotLeftNorm.set(newBotLeftNorm.X(), newBotLeftNorm.Y(), newBotLeftNorm.Z(), 0);
			}
			// vert 3 == botright
			{
				Vect brNorm = cellArray[row * imgWidth + col].botright.normal;
				Vect rightblNorm = cellArray[row * imgWidth + (col + 1)].botleft.normal;
				Vect belowtrNorm = cellArray[(row + 1) * imgWidth + col].topright.normal;
				Vect belowrighttlNorm = cellArray[(row + 1) * imgWidth + (col + 1)].topleft.normal;

				newBotRightNorm = brNorm + rightblNorm + belowtrNorm + belowrighttlNorm;
				newBotRightNorm *= 0.25;
				newBotRightNorm.set(newBotRightNorm.X(), newBotRightNorm.Y(), newBotRightNorm.Z(), 0);
			}
			// vert 4 == topright
			{
				Vect trNorm = cellArray[row * imgWidth + col].topright.normal;
				Vect abovebrNorm = cellArray[(row - 1) * imgWidth + col].botright.normal;
				Vect righttlNorm = cellArray[row * imgWidth + (col + 1)].botleft.normal;
				Vect aboverightblNorm = cellArray[(row - 1) * imgWidth + (col + 1)].botleft.normal;

				newTopRightNorm = trNorm + abovebrNorm + righttlNorm + aboverightblNorm;
				newTopRightNorm *= 0.25;
				newTopRightNorm.set(newTopRightNorm.X(), newTopRightNorm.Y(), newTopRightNorm.Z(), 0);
			}

			pVerts[vertItr].normal = newTopLeftNorm;
			pVerts[vertItr + 1].normal = newBotLeftNorm;
			pVerts[vertItr + 2].normal = newBotRightNorm;
			pVerts[vertItr + 3].normal = newTopRightNorm;

			vertItr += 4;

			//*

			cellArray[cellCounter].topleft.normal = newTopLeftNorm;
			cellArray[cellCounter].botleft.normal = newBotLeftNorm;
			cellArray[cellCounter].botright.normal = newBotRightNorm;
			cellArray[cellCounter].topright.normal = newTopRightNorm;

			//*/

			++cellCounter;
		}

		++cellCounter;
		vertItr += 4;
	}
	//*/

	pModTerrain = new Model(pVerts, nverts, pTriList, ntri);
}

float TerrainModel::PixelHeight(int x, int z, float maxheight,
					const DirectX::Image* hgtmap, size_t pixel_width, size_t side)
{
	uint8_t h_val = hgtmap->pixels[pixel_width * (z * side + x)];

	int heightInt = (int)h_val;
	float rval; 

	if (heightInt == 0)
		rval = 0;
	else
		rval = maxheight * ((float)h_val / 255.0f);

	return rval;
}

void TerrainModel::FindMatchingPoint(int& x, int& z, const Vect& otherPos) const
{
	// Get the difference between the collidables x/z coordinates and the start of the terrain
	float xDif = otherPos.X() - startX;
	float zDif = otherPos.Z() - startZ;
	// divide by sidelength and multiply by the number of cells per side
	xDif /= totalWidth;
	zDif /= totalWidth;
	xDif *= imgWidth;
	zDif *= imgWidth;
	x = (int)xDif;
	z = (int)zDif;

	if (x < 0 || x > imgWidth)
		x = -1;

	if (z < 0 || z > imgWidth)
		z = -1;
}

float TerrainModel::GetMaxHeight(const int& x, const int& z) const
{
	CellIndex c = cellArray[x * imgWidth + z];

	float max = -1 * std::numeric_limits<float>::infinity();

	// search for max...
	if (c.topleft.Pos.Y() > max) max = c.topleft.Pos.Y();
	if (c.botleft.Pos.Y() > max) max = c.botleft.Pos.Y();
	if (c.botright.Pos.Y() > max) max = c.botright.Pos.Y();
	if (c.topright.Pos.Y() > max) max = c.topright.Pos.Y();

	return max;
}

float TerrainModel::GetMinHeight(const int& x, const int& z) const
{
	CellIndex c = cellArray[x * imgWidth + z];

	float min = std::numeric_limits<float>::infinity();

	// search for min...
	if (c.topleft.Pos.Y() < min) min = c.topleft.Pos.Y();
	if (c.botleft.Pos.Y() < min) min = c.botleft.Pos.Y();
	if (c.botright.Pos.Y() < min) min = c.botright.Pos.Y();
	if (c.topright.Pos.Y() < min) min = c.topright.Pos.Y();

	return min;
}

Vect TerrainModel::GetCellMax(const int& x, const int& z) const
{
	CellIndex c = cellArray[x * imgWidth + z];
	
	float max = -1 * std::numeric_limits<float>::infinity();
	Vect maxVect = Vect(max, max, max);

	// search for max...
	if (c.topleft.Pos.Y() > max) maxVect = c.topleft.Pos;
	if (c.botleft.Pos.Y() > max) maxVect = c.botleft.Pos;
	if (c.botright.Pos.Y() > max) maxVect = c.botright.Pos;
	if (c.topright.Pos.Y() > max) maxVect = c.topright.Pos;

	return maxVect;
}
Vect TerrainModel::GetCellMin(const int& x, const int& z) const
{
	CellIndex c = cellArray[x * imgWidth + z];

	float min = std::numeric_limits<float>::infinity();
	Vect minVect = Vect(min, min, min);

	// search for max...
	if (c.topleft.Pos.Y() < min) minVect = c.topleft.Pos;
	if (c.botleft.Pos.Y() < min) minVect = c.botleft.Pos;
	if (c.botright.Pos.Y() < min) minVect = c.botright.Pos;
	if (c.topright.Pos.Y() < min) minVect = c.topright.Pos;

	return minVect;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	// ?
	// This should be fine?
	pModTerrain->Render(context);
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}