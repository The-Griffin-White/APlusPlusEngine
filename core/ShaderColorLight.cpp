#include "ShaderColorLight.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include <limits>

#include "SFXManager.h"

#include "Camera.h"
#include "SceneManager.h"

ShaderColorLight::ShaderColorLight()
	: ShaderBase(L"../Assets/Shaders/ColorLight.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
}

ShaderColorLight::~ShaderColorLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}

void ShaderColorLight::ChangeDirectionalLighting()
{
	DirLightData = SFXManager::GetDirectionalLighting();
}
void ShaderColorLight::ChangePointLighting(int n)
{
	assert(n >= 0 && n < POINTARRAY_SIZE);
	PointLightData[n] = SFXManager::GetPointLighting(n);
}
void ShaderColorLight::ChangeSpotLighting(int n)
{
	assert(n >= 0 && n < SPOTARRAY_SIZE);
	SpotLightData[n] = SFXManager::GetSpotLighting(n);
}

void ShaderColorLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderColorLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

void ShaderColorLight::SetPointLightParameters(const int n, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData[n].Light.Ambient = amb;
	PointLightData[n].Light.Diffuse = dif;
	PointLightData[n].Light.Specular = sp;
	PointLightData[n].Position = pos;
	PointLightData[n].Attenuation = att;
	PointLightData[n].Range = r;
}

void ShaderColorLight::SetSpotLightParameters(const int n, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[n].Light.Ambient = amb;
	SpotLightData[n].Light.Diffuse = dif;
	SpotLightData[n].Light.Specular = sp;
	SpotLightData[n].Position = pos;
	SpotLightData[n].Direction = dir;
	SpotLightData[n].Attenuation = att;
	SpotLightData[n].Range = r;
	SpotLightData[n].SpotExp = spotExp;
}

void ShaderColorLight::SendLightParameters( const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	memcpy(dl.PntLight, PointLightData, sizeof(PointLightData));
	memcpy(dl.SptLight, SpotLightData, sizeof(SpotLightData));
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderColorLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderColorLight::SetToContext()
{
	ShaderBase::SetContext();
	ShaderBase::SetToContext_VS_PS_InputLayout();

	Camera* pCam = SceneManager::GetCurrentCamera();
	this->SendCamMatrices(pCam->getViewMatrix(), pCam->getProjMatrix());
	Vect eyePos;
	pCam->getPos(eyePos);
	this->SendLightParameters(eyePos);
	this->SendFogParameters();

	ShaderBase::GetContext()->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	ShaderBase::GetContext()->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	ShaderBase::GetContext()->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	ShaderBase::GetContext()->VSSetConstantBuffers(3, 1, &mpFogParams);

	ShaderBase::GetContext()->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	ShaderBase::GetContext()->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	ShaderBase::GetContext()->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	ShaderBase::GetContext()->PSSetConstantBuffers(3, 1, &mpFogParams);
}