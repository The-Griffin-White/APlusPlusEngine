#include "Terrain.h"
#include "Model.h"
#include "Texture.h"
#include "TerrainModel.h"

#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

#include "Visualizer.h"
#include "PWMathTools.h"

// Collision Iterator
TerrainAreaIterator::TerrainAreaIterator(Terrain* pTr, Collidable* c)
	: tr(pTr), col(c)
{
	end = false;
	// Get the difference between the collidables x/z coordinates and the start of the terrain
	float cRadius = col->GetCollisionBSphere()->GetRadius();
	Vect cCenter = col->GetCollisionBSphere()->GetCenter();
	Vect minPos = cCenter - Vect(cRadius, cRadius, cRadius);
	Vect maxPos = cCenter + Vect(cRadius, cRadius, cRadius);
	tr->pModel->FindMatchingPoint(startX, startZ, minPos);
	tr->pModel->FindMatchingPoint(endX, endZ, maxPos);
	// Set starting coordinate
	int max = tr->TerrainWidth();
	if (startX < 0 || startZ < 0 || startX > max || startZ > max || 
		endX < 0 || endZ < 0 || endX < 0 || endZ < 0)
	{
		end = true;		// out of bounds
	}
	x = startX;
	z = startZ;
}

bool TerrainAreaIterator::End()
{
	return end;
}

TerrainAreaIterator& TerrainAreaIterator::operator++()
{
	++z;
	if (z > endZ)
	{
		z = startZ;
		++x;
	}
	if (x > endX) end = true;
	return *this;
}
TerrainAreaIterator TerrainAreaIterator::operator++(int)
{
	TerrainAreaIterator temp = *this;
	++*this;
	if (x > endX) end = true;
	return temp;
}

Vect TerrainAreaIterator::GetMin()
{
	return tr->cellMin(x, z);
}
Vect TerrainAreaIterator::GetMax()
{
	return tr->cellMax(x, z);
}

// Terrain Stuff
Terrain::Terrain()
{
	pTerrain = nullptr;
}

void Terrain::Initialize(Texture* tex, const char* heightMap, float len, float maxheight, float ytrans, float firstU, float secondU, float firstV, float secondV)
{
	// convert the char* to a wchar_t*
	size_t newsize = strlen(heightMap) + 1;
	wchar_t * heightMapL = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, heightMapL, newsize, heightMap, _TRUNCATE);
	pTerrain = new TerrainObject(heightMapL, len, maxheight, ytrans, firstU, secondU, firstV, secondV);
	pModel = pTerrain->pTerrain;
	pTerrain->SetTexture(tex);
	pTerrain->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100));

	Matrix world = Matrix(IDENTITY);
	pTerrain->SetWorld(world);
}

int Terrain::TerrainWidth()
{
	return pModel->imgWidth;
}

float Terrain::cellMinHeight(const int& x, const int& z)
{
	return pModel->GetMinHeight(x, z);
}

float Terrain::cellMaxHeight(const int& x, const int& z)
{
	return pModel->GetMaxHeight(x, z);
}

Vect Terrain::cellMin(const int& x, const int& z)
{
	return Vect
	( 
		pModel->startX + (pModel->cellWidth * x),
		this->cellMinHeight(z, x), 
		pModel->startZ + (pModel->cellWidth * z)
	);
}

Vect Terrain::cellMax(const int& x, const int& z)
{
	return Vect
	(
		pModel->startX + (pModel->cellWidth * (x + 1)),
		this->cellMaxHeight(z, x),
		pModel->startZ + (pModel->cellWidth * (z + 1))
	);
}

