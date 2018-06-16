#ifndef _TerrainObject
#define _TerrainObject

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexLight.h"

class Texture;
class TerrainModel;

class TerrainObject : public GraphicObject_Base
{
	friend class ShaderTexLight;
	friend class Terrain;

public:
	TerrainObject(const TerrainObject&) = delete;				 // Copy constructor
	TerrainObject(TerrainObject&&) = default;                    // Move constructor
	TerrainObject& operator=(const TerrainObject&) & = default;  // Copy assignment operator
	TerrainObject& operator=(TerrainObject&&) & = default;       // Move assignment operator
	~TerrainObject();
	
	TerrainObject() = delete;
	
	void SetTexture(Texture* tex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	TerrainObject(LPCWSTR heightmapFile, float len, float maxheight, float ytrans, 
		float firstU, float secondU, float firstV, float secondV);

private:
	TerrainModel * pTerrain;
	ShaderTexLight * pShader;
	Texture*						pTex;
	Vect							Ambient;
	Vect							Diffuse;
	Vect							Specular;
	Matrix							World;

};

#endif