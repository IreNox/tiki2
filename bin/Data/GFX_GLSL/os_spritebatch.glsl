
#version 400

#ifdef TIKI_VS

in vec3 inPos;
in vec2 inUV;
in vec4 inColor;

out vec2 UV;
out vec4 Color;

uniform mat4 SBProjM;

void main()
{
	gl_Position = SBProjM * vec4(inPos, 1.0);
	
	UV = inUV;
	Color = inColor;
}

#endif
#ifdef TIKI_PS

in vec4 Color;

uniform float value;
uniform sampler2D tex;

void main()
{
	float v = value;

	gl_FragColor = texture(tex, UV); //* Color
}

#endif