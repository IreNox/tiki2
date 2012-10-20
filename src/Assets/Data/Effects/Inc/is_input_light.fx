/////////////
// GLOBALS //
/////////////
cbuffer LightBuffer //: register(b2)
{
    float LightsCount;
	float DiffuseIntensity;
	float AmbientIntensity;
	float EmissiveIntensity;

	float4 AmbientColor		: COLOR;
	float4 EmissiveColor	: COLOR;

	//float IsDirty;
	//float DefaultShading;
	//float UnusedLightProperties[2];

	Light Lights[32];
};