// FlatPlane.h
// Berthiaume Jan 2017

#ifndef _FlatPlane
#define _FlatPlane

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class FlatPlane 
{
private:
	Model* pPlane;

public:
	static Model* getFlatPlaneModel(float height, float width, float hrep, float vrep);

	FlatPlane(const FlatPlane&) = delete;				// Copy constructor
	FlatPlane(Model&&) = delete;                    // Move constructor
	FlatPlane& operator=(const FlatPlane&) & = delete;  // Copy assignment operator
	FlatPlane& operator=(FlatPlane&&) & = delete;       // Move assignment operator
	~FlatPlane();

	FlatPlane(float size, float hrep, float vrep);
	FlatPlane(float height, float width, float hrep, float vrep);

	Model* getModel() { return pPlane; };

	void Render(ID3D11DeviceContext* context);

};

#endif _FlatPlane
