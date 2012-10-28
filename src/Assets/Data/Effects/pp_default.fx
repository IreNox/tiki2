//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

Texture2D rtScreen;
Texture2D rtNormal;
//Texture2D rtDepth;

Texture2D spriteBatch;
Texture2D debugLines;

SamplerState sam 
{    
  AddressU  = CLAMP;
  AddressV = CLAMP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};

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
	float4 bbColor = rtScreen.Sample(sam, input.UV);
	float4 sbColor = spriteBatch.Sample(sam, input.UV);
	float4 dlColor = debugLines.Sample(sam, input.UV);
	float4 alColor = float4(1, 1, 1, 1); //ambientLight.Sample(sam, input.UV);
	float4 color = float4(0, 0, 0, 0);

	if (LightsCount != 0.0f && true)
	{
		float3 termLight = float3(1, 1, 1);

		float3 pixelNormal = rtNormal.Sample(sam, input.UV).xyz;

		for (float i = 0; i < LightsCount; i++)
		{
			float3 lightDir = normalize(Lights[i].Direction);

			float lighting = dot(pixelNormal, lightDir);	
			//lighting *= (Lights[i].Range / dot(lightDir, lightDir));

			termLight += Lights[i].Color * lighting;
		}		

		bbColor.rgb *= termLight;
	}

	color = ((bbColor * alColor) * (1 - dlColor.a)) + dlColor;
	color = (color * (1 - sbColor.a)) + sbColor;

	return color;
}


#include "Data/Effects/IncOS/is_technique.fx"