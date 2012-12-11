//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/Inc/is_struct_light.fx"

#ifndef VS_INPUT_NODEF
struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float2 UV	  : TEXCOORD;

	float3 Normal	: NORMAL;
	
	#ifdef VS_INPUT_EXT
	VS_INPUT_EXT
	#endif
};
#endif

#ifndef PS_INPUT_NODEF
struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float3 WorldPos	: POSITION0;
	float4 ViewPos	: POSITION1;
    float2 UV		: TEXCOORD0;

	float3 Normal	: NORMAL;
	float3 Binormal	: BINORMAL;
	float3 Tangent	: TANGENT;

	#ifdef PS_INPUT_EXT
	PS_INPUT_EXT
	#endif
};
#endif

#ifndef VS_OUTPUT_NODEF
struct PS_OUTPUT
{
	float4 Screen	: SV_TARGET;
	float4 Depth	: SV_TARGET;
	float4 Normal	: SV_TARGET;
	float4 Light	: SV_TARGET;
};
#endif

#ifndef SHADOW_NODEF
struct GS_INPUT_SHADOW
{
    float4 Pos		: SV_POSITION;
};

struct PS_INPUT_SHADOW
{
	float4 Pos		: SV_POSITION;
};
#endif