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
    float3 Pos		: POSITION;
	float3 UV		: TEXCOORD0;
	float4 Color	: COLOR;
};

struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float3 UV		: TEXCOORD0;
	float4 Color	: COLOR;
};

matrix SBProjM;

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

float value;

Texture2D tex;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;    

	output.Pos = float4(input.Pos, 1.0f);
	//output.Pos = mul(output.Pos, spLocalM);
	//output.Pos = mul(output.Pos, spWorldM);
	//output.Pos = mul(output.Pos, spViewM);
	output.Pos = mul(output.Pos, SBProjM);
	output.UV = input.UV;
	output.Color = input.Color;
	    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 color = input.Color;

	float val = (value * 6.28318f) - 3.14159f;
	float angle = atan2(input.UV.y - 0.5f, input.UV.x - 0.5f);
	
	if (val != 0 && angle <= val)
	{
		color.rgb -= 0.4;
	}
	
	return saturate(tex.Sample(sam, input.UV.xy) * color);
}


#include "Data/Effects/Inc/is_technique.fx"