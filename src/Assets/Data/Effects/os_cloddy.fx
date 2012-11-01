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

//Texture2DArray 

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
	
	output.Screen = input.Color;

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