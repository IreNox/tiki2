
#version 400

#ifdef TIKI_VS

in vec3 inPos;
in vec2 inUV;

void main()
{
	gl_Position = vec4(inPos, 1.0);
	gl_TexCoord[0] = vec4(
		inUV.x,
		1 - inUV.y,
		0,
		0
	);
}

#endif
#ifdef TIKI_PS

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

uniform sampler2D rtDepth;
uniform sampler2D rtLight;
uniform sampler2D rtNormal;
uniform sampler2D rtScreen;
uniform sampler2D rtShadow;
uniform sampler2D rtInterface;

void main()
{
	vec4 sceneColor		= texture(rtScreen, vec2(gl_TexCoord[0]));
	vec4 shadowColor	= texture(rtShadow, vec2(gl_TexCoord[0]));
	vec4 lightColor		= texture(rtLight, vec2(gl_TexCoord[0]));
	vec4 interfaceColor	= texture(rtInterface, vec2(gl_TexCoord[0]));
	vec4 ambientColor	= vec4(1, 1, 1, 1); //ambientLight.Sample(sam, input.UV);

	vec4 color = sceneColor;

	if (LightsCount != 0.0f)
	{
		vec3 termLight = vec3(1, 1, 1);

		vec3 pixelPos = texture(rtDepth, vec2(gl_TexCoord[0])).xyz;
		vec3 pixelNormal = texture(rtNormal, vec2(gl_TexCoord[0])).xyz;

		for (int i = 0; i < LightsCount; i++)
		{
			vec3 lightDir = normalize(Lights[i].Direction); //normalize(Lights[i].Position - pixelPos);

			float lighting = dot(pixelNormal, lightDir);	
			//lighting *= (Lights[i].Range / dot(lightDir, lightDir));

			termLight += Lights[i].Color.xyz * lighting;
		}

		color.rgb *= termLight;
	}
	//color *= shadowColor;
	color *= ambientColor;
	color += lightColor;

	//color = (color * (1 - interfaceColor.a)) + interfaceColor;
	color.a = 1;

	gl_FragData[0] = color;
}

#endif