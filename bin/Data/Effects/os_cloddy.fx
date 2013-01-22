/////////////
// DEFINES //
/////////////
#define VS_INPUT_EXT float4 Color : COLOR;
#define PS_INPUT_EXT float4 Color : COLOR;

#define VS_MAIN_EXT output.Color = input.Color;

//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncOS/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

float2 TerrainSize;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_getworld_default.fx"
#include "Data/Effects/IncOS/is_defaultshader_vertex.fx"

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_defaultshader_pixel.fx"

PS_OUTPUT PS_Main_Cloddy(PS_INPUT input) : SV_TARGET
{
	PS_OUTPUT output = PS_Main(input);

	float2 halfSize = TerrainSize / 2;

	float2 uv = input.WorldPos.xz + halfSize;
	uv /= TerrainSize;

	output.Screen = TexDiffuse.Sample(sam, uv);
	output.Screen.a = 0.0f;

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