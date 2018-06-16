//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------

#pragma pack_matrix( row_major )

cbuffer WVPBuffer : register( b0 )
{
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
}

cbuffer FogData : register(b1)
{
	float FogStart;
	float FogRange;
	float4 FogColor;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR )
{
    VS_OUTPUT output;
    output.Pos = mul( Pos, World);
    output.Pos = mul( output.Pos, View);
    output.Pos = mul( output.Pos, Projection);
    output.Color = Color;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	float4 litColor = input.Color;

	/****************************************************/
	// Fog Demo

	// Compute fog density as function of distance to eye
	float distToEye = length(msEyePos - input.PosMS);
	float FogPercent = saturate((distToEye - FogStart) / FogRange);  // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx

																 // blend litcolor with fog level
																 // C_src = FogColor
																 // C_dst = litColor
																 // C = C_src * fogPercent + C_dst * (1 - fogPercent)
	litColor = lerp(litColor, FogColor, FogPercent);				// See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509618(v=vs.85).aspx

	/****************************************************/
    return litColor;
}
