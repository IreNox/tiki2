
#version 400

#ifdef TIKI_VS

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;

out vec2 UV;

out vec3 Normal;
out vec3 Tangent;
out vec3 Binormal;

out vec3 WorldPos;
out vec3 ViewPos;
out vec4 ProjPos;

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

	WorldPos = gl_Position.xyz;
	ViewPos = normalize(ViewIM[3] - gl_Position).xyz;

	gl_Position *= ViewM;
	gl_Position *= ProjectionM;
	ProjPos = gl_Position;

	UV = vec2(inUV.x, 1 - inUV.y);

	mat3 world = mat3(WorldM);
	Normal = normalize(inNormal * world);

	vec3 c1 = cross(Normal, vec3(0.0, 0.0, 1.0)); 
	vec3 c2 = cross(Normal, vec3(0.0, 1.0, 0.0)); 

	Tangent = normalize(length(c1) > length(c2) ? c1 : c2);
    Binormal = normalize(cross(Normal, Tangent));
}

#endif
#ifdef TIKI_PS

in vec2 UV;

in vec3 Normal;
in vec3 Tangent;
in vec3 Binormal;

in vec3 WorldPos;
in vec3 ViewPos;
in vec4 ProjPos;

layout(location = 0) out vec4 outDiffuse;
layout(location = 1) out vec4 outDepth;
layout(location = 2) out vec4 outNormal;
layout(location = 3) out vec4 outLight;

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
	vec4 termDiffuse = vec4(0.8, 0.8, 0.8, 1);
	
	if (true)
	{
		termDiffuse = texture(TexSpecularMap, UV) * DiffuseIntensity;
	}

	vec3 bumpedNormal = Normal;		
	if (true)
	{
		vec3 normalSample = 2 * texture(TexNormalMap, UV).xyz - 1;
		//float3x3 TBN = float3x3(input.Tangent, input.Binormal, input.Normal);
		
		//bumpedNormal = normalize(mul(normalSample, TBN));
		bumpedNormal = normalize(Normal + normalSample.x * Tangent + normalSample.y * Binormal);
	}

	if (true)
	{
		float specularIntensity = 1.0f;
		float specularity = 25.0f;

		vec3 H = normalize(ViewPos - Lights[0].Direction);
		termDiffuse.xyz += specularIntensity * texture(TexSpecularMap, vec2(UV)).xyz * pow(clamp(dot(H, bumpedNormal), 0.0, 1.0), specularity);
	}

	if (true)
	{
		//outLight = texture(TexLightMap, UV);
	}

	outDiffuse = termDiffuse;
	//outDepth = vec4(WorldPos, ProjPos.z / ProjPos.w);
	//outNormal = vec4(bumpedNormal, 1.0f);
}

#endif