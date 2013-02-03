
#version 400

#ifdef TIKI_VS

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec4 inColor;

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

in vec2 UV;
in vec4 Color;

layout(location = 0) out vec4 outColor;

uniform float value;
uniform sampler2D tex;

void main()
{
	float v = value;

	outColor = texture(tex, UV); //* Color
}

#endif