//////////////
// TYPEDEFS //
//////////////
struct Light
{
	float3 Position;
	float3 Direction;
	float4 Color;
	float Range;
};

struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float2 UV	  : TEXCOORD;

	float3 Normal	: NORMAL;
	float3 Binormal	: BINORMAL;
	float3 Tangent	: TANGENT;
};

struct PS_INPUT
{
    float4 Pos		: SV_POSITION;
	float3 WorldPos	: POSITION0;
	float4 DepthPos	: POSITION1;
    float2 UV		: TEXCOORD0;

	float3 Normal	: NORMAL;
	float3 Binormal	: BINORMAL;
	float3 Tangent	: TANGENT;
};

struct PS_OUTPUT
{
	float4 Screen	: SV_TARGET;
	float4 Depth	: SV_TARGET;
	float4 Normal	: SV_TARGET;
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

Texture2D tex; // : register(t0);

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
    output.DepthPos = output.Pos;

	output.Normal = normalize(mul(input.Normal, worldMatrixInverseTranspose));
    output.UV = input.UV;
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
PS_OUTPUT PS_Main(PS_INPUT input) : SV_TARGET
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 termDiffuse = tex.Sample(sam, input.UV) * DiffuseIntensity;
	float3 termAmbient = AmbientColor.rgb * AmbientIntensity;
	float3 termEmissive = EmissiveColor.rgb * EmissiveIntensity;
	float3 termLight = float3(1, 1, 1);

	//lighting *= (LightRange / dot(input.LightDir, input.LightDir));
	
	if (LightsCount != 0.0f)
	{
		for (float i = 0; i < LightsCount; i++)
		{
			float3 lightDir = normalize(Lights[i].Direction);

			float lighting = dot(input.Normal, lightDir);	
			//lighting *= (Lights[i].Range / dot(lightDir, lightDir));

			termLight += Lights[i].Color * lighting;
		}		
	
		termDiffuse.rgb *= termLight;
	}
	
	output.Screen = float4(
		saturate(termDiffuse.rgb + termAmbient + termEmissive),
		termDiffuse.a
	);

	output.Depth.rgb = 1 - (input.DepthPos.z / 1000.0f); //input.DepthPos.w;
	output.Depth.a = 1.0f;
	output.Normal = float4(input.Normal, 1.0f);

	return output;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}