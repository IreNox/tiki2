
#include "Data/Effects/IncOS/is_states.fx"

technique10 tiki10
{
    pass Geometry10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main() ) );
		SetGeometryShader(  NULL );
        SetPixelShader( CompileShader( ps_4_0, PS_Main() ) );

        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 0 );
        SetRasterizerState( EnableCulling );
    }

    pass StencilShadow10
    {
        SetVertexShader( CompileShader( vs_4_0, VS_Main_Shadow() ) );
		SetGeometryShader( CompileShader( gs_4_0, GS_Main_Shadow() ) );
        SetPixelShader( CompileShader( ps_4_0, PS_Main_Shadow() ) );

        SetBlendState( DisableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( TwoSidedStencil, 1 ); //state, stencilref
        SetRasterizerState( DisableCulling );
    }
}

technique11 tiki11
{
    pass Geometry11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );

        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 0 );
        SetRasterizerState( EnableCulling );
    }

    pass StencilShadow11
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main_Shadow() ) );
		SetGeometryShader( CompileShader( gs_5_0, GS_Main_Shadow() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main_Shadow() ) );

        SetBlendState( DisableFrameBuffer, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( TwoSidedStencil, 1 ); //state, stencilref
        SetRasterizerState( DisableCulling );
    }
}