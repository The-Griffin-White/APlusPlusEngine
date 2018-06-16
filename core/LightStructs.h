#ifndef _LightStructs
#define _LightStructs

#include "Vect.h"

#define POINTARRAY_SIZE 100
#define SPOTARRAY_SIZE 50

// structs for lighting storage...
struct Material		// Material
{
	Vect Ambient;
	Vect Diffuse;
	Vect Specular;
};
struct PhongADS		// PhongADS
{
	Vect Ambient;
	Vect Diffuse;
	Vect Specular;
};
struct DirectionalLight	// Directional
{
	PhongADS Light;
	Vect Direction;
};
struct PointLight
{
	PhongADS Light;
	Vect Position;
	Vect Attenuation;
	float Range;
};
struct SpotLight
{
	PhongADS Light;
	Vect Position;
	Vect Attenuation;
	Vect Direction;
	float SpotExp;
	float Range;
};

struct Data_LightParams
{
	DirectionalLight DirLight;
	PointLight PntLight[POINTARRAY_SIZE];
	SpotLight SptLight[SPOTARRAY_SIZE];
	Vect EyePosWorld;
};

#endif _LightStructs