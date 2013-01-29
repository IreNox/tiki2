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
	float2 UV		: TEXCOORD0;
	float4 Color	: COLOR;
};

struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float2 UV		: TEXCOORD0;
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

	if (value > 0)
	{
		if (angle >= val)
		{
			color.rgb -= 0.4;
		}
	}
	else if (value < 0)
	{
		float a = 0;
		angle += val;
	
		a += clamp(cos(angle) - 0.25f, 0, 1) / 1.5f;
		a += clamp(cos(angle + 2.0943f) - 0.25f, 0, 1) / 1.5f;
		a += clamp(cos(angle + 4.1888f) - 0.25f, 0, 1) / 1.5f;
		
		color.rgb -= a;
	}
	
	if (!(input.UV.x == -1.0f && input.UV.y == -1.0f))
	{
		color = tex.Sample(sam, input.UV) * color;
	}

	return color;
}


#include "Data/Effects/Inc/is_technique.fx"