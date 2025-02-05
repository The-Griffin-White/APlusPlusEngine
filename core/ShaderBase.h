// ShaderBase
// AB, June 2016

#ifndef _ShaderBase
#define _ShaderBase

#include <d3dcommon.h>
#include "Matrix.h"
#include <string>

struct ID3D11Buffer;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11DeviceContext;
struct D3D11_INPUT_ELEMENT_DESC;

class ShaderBase : public Align16
{
private:
	// Store these pointers to avoid passing them in every method
	ID3D11Device*			mDevice;
	ID3D11DeviceContext*	mContext;

	// Actual objects managed by this class
	ID3D11VertexShader*     mpVertexShader;
	ID3D11PixelShader*      mpPixelShader;
	ID3D11InputLayout*      mpVertexLayout;

	// Needed for building shaders
	ID3DBlob*				pVSBlob;
	ID3DBlob*				pPSBlob;

	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	void privBuildShaders(WCHAR* filename, LPCSTR vsModel, LPCSTR psModel);


protected:
	ID3D11Device* GetDevice(); 

	ShaderBase(WCHAR* filename, LPCSTR vsModel = "vs_4_0", LPCSTR psModel = "ps_4_0");
	void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layoutdesc, UINT size);
	void SetContext();
	void SetToContext_VS_PS_InputLayout();

	struct Fog
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	Fog FogData;

	struct Fog_Params
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	ID3D11Buffer*  mpFogParams;

public:
	ID3D11DeviceContext * GetContext();

	ShaderBase(const ShaderBase&) = delete;				  // Copy constructor
	ShaderBase(ShaderBase&&) = delete;                    // Move constructor
	ShaderBase& operator=(const ShaderBase&) & = delete;  // Copy assignment operator
	ShaderBase& operator=(ShaderBase&&) & = delete;       // Move assignment operator
	ShaderBase() = delete;
	virtual ~ShaderBase();

	void SetFogParameters(const float& fogstart, const float& fogrange, const Vect& fogcolor);
	void SetDisableFog();
	void SendFogParameters();

	virtual void ChangeDirectionalLighting() {};
	virtual void ChangePointLighting(int) {};
	virtual void ChangeSpotLighting(int) {};

	virtual void SetToContext() = 0;
};


#endif _ShaderBase