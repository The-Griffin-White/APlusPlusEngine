#ifndef _FlatPlane_Object_NoLight
#define _FlatPlane_Object_NoLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexture.h"

class Texture;
class FlatPlane;

class FlatPlane_Object_NoLight : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	FlatPlane_Object_NoLight(const FlatPlane_Object_NoLight&) = delete;				 // Copy constructor
	FlatPlane_Object_NoLight(FlatPlane_Object_NoLight&&) = default;                    // Move constructor
	FlatPlane_Object_NoLight& operator=(const FlatPlane_Object_NoLight&) & = default;  // Copy assignment operator
	FlatPlane_Object_NoLight& operator=(FlatPlane_Object_NoLight&&) & = default;       // Move assignment operator
	~FlatPlane_Object_NoLight();

	FlatPlane_Object_NoLight() = delete;

	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	FlatPlane_Object_NoLight(float size, float hrep, float vrep);

private:
	FlatPlane * pPlane;
	ShaderTexture * pShader;
	Texture*						pTex;
	Vect							Ambient;
	Vect							Diffuse;
	Vect							Specular;
	Matrix							World;

};

#endif _FlatPlane_Object_NoLight