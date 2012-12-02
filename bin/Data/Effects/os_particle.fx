/////////////
// DEFINES //
/////////////
#define VS_INPUT_NODEF 1
#define PS_INPUT_NODEF 1

//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncOS/is_structs.fx"

struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float4 Color  : COLOR;
	float3 ScaleRot	: TEXCOORD0;
};

struct GS_INPUT
{
    float4 Pos		: POSITION;
	float4 Color	: COLOR;
	float3 ScaleRot	: TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float4 Color	: COLOR;
	float2 UV		: TEXCOORD0;
};

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncOS/is_input.fx"

Texture2D tex;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
GS_INPUT VS_Main(VS_INPUT input)
{
    GS_INPUT output = (GS_INPUT)0;

	output.Pos = mul(float4(input.Pos, 1.0f), WorldM);    
	output.Color = input.Color;
	output.ScaleRot = input.ScaleRot;
    
    return output;
}


////////////////////////////////////////////////////////////////////////////////
// Geometry Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_particle_gs_point.fx"
#include "Data/Effects/IncOS/is_particle_gs_linelist.fx"
//#include "Data/Effects/IncOS/is_particle_gs_linestrip.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	input.Color.a = 0.5f;

	return tex.Sample(sam, input.UV) * input.Color;
}

technique11 Particle
{
    pass Particle_PointList
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( CompileShader( gs_5_0, GS_Main_Point() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }

    pass Particle_LineList
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( CompileShader( gs_5_0, GS_Main_LineList() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }

  //  pass Particle_LineStrip
  //  {
  //      SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		//SetGeometryShader( CompileShader( gs_5_0, GS_Main_Point() ) );
  //      SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
  //  }
}