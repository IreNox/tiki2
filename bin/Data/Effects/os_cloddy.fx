/////////////
// DEFINES //
/////////////
#define VS_INPUT_NODEF 1
#define PS_INPUT_EXT float4 Color : COLOR;

#define VS_MAIN_USE_NOUV 1
#define VS_MAIN_EXT output.Color = input.Color;

//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncOS/is_structs.fx"

struct VS_INPUT
{
    float3 Pos		: POSITION;
	float3 Normal	: NORMAL;
	float4 Color	: COLOR;
};

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

float2 TerrainSize = float2(512, 512);

SamplerState samC
{    
  AddressU  = WRAP;
  AddressV = WRAP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_getworld_default.fx"
#include "Data/Effects/IncOS/is_defaultshader_vertex.fx"

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 colorTiled(Texture2D tex, float value, float2 uv, float scale)
{
	return tex.Sample(samC, uv * scale) * value;
}

PS_OUTPUT PS_Main_Cloddy(PS_INPUT input) : SV_TARGET
{
	float2 halfSize = TerrainSize / 2;
	float2 uv = input.WorldPos.xz + halfSize;

	float4 color = float4(0, 0, 0, 0);
	color += TexDiffuse.Sample(sam, uv / TerrainSize) * 0.5f; 
	color += colorTiled(TexLightMap, input.Color.r, uv, 0.2);
	color += colorTiled(TexNormalMap, input.Color.g, uv, 0.4);
	color += colorTiled(TexSpecularMap, input.Color.b * 2, uv, 0.1);

	color.g += input.Color.b * 0.1f;

	PS_OUTPUT output = (PS_OUTPUT)0;
	output.Screen.rgb = color.rgb / color.w;
	output.Screen.a = 0.0f;
	output.Normal = float4(input.Normal, 1);
	output.Depth.rgb = input.WorldPos;
	output.Depth.a = input.Pos.z / input.Pos.w;

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_states.fx"

technique10 tiki10
{
    pass p10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Main_Cloddy() ) );

        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 0 );
    }
}

technique11 tiki11
{
    pass p11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main_Cloddy() ) );

        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 0 );
    }
}