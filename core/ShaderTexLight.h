#ifndef _ShaderTexLight
#define _ShaderTexLight

#include "ShaderBase.h"
#include "Matrix.h"

#include "LightStructs.h"

struct ID3D11Buffer;
struct ID3D11Device;
class Texture;

class ShaderTexLight : public ShaderBase
{
public:
	ShaderTexLight(const ShaderTexLight&) = delete;				 // Copy constructor
	ShaderTexLight(ShaderTexLight&&) = default;                    // Move constructor
	ShaderTexLight& operator=(const ShaderTexLight&) & = default;  // Copy assignment operator
	ShaderTexLight& operator=(ShaderTexLight&&) & = default;       // Move assignment operator
	~ShaderTexLight();		  							         // Destructor

	ShaderTexLight();

	virtual void SetToContext() override;
	virtual void SetToContext2D();

	void SetTextureResourceAndSampler(Texture* tex);
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const int n, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const int n, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	virtual void ChangeDirectionalLighting() override;
	virtual void ChangePointLighting(int) override;
	virtual void ChangeSpotLighting(int) override;

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

private:
	Texture *pTex;

	DirectionalLight DirLightData;

	PointLight PointLightData[POINTARRAY_SIZE];

	SpotLight SpotLightData[SPOTARRAY_SIZE];

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	ID3D11Buffer*  mpBufferLightParams;

};

#endif