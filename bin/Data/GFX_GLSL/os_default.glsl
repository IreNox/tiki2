
#version 140

#ifdef TIKI_VS

in vec3 inPos;
in vec2 inUV;
in vec3 inNormal;

out vec3 Normal;

uniform ObjectData
{
	mat4 WorldM;		// World Matrix
	mat4 WorldMIT;		// World Inverse Transpose Matrix

	uint UseDiffuse;
	uint UseLightMap;
	uint UseNormalMap;
	uint UseSpecularMap;
};

uniform MatrixBuffer
{
    mat4 ViewM;			// View Matrix;
	mat4 ViewIM;		// View Inverse Matrix;
    mat4 ProjectionM;	// Projection Matrix;
};

void main()
{
	gl_Position = vec4(inPos, 1.0);
	gl_Position *= WorldM;
	gl_Position *= ViewM;
	gl_Position *= ProjectionM;

	gl_TexCoord[0] = vec4(
		inUV.x,
		1 - inUV.y,
		0,
		0
	);

	Normal = inNormal;
}

#endif
#ifdef TIKI_PS

in vec3 Normal;

struct Light
{
	vec3 Position;
	vec3 Direction;
	vec4 Color;
	float Range;
};

uniform LightBuffer
{
    float LightsCount;
	float DiffuseIntensity;
	float AmbientIntensity;
	float EmissiveIntensity;

	vec4 AmbientColor;
	vec4 EmissiveColor;

	//float IsDirty;
	//float DefaultShading;
	//float UnusedLightProperties[2];

	Light Lights[32];
};

uniform ObjectData
{
	mat4 WorldM;		// World Matrix
	mat4 WorldMIT;		// World Inverse Transpose Matrix

	uint UseDiffuse;
	uint UseLightMap;
	uint UseNormalMap;
	uint UseSpecularMap;
};

uniform sampler2D TexDiffuse;
uniform sampler2D TexLightMap;
uniform sampler2D TexNormalMap;
uniform sampler2D TexSpecularMap;

void main()
{
	gl_FragData[0] = texture(TexDiffuse, vec2(gl_TexCoord[0]));
	gl_FragData[1] = vec4(Normal, 1);
}

#endif