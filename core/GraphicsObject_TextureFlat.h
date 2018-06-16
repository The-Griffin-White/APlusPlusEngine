#ifndef _GraphicsObject_TextureFlat
#define _GraphicsObject_TextureFlat

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class Texture;

class GraphicsObject_TextureFlat : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicsObject_TextureFlat(const GraphicsObject_TextureFlat&) = delete;				 // Copy constructor
	GraphicsObject_TextureFlat(GraphicsObject_TextureFlat&&) = default;                    // Move constructor
	GraphicsObject_TextureFlat& operator=(const GraphicsObject_TextureFlat&) & = default;  // Copy assignment operator
	GraphicsObject_TextureFlat& operator=(GraphicsObject_TextureFlat&&) & = default;       // Move assignment operator
	~GraphicsObject_TextureFlat();		  											 // Destructor

	GraphicsObject_TextureFlat() = delete;

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, const int& meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicsObject_TextureFlat(Model* mod);

private:
	ShaderTexture *					pShader;
	Texture**						pTex;
	Matrix							World;

};

#endif _GraphicObject_Color