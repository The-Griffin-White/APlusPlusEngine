#include "GraphicObject_Base.h"
#include "Model.h"
#include <assert.h>
#include "EngineAttorneyToGraphics.h"

GraphicObject_Base::GraphicObject_Base()
{
	pModel = nullptr;
}


void GraphicObject_Base::SetModel(Model* mod)
{
	pModel = mod;
}


ID3D11Device* GraphicObject_Base::getDevice()
{
	return EngineAttorneyToGraphics::GetDevice();
}