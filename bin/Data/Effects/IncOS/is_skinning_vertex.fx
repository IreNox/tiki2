////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;    

	matrix transform = 0;
	float weight = 0;

	for(int i = 0; i < 4;i++)
	{
		transform += bones[input.SkinningIndices[i]] * input.SkinningWeights[i];
		weight += input.SkinningWeights[i];
	}

	float4 pos = mul(float4(input.Pos,1.0f), transform);

	if(weight != 0)
	{
		output.Pos = mul(pos, WorldM);
	}
	else
	{
		output.Pos = mul(float4(input.Pos, 1.0f), WorldM);
	}
    
	output.WorldPos = output.Pos.xyz;

    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
    output.DepthPos = output.Pos;

	output.UV = input.UV;
	output.UV.y = 1 - output.UV.y;
	//if (FlipTexcoordV) 

	float3 c1 = cross(input.Normal, float3(0.0, 0.0, 1.0)); 
	float3 c2 = cross(input.Normal, float3(0.0, 1.0, 0.0)); 

	output.Normal = normalize(mul(mul(input.Normal,(float3x3)transform), (float3x3)WorldMIT));
	output.Tangent = normalize(length(c1) > length(c2) ? c1 : c2);
    output.Binormal = normalize(cross(output.Normal, output.Tangent));
    
	#ifdef VS_MAIN_EXT
	VS_MAIN_EXT
	#endif

    return output;
}