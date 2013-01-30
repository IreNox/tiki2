struct VSInput
{
    vec3 Pos;
    vec2 UV;
    vec4 Color;
};

struct VSOutput
{
    vec2 UV;                                                                 
    vec4 Color;
};
			 
uniform mat4 SBProjM;
uniform sampler2D tex;
                                                                                    
shader VSmain(in vec3 Pos, in vec2 UV, in vec4 Color, out VSOutput VSout)                                                                         
{
    gl_Position		= SBProjM * vec4(Pos, 1.0);
    VSout.UV		= UV;                                                         
    VSout.Color		= Color;
}
                                                                                            
shader FSmain(in VSOutput FSin, out vec4 FragColor)
{                                    
    FragColor = FSin.Color; // * texture(tex, FSin.UV);
}

program tiki
{
    vs(430)=VSmain();
    fs(430)=FSmain();
};