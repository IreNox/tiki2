/////////////
// DEFINES //
/////////////
#define VS_INPUT_NODEF 1
#define PS_INPUT_NODEF 1

//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncOS/is_structs.fx"

struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float4 Color  : COLOR;
};

struct PS_INPUT
{
    float4 Pos	  : SV_POSITION;
	float4 Color  : COLOR;
};

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(input.Pos, 1.0f);
    //output.Pos = mul(output.Pos, WorldM);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
    
	output.Color = input.Color;
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	return input.Color;
}

#include "Data/Effects/IncOS/is_technique.fx"