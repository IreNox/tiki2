/////////////
// GLOBALS //
/////////////
#include "Data/Effects/Inc/is_input_light.fx"

cbuffer ObjectData : register(b1)
{
	matrix WorldM;		// World Matrix
	matrix WorldMIT;	// World Inverse Transpose Matrix

	bool UseDiffuse;
	bool UseLightMap;
	bool UseNormalMap;
	bool UseSpecularMap;
};

cbuffer MatrixBuffer : register(b2)
{
    matrix ViewM;		// View Matrix;
	matrix ViewIM;		// View Inverse Matrix;
    matrix ProjectionM;	// Projection Matrix;
};

Texture2D TexDiffuse;
Texture2D TexLightMap;
Texture2D TexNormalMap;
Texture2D TexSpecularMap;

SamplerState sam : register(s0)
{    
  AddressU  = WRAP;
  AddressV = WRAP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};