bool Terrain::GetNormal(Collidable* Col, Vect& up)
{
	// Test to see which triangle we are directly over
	Vect cCenter = Col->GetCollisionBSphere()->GetCenter();
	int cX, cZ;
	pModel->FindMatchingPoint(cZ, cX, cCenter);
	if (cX >= 1 && cX <= pModel->imgWidth - 1 && cZ >= 1 && cZ <= pModel->imgWidth - 1)
	{
		// A is the vert at the -x/-z corner, bottom left at starting cam position
		int ourVect;
		ourVect = cX * pModel->imgWidth + cZ;

		Vect A = pModel->cellArray[ourVect].topleft.Pos;
		Vect Anorm = pModel->cellArray[ourVect].topleft.normal;
		Vect v = cCenter - A;
		Vect B, Bnorm, C, Cnorm;

		if (v.X() < v.Z())
		{
			B = pModel->cellArray[ourVect].botleft.Pos;
			Bnorm = pModel->cellArray[ourVect].botleft.normal;
		}
		else
		{
			B = pModel->cellArray[ourVect].topright.Pos;
			Bnorm = pModel->cellArray[ourVect].topright.normal;
		}
		C = pModel->cellArray[ourVect].botright.Pos;
		Cnorm = pModel->cellArray[ourVect].botright.normal;

		float beta, gamma;
		PWMathTools::BarycentricCoordinate(cCenter, A, B, C, beta, gamma);
		up = (Anorm + (beta * (Bnorm - Anorm)) + (gamma * (Cnorm - Bnorm)));
		up.set(up.X(), up.Y(), up.Z(), 0);

		return true;
	}
	return false;
}

bool Terrain::GetHeight(Collidable* Col, float& y)
{
	// Test to see which triangle we are directly over
	Vect cCenter = Col->GetCollisionBSphere()->GetCenter();
	int cX, cZ;
	pModel->FindMatchingPoint(cZ, cX, cCenter);
	if (cX >= 1 && cX <= pModel->imgWidth - 1 && cZ >= 1 && cZ <= pModel->imgWidth - 1)
	{
		// A is the vert at the -x/-z corner, bottom left at starting cam position
		int ourVect;
		ourVect = cX * pModel->imgWidth + cZ;

		Vect A = pModel->cellArray[ourVect].topleft.Pos;
		Vect v = cCenter - A;
		Vect B, C;

		if (v.X() < v.Z())
		{
			B = pModel->cellArray[ourVect].botleft.Pos;
		}
		else
		{
			B = pModel->cellArray[ourVect].topright.Pos;
		}
		C = pModel->cellArray[ourVect].botright.Pos;

		float beta, gamma;
		Vect tmp = PWMathTools::BarycentricCoordinate(cCenter, A, B, C, beta, gamma);
		y = tmp.Y();

		return true;
	}
	return false;
}

bool Terrain::PointUnderCollidable(Collidable* Col, Vect& point)
{
	// Test to see which triangle we are directly over
	Vect cCenter = Col->GetCollisionBSphere()->GetCenter();
	int cX, cZ;
	pModel->FindMatchingPoint(cZ, cX, cCenter);
	if (cX >= 1 && cX <= pModel->imgWidth - 1 && cZ >= 1 && cZ <= pModel->imgWidth - 1)
	{
		// A is the vert at the -x/-z corner, bottom left at starting cam position
		int ourVect;
		ourVect = cX * pModel->imgWidth + cZ;

		Vect A = pModel->cellArray[ourVect].topleft.Pos;
		Vect v = cCenter - A;
		Vect B, C;

		if (v.X() < v.Z())
		{
			B = pModel->cellArray[ourVect].botleft.Pos;
		}
		else
		{
			B = pModel->cellArray[ourVect].topright.Pos;
		}
		C = pModel->cellArray[ourVect].botright.Pos;

		float beta, gamma;
		point = PWMathTools::BarycentricCoordinate(cCenter, A, B, C, beta, gamma);

		return true;
	}
	return false;
}

void Terrain::SetMaterial(const Vect amb, const Vect dif, const Vect spec)
{
	pTerrain->SetMaterial(amb, dif, spec);
}

Terrain::~Terrain()
{
	delete pTerrain;
}

void Terrain::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
}

void Terrain::SceneExit()
{
	Drawable::SubmitDrawDeregistration();
}

void Terrain::Draw()
{
	pTerrain->Render();
}