//////////////
// TYPEDEFS //
//////////////
struct Light
{
	float3 Position;
	float3 Direction;
	float3 Color;
	float Range;
};

struct VS_INPUT
{
    float3 Pos	: POSITION;
	float3 UV	: TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos	: SV_POSITION;
	float3 UV	: TEXCOORD0;
};

/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix worldMatrixInverseTranspose;

cbuffer MatrixBuffer : register(b0)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer LightBuffer : register(b1)
{
    float LightsCount;
	float DiffuseIntensity;
	float AmbientIntensity;
	float EmissiveIntensity;

	float4 AmbientColor		: COLOR;
	float4 EmissiveColor	: COLOR;

	Light Lights[32];
};

Texture2D tex;

SamplerState sam : register(s0)
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
	int i = (int)input.UV.z;

	return tex.Sample(sam, input.UV.xy);
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}