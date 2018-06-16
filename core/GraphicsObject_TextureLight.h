#ifndef _GraphicsObject_TextureLight
#define _GraphicsObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class Texture;

class GraphicsObject_TextureLight : public GraphicObject_Base
{
	friend class ShaderTexLight;

public:
	GraphicsObject_TextureLight(const GraphicsObject_TextureLight&) = delete;				 // Copy constructor
	GraphicsObject_TextureLight(GraphicsObject_TextureLight&&) = default;                    // Move constructor
	GraphicsObject_TextureLight& operator=(const GraphicsObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicsObject_TextureLight& operator=(GraphicsObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicsObject_TextureLight();		  											 // Destructor

	GraphicsObject_TextureLight() = delete;

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, const int& meshnum);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicsObject_TextureLight(Model* mod);

private:
	ShaderTexLight*					pShader;
	Texture**						pTex;
	Vect*							Ambient;
	Vect*							Diffuse;
	Vect*							Specular;
	Matrix							World;

};

#endif _GraphicObject_Color
