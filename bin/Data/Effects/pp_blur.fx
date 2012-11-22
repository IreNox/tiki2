/////////////
// GLOBALS //
/////////////

Texture2D tex;

SamplerState sam 
{    
  AddressU  = CLAMP;
  AddressV = CLAMP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};

float BlurRange = 16.0f;
float BlurIntensity = 1.0f;

float2 ScreenSize = float2(400, 300);

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

float4 PSPP_Blur(PS_INPUT input, float2 pixel, Texture2D tex)
{
	pixel /= ScreenSize;
	pixel *= BlurIntensity; 
	
	float h = BlurRange / 2;
	float w = 0;
	float4 color = (float4)0;
	
	for (float i = 0; i < BlurRange; i++)
	{
		float weight = sin(i / h);
		w += weight;
		
		color += tex.Sample(sam, input.UV + (pixel * (i - h))) * weight;
	}
	color /= w;
	
    return color;
}

float4 PSPP_BlurVertical(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(
		input,
		float2(0, 1),
		tex
	);
}

float4 PSPP_BlurHorizontal(PS_INPUT input) : SV_TARGET 
{	
	return PSPP_Blur(
		input,
		float2(1, 0),
		tex
	);
}

technique11 basic
{
    pass blurVertical
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurVertical() ) );
    }

    pass blurHorizontal
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPP_BlurHorizontal() ) );
    }
}