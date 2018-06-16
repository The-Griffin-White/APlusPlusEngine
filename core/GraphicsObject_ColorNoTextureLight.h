#ifndef _GraphicsObject_ColorNoTextureLight
#define _GraphicsObject_ColorNoTextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class GraphicsObject_ColorNoTextureLight : public GraphicObject_Base
{
	friend class ShaderColorLight;

public:
	GraphicsObject_ColorNoTextureLight(const GraphicsObject_ColorNoTextureLight&) = delete;				 // Copy constructor
	GraphicsObject_ColorNoTextureLight(GraphicsObject_ColorNoTextureLight&&) = default;                    // Move constructor
	GraphicsObject_ColorNoTextureLight& operator=(const GraphicsObject_ColorNoTextureLight&) & = default;  // Copy assignment operator
	GraphicsObject_ColorNoTextureLight& operator=(GraphicsObject_ColorNoTextureLight&&) & = default;       // Move assignment operator
	~GraphicsObject_ColorNoTextureLight();		  											 // Destructor

	GraphicsObject_ColorNoTextureLight() = delete;

	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicsObject_ColorNoTextureLight(Model* mod);

private:
	ShaderColorLight*				pShader;
	Vect*							Ambient;
	Vect*							Diffuse;
	Vect*							Specular;
	Matrix							World;

};

#endif _GraphicsObject_ColorNoTextureLight
