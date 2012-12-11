//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

Texture2D rtDepth;
Texture2D rtLight;
Texture2D rtNormal;
Texture2D rtScreen;
Texture2D rtShadow;
Texture2D rtInterface;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 sceneColor = rtScreen.Sample(sam, input.UV);
	float4 shadowColor = rtShadow.Sample(sam, input.UV);
	float4 lightColor = rtLight.Sample(sam, input.UV);
	float4 interfaceColor = rtInterface.Sample(sam, input.UV);
	float4 ambientColor = float4(1, 1, 1, 1); //ambientLight.Sample(sam, input.UV);

	float4 color = sceneColor;

	if (LightsCount != 0.0f)
	{
		float3 termLight = float3(1, 1, 1);

		float3 pixelPos = rtDepth.Sample(sam, input.UV).xyz;
		float3 pixelNormal = rtNormal.Sample(sam, input.UV).xyz;

		for (float i = 0; i < LightsCount; i++)
		{
			float3 lightDir = normalize(Lights[i].Position - pixelPos);

			float lighting = dot(pixelNormal, lightDir);	
			//lighting *= (Lights[i].Range / dot(lightDir, lightDir));

			termLight += Lights[i].Color * lighting;
		}		

		color.rgb *= termLight;
	}
	color *= shadowColor;
	color *= ambientColor;
	color += lightColor;

	color = (color * (1 - interfaceColor.a)) + interfaceColor;
	color.a = 1;

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

technique11 basic
{
    pass FinalScreen
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader(  NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );

		SetDepthStencilState( DisableDepth, 0 );
    }
}