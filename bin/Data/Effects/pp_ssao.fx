//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

Texture2D tRandom;
//Texture2D<float> tLinDepth;
Texture2D rtNormal;

float2 ScreenSize;

#define M_PI 3.14159265f
#define M_2PI 6.28318530f
#define M_PIOVER2 1.570796325f

SamplerState samNearest
{    
    Filter   = MIN_MAG_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float3 sN = rtNormal.Sample(sam, input.UV).xyz;

	float ao = 0;

	for (float i = 0; i < M_2PI; i += M_PIOVER2)
	{
		float2 t = (float2(sin(i), cos(i)) / ScreenSize) * 5;
		float3 sNP = rtNormal.Sample(sam, input.UV + t).xyz;

		t = (float2(sin(-i), cos(-i)) / ScreenSize) * 5;
		float3 sNM = rtNormal.Sample(sam, input.UV + t).xyz;

		ao += 1 - saturate(dot(sNP,sNM)/length(sN));
		ao += 1 - saturate(dot(sNP,sN)/length(sN));
		ao += 1 - saturate(dot(sNM,sN)/length(sN));
	}

	ao = 1 - ao;

	return float4(ao.xxx, 1);
}


#include "Data/Effects/Inc/is_technique.fx"