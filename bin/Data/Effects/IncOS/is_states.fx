BlendState NoBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = FALSE;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState DisableFrameBuffer
{
    BlendEnable[0] = FALSE;
    RenderTargetWriteMask[0] = 0x0;
};

DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

DepthStencilState TwoSidedStencil
{
    DepthEnable = true;
    DepthWriteMask = ZERO;
    DepthFunc = Less;
    
    StencilEnable = true;
    StencilReadMask = 0xFFFFFFFF;
    StencilWriteMask = 0xFFFFFFFF;
    
    BackFaceStencilFunc = Always;
    BackFaceStencilDepthFail = Incr;
    BackFaceStencilPass = Keep;
    BackFaceStencilFail = Keep;
    
    FrontFaceStencilFunc = Always;
    FrontFaceStencilDepthFail = Decr;
    FrontFaceStencilPass = Keep;
    FrontFaceStencilFail = Keep;
};

RasterizerState EnableCulling
{
    CullMode = BACK;
};

RasterizerState DisableCulling
{
    CullMode = NONE;
};
