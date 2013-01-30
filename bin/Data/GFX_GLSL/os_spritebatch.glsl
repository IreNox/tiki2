
#version 400

#ifdef TIKI_VS

in vec3 inPos;
in vec2 inUV;
in vec4 inColor;

out vec4 Color;

uniform mat4 SBProjM;

void main()
{
	gl_Position = SBProjM * vec4(inPos, 1.0);
	gl_TexCoord[0] = vec4(inUV, 0, 0);

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

	gl_FragColor = texture(tex, vec2(gl_TexCoord[0])); //* Color
}

#endif