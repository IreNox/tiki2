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
#include "Data/Effects/IncOS/is_defaultshader_vertex.fx"

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
#include "Data/Effects/IncOS/is_defaultshader_pixel.fx"

PS_OUTPUT PS_Main_Cloddy(PS_INPUT input) : SV_TARGET
{
	PS_OUTPUT output = PS_Main(input);
	
	float2 uv = input.WorldPos.xz + float2(1536, 1536);
	uv /= 3072;

	output.Screen = TexDiffuse.Sample(sam, uv);

	return output;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main_Cloddy() ) );
    }
}