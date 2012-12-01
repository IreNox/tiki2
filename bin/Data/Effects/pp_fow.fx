//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

struct Unit
{
	float3 Position;
	float Range;
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
	float fog = 1;
	float3 worldPos = rtDepth.Sample(sam, input.UV).rgb;

	//float msHalf = MapSize.x / 2;

	//fog += (MapSize.x * 0.66f) + worldPos.x;
	//fog -= (msHalf - worldPos.x / 256);

	for (float i = 0; i < UnitCount; i++)
	{
		float dis = distance(Units[i].Position.xz, worldPos.xz);

		if (dis < Units[i].Range) fog = 0;
		//fog += dis / 2000; //;
	}	

	fog = clamp(fog, 0, 1);
	float4 diff = rtScreen.Sample(sam, input.UV);
	float4 grey = float4((diff.r + diff.g + diff.b).xxx * 0.15f, 1);

	return (diff * (1 - fog)) + (grey * fog);
}


#include "Data/Effects/Inc/is_technique.fx"