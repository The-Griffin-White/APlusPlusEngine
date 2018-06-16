#pragma pack_matrix( row_major )

Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);

// Material properties
struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;  // Hack: w holds the specular power
};

// Light properties
struct PhongADS
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};

// Directional Light Data
struct DirectionalLight
{
	PhongADS LightInt;
	float4 Direction;
};

// Point Light data
struct PointLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation;
	float Range;
};

// Spot light data
struct SpotLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation;
	float4 Direction;
	float SpotExp;
	float Range;
};

//  Constant Buffers
cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

cbuffer InstanceData : register(b1)
{
	float4x4 World;
	float4x4 WorldInv;
	Material Mater;
};

// ******* Shader operations

struct VS_INPUT
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;

	output.Pos = mul(input.pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Tex = input.tex;

	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 litColor = mainTexture.Sample(aSampler, input.Tex);

	return litColor;
}
