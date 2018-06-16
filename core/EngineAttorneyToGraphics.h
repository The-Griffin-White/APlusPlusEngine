#ifndef _EngineAttorneyToGraphics
#define _EngineAttorneyToGraphics

#include "Engine.h"

class EngineAttorneyToGraphics
{
private:
	friend class Model;
	friend class Texture;
	friend class ShaderBase;
	friend class GraphicObject_Base;
	friend class FlatPlane_Object;
	friend class FlatPlane_Object_NoLight;
	friend class SkyBox_Object;
	friend class GraphicsObject_Sprite;
	friend class GraphicsObject_ColorNoTexture;
	friend class GraphicsObject_ColorNoTextureLight;
	friend class GraphicsObject_TextureFlat;
	friend class GraphicsObject_TextureLight;
	friend class GraphicsObject_WireframeConstantColor;
	static ID3D11Device* GetDevice() { return Engine::getDevice(); };
	static ID3D11DeviceContext* GetContext() { return Engine::getContext(); };
	static void SetSolidRender() { Engine::SetSolidRender(); };
	static void SetWireRender() { Engine::SetWireRender(); };
};

#endif