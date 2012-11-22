//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/Inc/is_struct_light.fx"

struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float2 UV	  : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 UV  : TEXCOORD0;
};