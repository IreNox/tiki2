technique11 basic
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_Main() ) );
        SetPixelShader( CompileShader( ps_5_0, PS_Main() ) );
    }
}