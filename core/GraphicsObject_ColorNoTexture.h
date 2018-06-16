// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicsObject_ColorNoTexture
#define _GraphicsObject_ColorNoTexture

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class GraphicsObject_ColorNoTexture : public GraphicObject_Base
{
friend class ShaderColor;

public:
	GraphicsObject_ColorNoTexture(const GraphicsObject_ColorNoTexture&) = delete;				 // Copy constructor
	GraphicsObject_ColorNoTexture(GraphicsObject_ColorNoTexture&&) = default;                    // Move constructor
	GraphicsObject_ColorNoTexture& operator=(const GraphicsObject_ColorNoTexture&) & = default;  // Copy assignment operator
	GraphicsObject_ColorNoTexture& operator=(GraphicsObject_ColorNoTexture&&) & = default;       // Move assignment operator
	~GraphicsObject_ColorNoTexture();		  											 // Destructor

	GraphicsObject_ColorNoTexture() = delete;

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicsObject_ColorNoTexture(Model* mod);

private:
	ShaderColor*					pShader;
	
	//Vect							Color;
	Vect*							MeshColors;

	Matrix							World;

};

#endif _GraphicsObject_ColorNoTexture
