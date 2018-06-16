#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"
#include <d3d11.h>

class Model;

class SkyBox : public Align16
{
private:
	Model* pSkyBox;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;                    // Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(const float &scale);

	void Render(ID3D11DeviceContext* context);

};

#endif