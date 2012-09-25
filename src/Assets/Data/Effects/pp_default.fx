/////////////
// GLOBALS //
/////////////

Texture2D backBuffer;
Texture2D spriteBatch;
Texture2D debugLines;

SamplerState sam 
{    
  AddressU  = CLAMP;
  AddressV = CLAMP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};

//////////////
// TYPEDEFS //
//////////////
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
	float4 bbColor = backBuffer.Sample(sam, input.UV);
	float4 sbColor = spriteBatch.Sample(sam, input.UV);
	float4 dlColor = debugLines.Sample(sam, input.UV);
	float4 color = float4(0, 0, 0, 0);

	color = (bbColor * (1 - dlColor.a)) + dlColor;
	color = (color * (1 - sbColor.a)) + sbColor;

	//color = bbColor + sbColor + dlColor;

    return color;
}

technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}