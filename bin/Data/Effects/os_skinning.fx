//////////////
// DEFINES  //
//////////////

#ifndef VS_INPUT_EXT
#define VS_INPUT_EXT float4  SkinningWeights    : BLENDWEIGHT; float4  SkinningIndices    : BLENDINDICES;
#endif

//////////////
// TYPEDEFS //
//////////////

#include "Data/Effects/IncOS/is_structs.fx"

/////////////
// GLOBALS //
/////////////

cbuffer SkinMatrices 
{
	matrix bones[128];
};

#include "Data/Effects/IncOS/is_input.fx"


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_getworld_skinning.fx"
#include "Data/Effects/IncOS/is_defaultshader_vertex.fx"


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_defaultshader_pixel.fx"


////////////////////////////////////////////////////////////////////////////////
// Shadow
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_defaultshader_shadow.fx"


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////

#include "Data/Effects/IncOS/is_technique.fx"
