//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

Texture2D tex;

float BlurRange = 2.0f;
float BlurIntensity = 1.0f;

float2 ScreenSize = float2(400, 300);


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PSPP_Blur(PS_INPUT input, float2 pixel, Texture2D tex)
{
	pixel /= ScreenSize;
	pixel *= BlurIntensity; 
	
	float h = BlurRange / 2;
	float w = 0;
	float4 color = (float4)0;
	
	for (float i = 0; i < BlurRange; i++)
	{
		float weight = sin(i / h);
		w += weight;
		
		color += tex.Sample(sam, input.UV + (pixel * (i - h))) * weight;
	}
	color /= w;
	
    return color;
}

float4 PSPP_BlurVertical(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(
		input,
		float2(0, 1),
		tex
	);
}

float4 PSPP_BlurHorizontal(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(
		input,
		float2(1, 0),
		tex
	);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

technique10 tiki10
{
    pass blurVertical10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSPP_BlurVertical() ) );
    }

    pass blurHorizontal10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSPP_BlurHorizontal() ) );
    }
}

technique11 tiki11
{
    pass blurVertical11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurVertical() ) );
    }

    pass blurHorizontal11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurHorizontal() ) );
    }
}