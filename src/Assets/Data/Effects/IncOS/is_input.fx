/////////////
// GLOBALS //
/////////////
matrix fuckYouAsshole;

cbuffer ObjectData //: register(b0)
{
	matrix WorldM;		// World Matrix
	matrix WorldMIT;	// World Inverse Transpose Matrix

	bool UseDiffuse;
	bool UseNormalMap;
	bool UseSpecular;

	bool FlipTexcoordV;

	bool UnusedObjectData[12];
};

#include "Data/Effects/Inc/is_input_light.fx"

cbuffer MatrixBuffer //: register(b1)
{
    matrix ViewM;		// View Matrix;
    matrix ProjectionM;	// Projection Matrix;
};

Texture2D TexDiffuse;
Texture2D TexNormalMap;
Texture2D TexSpecular;

SamplerState sam : register(s0)
{    
  AddressU  = CLAMP;
  AddressV = CLAMP;
  FILTER = MIN_MAG_LINEAR_MIP_POINT;
};