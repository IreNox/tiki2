//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

struct Unit
{
	float2 Position;
	float Range;
	float Type;
};

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

cbuffer FogOfWar
{
	float UnitCount;
	float3 MapSize;

	Unit Units[128];
};

Texture2D rtScreen;
Texture2D rtDepth;

Texture2D SkillCrosshair;

SamplerState samW
{    
  AddressU  = BORDER;
  AddressV = BORDER;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
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
	float fog = 0;
	float3 worldPos = rtDepth.Sample(sam, input.UV).rgb;

	float3 addc = float3(0, 0, 0);
	float4 diff = rtScreen.Sample(sam, input.UV);
	float4 srcDiff = diff;

	for (float i = 0; i < UnitCount; i++)
	{
		if (Units[i].Type < 2.0f)
		{
			float r = (Units[i].Range + 3.14159f) / 2;
			float bDis = distance(Units[i].Position, worldPos.xz) + 3.14159f;
			float dis = bDis / r;
			dis = clamp(dis, 0, 3.14159);

			fog = max(sin(dis) * 1.25, fog);

			if (Units[i].Type == 1.0f)
			{
				dis = bDis - 4.5f;
				dis = clamp(dis * 4.5f, 0, 3.14159);

				diff.b += sin(dis);
			}
		}
		else
		{
			float3 pos = rtDepth.Sample(sam, Units[i].Position);
			float range = Units[i].Range;

			float2 uv = float2(
				((worldPos.x - pos.x) + (range / 2)) / range,
				((worldPos.z - pos.z) + (range / 2)) / range
			);
			
			float4 color = SkillCrosshair.Sample(samW, uv);

			if (Units[i].Type == 3.0f)
			{
				addc.r += color.rgb * color.a;
			}
			else
			{
				addc.rgb -= color.a;
			}
		}
	}

	fog = clamp(fog, 0, 1);
	fog = lerp(0.2f, 1, fog);

	if (diff.a != 0)
	{
		diff = srcDiff;
	}

	diff.rgb *= fog;
	diff.rgb += addc;
	diff.a = 1;

	return diff;
}

////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////


#include "Data/Effects/Inc/is_technique.fx"
