//////////////
// TYPEDEFS //
//////////////
#include "Data/Effects/IncPP/is_structs.fx"

/////////////
// GLOBALS //
/////////////
#include "Data/Effects/IncPP/is_input.fx"

//Texture2D tex;

//float BlurRange = 2.0f;
//float BlurIntensity = 1.0f;

//float2 ScreenSize = float2(400, 300);

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncPP/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
	float4 color = float4(1, 1, 1, 1);
	color *= 0.25f;
	color.a = 1;

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

BlendState EnableFrameBuffer
{
    BlendEnable[0] = FALSE;
    RenderTargetWriteMask[0] = 0x0F;
};

DepthStencilState RenderNonShadows
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
    
    StencilEnable = true;
    StencilReadMask = 0xFFFFFFFF;
    StencilWriteMask = 0x0;
    
    FrontFaceStencilFunc = Less;
    FrontFaceStencilPass = Keep;
    FrontFaceStencilFail = Zero;
    
    BackFaceStencilFunc = Never;
    BackFaceStencilPass = Zero;
    BackFaceStencilFail = Zero;
};

RasterizerState EnableCulling
{
    CullMode = BACK;
};

technique10 tiki10
{
    pass Shadow10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main() ) );
		SetGeometryShader(  NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Main() ) );

        SetBlendState( EnableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( RenderNonShadows, 0 );
        SetRasterizerState( EnableCulling );
    }
}

technique11 tiki11
{
    pass Shadow11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader(  NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );

        SetBlendState( EnableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( RenderNonShadows, 0 );
        SetRasterizerState( EnableCulling );
    }
}