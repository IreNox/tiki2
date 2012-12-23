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

	Unit Units[32];
};

Texture2D rtScreen;
Texture2D rtDepth;

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

	float4 diff = rtScreen.Sample(sam, input.UV);

	for (float i = 0; i < UnitCount; i++)
	{
		float r = (Units[i].Range + 3.14159f) / 2;
		float bDis = distance(Units[i].Position, worldPos.xz) + 3.14159f;
		float dis = bDis / r;
		dis = clamp(dis, 0, 3.14159);

		fog = max(sin(dis) * 1.25, fog);

		if (Units[i].Type == 1.0f)
		{
			dis = bDis - 8;
			dis = clamp(dis * 1.5f, 0, 3.14159);

			diff.b += sin(dis);
		}
	}

	fog = clamp(fog, 0, 1);
	fog = lerp(0.2f, 1, fog);

	diff.rgb *= fog;
	return diff;
}


#include "Data/Effects/Inc/is_technique.fx"