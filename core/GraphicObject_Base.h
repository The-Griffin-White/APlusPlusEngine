// GraphicObject
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Base
#define _GraphicObject_Base

#include "Matrix.h"

class Model;
class ShaderMeshData;
struct ID3D11DeviceContext;
struct ID3D11Device;
class ShaderBase;


class GraphicObject_Base : public Align16
{
public:
	GraphicObject_Base(const GraphicObject_Base&) = delete;				   // Copy constructor
	GraphicObject_Base(GraphicObject_Base&&) = default;                    // Move constructor
	GraphicObject_Base& operator=(const GraphicObject_Base&) & = default;  // Copy assignment operator
	GraphicObject_Base& operator=(GraphicObject_Base&&) & = default;       // Move assignment operator
	virtual ~GraphicObject_Base() = default;		  					   // Destructor
	GraphicObject_Base();

	void SetModel(Model* mod);
	virtual void Render() = 0;

	Model* getModel()
	{
		return pModel;
	};

protected:
	ID3D11Device* getDevice();

	Model* pModel;

};

#endif _GraphicObject_Base
