#ifndef _SkyBox_Object
#define _SkyBox_Object

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexLight.h"

class Texture;
class SkyBox;

class SkyBox_Object : public GraphicObject_Base
{
	friend class ShaderTexLight;

public:
	SkyBox_Object(const SkyBox_Object&) = delete;				 // Copy constructor
	SkyBox_Object(SkyBox_Object&&) = default;                    // Move constructor
	SkyBox_Object& operator=(const SkyBox_Object&) & = default;  // Copy assignment operator
	SkyBox_Object& operator=(SkyBox_Object&&) & = default;       // Move assignment operator
	~SkyBox_Object();

	SkyBox_Object() = delete;

	void SetTexture(Texture* tex);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	SkyBox_Object(float scale, ShaderTexLight* shader);

private:
	SkyBox * pSkyBox;
	ShaderTexLight * pShader;
	Texture*						pTex;
	Vect							Ambient;
	Vect							Diffuse;
	Vect							Specular;
	Matrix							World;

};

#endif