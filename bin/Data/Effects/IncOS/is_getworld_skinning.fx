matrix GetWorld(VS_INPUT input)
{
	matrix transform = 0;
	float weight = 0;

	for(int i = 0; i < 4;i++)
	{
		transform += bones[input.SkinningIndices[i]] * input.SkinningWeights[i];
		weight += input.SkinningWeights[i];
	}

	if(weight != 0)
	{
		return mul(transform, WorldM);
	}
	else
	{
		return WorldM;
	}
}