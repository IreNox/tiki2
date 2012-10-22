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
    float3 Pos	: POSITION;
	float3 UV	: TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos	: SV_POSITION;
	float3 UV	: TEXCOORD0;
};

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

Texture2D tex;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;    

	output.Pos = float4(input.Pos, 1.0f);
	output.UV = input.UV;
	    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 color = tex.Sample(sam, input.UV.xy);
	//color *= color.a;

	return color;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}