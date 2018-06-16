#ifndef _GraphicsObject_WireframeConstantColor
#define _GraphicsObject_WireframeConstantColor

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class Texture;

class GraphicsObject_WireframeConstantColor : public GraphicObject_Base
{
	friend class ShaderTexLight;

public:
	GraphicsObject_WireframeConstantColor(const GraphicsObject_WireframeConstantColor&) = delete;				 // Copy constructor
	GraphicsObject_WireframeConstantColor(GraphicsObject_WireframeConstantColor&&) = default;                    // Move constructor
	GraphicsObject_WireframeConstantColor& operator=(const GraphicsObject_WireframeConstantColor&) & = default;  // Copy assignment operator
	GraphicsObject_WireframeConstantColor& operator=(GraphicsObject_WireframeConstantColor&&) & = default;       // Move assignment operator
	~GraphicsObject_WireframeConstantColor();		  											 // Destructor

	GraphicsObject_WireframeConstantColor() = delete;


	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicsObject_WireframeConstantColor(Model* mod);

private:
	ShaderColor*					pShader;
	Vect*							MeshColors;
	Matrix							World;

};

#endif _GraphicObject_Color
