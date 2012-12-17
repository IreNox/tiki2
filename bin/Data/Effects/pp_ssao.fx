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
Texture2D tDepth;

float2 ScreenSize;
float3 viewDirection;

float scale = 1.0f;
float bias = 0.0f;
float intensity = 1.0f;



#define M_PI 3.14159265f
#define M_2PI 6.28318530f
#define M_PIOVER2 1.570796325f
#define M_PIOVER4 0.785398162f


SamplerState samNearest
{    
    Filter   = MIN_MAG_LINEAR_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float3 getPosition(float2 uv)
{
	return viewDirection * tDepth.Sample(sam, uv).w;
}
float3 getNormal(float2 uv)
{
	return rtNormal.Sample(sam, uv);
}
float2 getRandom(float2 uv)
{
	return tRandom.Sample(samNearest, uv * ScreenSize / 256.0f).xy;
}
float doAmbientOcclusion(float2 coord, float2 uv, float3 p, float3 norm)
{
	float3 diff = getPosition(coord + uv) - p;
	float3 v = normalize(diff);
	float d = length(diff) * scale;
	return max(0.0f , dot(norm , v) - bias) * (1.0 / (1.0 + d) * intensity);
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float3 p = getPosition(input.UV);
	float3 n = getNormal(input.UV);
	float2 rand = getRandom(input.UV);

	float rad = 1.0f / p.z;
	float ao = 0;

	for(float i = 0; i < M_2PI; i += M_PIOVER4)
	{
		float2 coord = (float2(sin(i), cos(i)) / ScreenSize) * 5 * rad;
		coord = reflect(coord, rand);

		ao += doAmbientOcclusion(input.UV, coord * 0.25, p, n);
		ao += doAmbientOcclusion(input.UV, coord * 0.50, p, n);
		ao += doAmbientOcclusion(input.UV, coord * 0.75 , p, n);
		ao += doAmbientOcclusion(input.UV, coord * 1.00, p, n);
	}
	ao /= 32;
	ao = 1 - ao;

	return float4(0.0, 0.0, 0.0, 1.0);
	//return float4(ao.xxx , 1.0);
}


#include "Data/Effects/Inc/is_technique.fx"