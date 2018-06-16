#ifndef _Mirror
#define _Mirror

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include "Vect.h"
#include "Matrix.h"

#include <malloc.h>

class FlatPlane;
class ShaderColor;

class Mirror : public Align16
{
public:
	/// "Offset" used to place the reflected objects slightly offline the base world, to avoid visible clipping in the reflection
	Mirror(const float& scale, const Matrix& world, const Vect& offset, 
		ShaderColor* sh, const Vect& color, const float& alpha, ID3D11Device* dev);

	void MirrorPreliminaries(ID3D11Device* dev);
	~Mirror();

	const Matrix& ReflectMat();
	void MirrorEffectOn(ID3D11DeviceContext* context);
	void MirrorEffectOff(ID3D11DeviceContext* context, ID3D11RasterizerState* FrontFace);
	void MirrorTintEffect(ID3D11DeviceContext* context);

private:
	FlatPlane* pMirror;
	ShaderColor* pMirrorShader;
	Matrix mirrorMat;
	Vect mirrorColor;

	Matrix ReflectionMat;

	ID3D11DepthStencilState* MarkMirrorDSS;
	ID3D11DepthStencilState* DrawReflectionDSS;

	ID3D11RasterizerState* MirrorFrontFaceAsClockWiseRS;

	ID3D11BlendState* NoWriteToRenderTargetBS;
	ID3D11BlendState* TransparentBS;

	Mirror() = delete;	// Don't want this
};

#endif _Mirror