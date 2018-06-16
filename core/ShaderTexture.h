#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(const ShaderTexture&) = delete;				 // Copy constructor
	ShaderTexture(ShaderTexture&&) = default;                    // Move constructor
	ShaderTexture& operator=(const ShaderTexture&) & = default;  // Copy assignment operator
	ShaderTexture& operator=(ShaderTexture&&) & = default;       // Move assignment operator
	~ShaderTexture();		  							         // Destructor

	ShaderTexture();

	virtual void SetToContext() override;
	virtual void SetToContext2D();

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorld(const Matrix& world);

private:
	Texture* pTex;

	ID3D11Buffer*	mpcbViewProj;

	struct ViewProjData
	{
		Matrix mView;
		Matrix mProjection;
	};

	ID3D11Buffer*	mpcbWorld;

	struct WorldData
	{
		Matrix World;
		// The texture might change too, but that's done through mpTextureRV
	};
};

#endif _ShaderColor
