#ifndef _GraphicsObject_Sprite
#define _GraphicsObject_Sprite

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "Texture.h"

class ShaderTexLight;
class ShaderTexture;

struct Rect
{
	Rect(float _x, float _y, float _width, float _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}

	float x;
	float y;
	float width;
	float height;
};

class GraphicsObject_Sprite : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicsObject_Sprite(const GraphicsObject_Sprite&) = delete;				 // Copy constructor
	GraphicsObject_Sprite(GraphicsObject_Sprite&&) = default;                    // Move constructor
	GraphicsObject_Sprite& operator=(const GraphicsObject_Sprite&) & = default;  // Copy assignment operator
	GraphicsObject_Sprite& operator=(GraphicsObject_Sprite&&) & = default;       // Move assignment operator
	~GraphicsObject_Sprite();		  											 // Destructor

	GraphicsObject_Sprite();
	GraphicsObject_Sprite(Rect* _rect);

	void SetTexture(Texture* tex);
	void SetWorld(const Matrix& m);
	void UpdateRect(float height, float width);
	virtual void Render() override;

private:
	ShaderTexture *					pShader;
	Texture *						pTex;
	Rect *							rect;

	Matrix							World;
	Matrix							spriteSpace;
};

#endif _GraphicsObject_Sprite