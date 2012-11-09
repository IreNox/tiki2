/////////////
// GLOBALS //
/////////////
cbuffer LightBuffer : register(b0)
{
    float LightsCount;
	float specularity;
	float UnusedTemp[2];

	float DiffuseIntensity;
	float AmbientIntensity;
	float EmissiveIntensity;
	float SpecularIntensity;

	float4 AmbientColor		: COLOR;
	float4 EmissiveColor	: COLOR;
	//float4 SpecularColor	: COLOR;

	Light Lights[32];
};