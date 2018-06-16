#ifndef _FlatPlane_Object
#define _FlatPlane_Object

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexLight.h"

class Texture;
class FlatPlane;

class FlatPlane_Object : public GraphicObject_Base
{
	friend class ShaderTexLight;

public:
	FlatPlane_Object(const FlatPlane_Object&) = delete;				 // Copy constructor
	FlatPlane_Object(FlatPlane_Object&&) = default;                    // Move constructor
	FlatPlane_Object& operator=(const FlatPlane_Object&) & = default;  // Copy assignment operator
	FlatPlane_Object& operator=(FlatPlane_Object&&) & = default;       // Move assignment operator
	~FlatPlane_Object();

	FlatPlane_Object() = delete;

	void SetTexture(Texture* tex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	FlatPlane_Object(float size, float hrep, float vrep);

private:
	FlatPlane* pPlane;
	ShaderTexLight * pShader;
	Texture*						pTex;
	Vect							Ambient;
	Vect							Diffuse;
	Vect							Specular;
	Matrix							World;

};

#endif