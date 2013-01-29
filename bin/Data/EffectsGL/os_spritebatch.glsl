struct VSInput
{
    vec3 Pos;
    vec2 UV;
    vec4 Color;
};

interface VSOutput
{
    vec2 UV;                                                                 
    vec4 Color;
};
			 
uniform mat4 SBProjM;
uniform sampler2D tex;
                                                                                    
shader VSmain(in VSInput VSin, out VSOutput VSout)                                                                         
{
    gl_Position		= SBProjM * vec4(VSin.Pos, 1.0);
    VSout.UV		= VSin.UV;                                                         
    VSout.Color		= VSin.Color;
}
                                                                                            
shader FSmain(in VSOutput FSin, out vec4 FragColor)
{                                    
    FragColor = texture(tex, FSin.UV) * FSin.Color;
}

program tiki
{
    vs(330)=VSmain();
    fs(330)=FSmain();
};