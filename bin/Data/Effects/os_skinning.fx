//////////////
// DEFINES  //
//////////////

#ifndef VS_INPUT_EXT
#define VS_INPUT_EXT float4  SkinningWeights    : BLENDWEIGHT; float4  SkinningIndices    : BLENDINDICES;
#endif

//////////////
// TYPEDEFS //
//////////////

#include "Data/Effects/IncOS/is_structs.fx"

/////////////
// GLOBALS //
/////////////

cbuffer SkinMatrices 
{
	matrix bones[128];
};

#include "Data/Effects/IncOS/is_input.fx"


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_getworld_skinning.fx"
#include "Data/Effects/IncOS/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

PS_OUTPUT PS_Main(PS_INPUT input) : SV_TARGET
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 termDiffuse = (float4)0.8f;
	
	if (UseDiffuse)
	{
		termDiffuse = TexDiffuse.Sample(sam, input.UV) * DiffuseIntensity;
	}

	float3 bumpedNormal = input.Normal;		
	if (UseNormalMap)
	{
		float3 normalSample = 2 * TexNormalMap.Sample(sam, input.UV) - 1;
		//float3x3 TBN = float3x3(input.Tangent, input.Binormal, input.Normal);
		
		//bumpedNormal = normalize(mul(normalSample, TBN));
		bumpedNormal = normalize(input.Normal + normalSample.x * input.Tangent + normalSample.y * input.Binormal);
	}

	if (UseSpecularMap)
	{
		float specularIntensity = 1.0f;
		float specularity = 25.0f;

		float3 H = normalize(input.ViewPos - Lights[0].Direction);
		termDiffuse += specularIntensity * TexSpecularMap.Sample(sam, input.UV) * pow(saturate(dot(H, bumpedNormal)), specularity);
	}

	if (UseLightMap)
	{
		output.Light = TexLightMap.Sample(sam, input.UV);
	}

	output.Screen = termDiffuse;
	output.Depth.rgb = input.WorldPos;
	output.Depth.a = input.Pos.z / input.Pos.w; // / 1000.0f);
	output.Normal = float4(bumpedNormal, 1.0f);
	
	return output;
}

//#include "Data/Effects/IncOS/is_defaultshader_pixel.fx"


////////////////////////////////////////////////////////////////////////////////
// Shadow
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_defaultshader_shadow.fx"


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_technique.fx"
