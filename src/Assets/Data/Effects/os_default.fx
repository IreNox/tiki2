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
	float3 Normal : NORMAL;
	float2 UV	  : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float3 WorldPos	: POSITION0;
	float3 Normal	: NORMAL;
    float2 UV		: TEXCOORD0;
};

/////////////
// GLOBALS //
/////////////
matrix worldMatrix;

cbuffer MatrixBuffer : register(b0)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer LightBuffer : register(b1)
{
    int LightsCount;

	Light Lights[32];

	float DiffuseIntensity;
	float AmbientIntensity;
	float EmissiveIntensity;

	float4 AmbientColor		: COLOR;
	float4 EmissiveColor	: COLOR;
};

Texture2D tex : register(t0);

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
    output.Pos = mul(output.Pos, worldMatrix);
	output.WorldPos = output.Pos.xyz;

    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    
	output.Normal = input.Normal;
    output.UV = input.UV;
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 termDiffuse = tex.Sample(sam, input.UV) * DiffuseIntensity;
	float4 termAmbient = AmbientColor * AmbientIntensity;
	float4 termEmissive = EmissiveColor * EmissiveIntensity;
	float3 termLight = float3(0, 0, 0);

	//lighting *= (LightRange / dot(input.LightDir, input.LightDir));
	
	for (int i = 0; i < LightsCount; i++)
	{
		float lighting = dot(
			input.Normal,
			normalize(Lights[i].Position - input.WorldPos)
		);

		termLight += Lights[i].Color * lighting;
	}

	termDiffuse.rbg *= termLight.rgb;

	return saturate(termDiffuse + termAmbient + termEmissive);
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}