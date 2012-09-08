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
    float3 Pos	  : POSITION;
	float4 Color  : COLOR;
};

struct PS_INPUT
{
    float4 Pos	  : SV_POSITION;
	float4 Color  : COLOR;
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

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;    

	output.Pos = float4(input.Pos, 1.0f);
    output.Pos = mul(output.Pos, worldMatrix);
    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    
	output.Color = input.Color;
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	return input.Color;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}