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
	
	float light = 1.0f;
	float4 color = input.Color;

	if (LightsCount != 0.0f && false)
	{
		for (float i = 0; i < LightsCount; i++)
		{
			float3 lightDir = normalize(Lights[i].Direction); // - input.WorldPos

			float lighting = dot(input.Normal, lightDir);	
			//lighting *= (Lights[i].Range / dot(lightDir, lightDir));

			light += lighting;
		}

		color.rgb *= light;
	}

	output.Screen =  color;

	//output.Depth.rgb = 1.0f - (input.DepthPos.z / 1000.0f);
	//output.Depth.a = 1.0f;
	//output.Normal = float4(input.Normal, 1.0f);

	return output;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main_Cloddy() ) );
    }
}