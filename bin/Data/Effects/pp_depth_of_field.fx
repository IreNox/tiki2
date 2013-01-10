//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

Texture2D rtScene;
Texture2D rtDepth;

float BlurIntensity = 1.5f;

float2 ScreenSize = float2(400, 300);


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PSPP_Blur(PS_INPUT input, float2 pixel)
{
	float depth = rtDepth.Sample(sam, input.UV).a;

	float d2 = 1 - depth;
	float d3 = clamp((d2 - 0.995) * 200, 0, 3.14159f);
	float d4 = clamp(sin(d3) * 32, 2, 32);
	float blurRange = d4;

	pixel /= ScreenSize;
	pixel *= BlurIntensity; 
	
	float h = blurRange / 2;
	float w = 0;
	float4 color = (float4)0;
	
	for (float i = 0; i < blurRange; i++)
	{
		float weight = sin((i / blurRange) * 3.14159f);
		w += weight;
		
		color += rtScene.Sample(sam, input.UV + (pixel * (i - h))) * weight;
	}
	color /= w;
	
    return color;
}

float4 PSPP_BlurVertical(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(input, float2(0, 1));
}

float4 PSPP_BlurHorizontal(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(input,	float2(1, 0));
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

technique11 basic
{
    pass blurVertical
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurVertical() ) );
    }

    pass blurHorizontal
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurHorizontal() ) );
    }
}