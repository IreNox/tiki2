PS_OUTPUT PS_Main(PS_INPUT input) : SV_TARGET
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	float4 termDiffuse = (float4)0.8f;
	
	if (UseDiffuse)
	{
		termDiffuse = TexDiffuse.Sample(sam, input.UV) * DiffuseIntensity;
	}

	float3 bumpedNormal = input.Normal;		
	if (UseNormalMap)
	{
		float3 normalSample = 2 * TexNormalMap.Sample(sam, input.UV) - 1;
		float3x3 TBN = float3x3(input.Tangent, input.Binormal, input.Normal);

		bumpedNormal = normalize(mul(normalSample, TBN));
	}

	output.Screen = termDiffuse;
	output.Depth.rgb = 1 - (input.DepthPos.z / 1000.0f); //input.DepthPos.w;
	output.Depth.a = 1.0f;
	output.Normal = float4(bumpedNormal, 1.0f);
	
	return output;
}