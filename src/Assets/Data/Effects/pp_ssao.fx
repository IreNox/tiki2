/////////////
// GLOBALS //
/////////////

Texture2D rtDiffuse;
Texture2D rtNormal;

SamplerState samRT
{    
  AddressU = Border;
  AddressV = Border;
  Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D texRandom;

SamplerState samRandom
{
    AddressU = Mirror;
    AddressV = Mirror;
    Filter = MIN_MAG_MIP_POINT;
};

//The number of samples used by the SSAO
int nbrSamples = 32;
 
//The world scale 
float minScale = 4;
float maxScale = 30;

//Exponent used to enhance the final contrast
float exponent = 0.5f;

//The camera forward vector
float3 ViewForward;
Matrix SceneViewProj;
 
//Samples points distributed in the unit sphere using energy minimisation
float3 samples[32] =
{
        float3(-0.970699, -0.184458,  0.154010),
        float3(-0.831648, -0.217331, -0.511008),
        float3(-0.034957,  0.797863, -0.601824),
		float3(0.8753442, 0.36699, 0.3147869),
		float3(0.6382127, -0.7472377, 0.1852573),
		float3(-0.1142627, -0.5470265, -0.8292804),
		float3(0.6798767, -0.3389591, -0.6502879),
		float3(-0.5033126, 0.7276701, -0.4660179),
		float3(-0.5932125, 0.7694008, 0.2368994),
		float3(0.9814014, 0.09799305, -0.1650715),
		float3(0.3818589, -0.6596552, -0.6473321),
		float3(0.6219621, 0.2701145, 0.7349839),
		float3(-0.9414448, -0.2061836, -0.2667771),
		float3(-0.3273515, -0.9318677, -0.1564085),
		float3(-0.7889578, 0.4944179, 0.3648241),
		float3(-0.7335306, 0.64296, 0.2203074),
		float3(-0.7761862, 0.2504477, 0.5786286),
		float3(-0.2001825, -0.9330282, 0.2989738),
		float3(-0.6757848, -0.3040948, -0.6714471),
		float3(-0.2429276, 0.7178079, -0.652486),
		float3(0.9832612, 0.1801602, -0.02719888),
		float3(-0.009270667, -0.9394712, 0.3425023),
		float3(0.2488964, -0.9684005, -0.01584767),
		float3(0.5440276, -0.2700348, 0.7944276),
		float3(0.8157443, 0.1172611, -0.5664019),
		float3(0.3712924, -0.6539754, -0.6591344),
		float3(0.1022104, -0.55469, 0.8257555),
		float3(0.7087573, 0.223244, 0.6691974),
		float3(0.413506, -0.2202173, 0.8834688),
		float3(-0.3851829, -0.0937902, -0.9180618),
		float3(0.07387131, 0.8235579, 0.5624016),
		float3(-0.305365,  0.806397,  0.506435)
};

float2 HalfPixel = float2(0.01f, 0.01f);

//////////////
// TYPEDEFS //
//////////////
struct VS_INPUT
{
    float3 Pos	  : POSITION;
	float2 UV	  : TEXCOORD;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 UV  : TEXCOORD0;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;    

	output.Pos = float4(input.Pos, 1.0f);
    output.UV = input.UV + HalfPixel;
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PSPP_Main(PS_INPUT input) : SV_TARGET 
{	
    //Obtain the normalized forward vector
    float3 forward = normalize(ViewForward);
 
    //We sample the different buffers
    float4 fragmentPos = rtDiffuse.Sample(samRT, input.UV);
    float3 fragmentNormal = rtNormal.Sample(samRT, input.UV);
    fragmentNormal = normalize((fragmentNormal - 0.5f) * 2.0f);    
 
    //Pick a random vector for this pixel
    float3 random = normalize(texRandom.Sample(samRandom, input.UV * 250));
 
    float totalWeight = 0;
    float totalOcclusion = 0;
    for(int i = 0; fragmentPos.a > 0.5 && i < nbrSamples && i < 32; i++)
    {
        //Distribute samples scale between minScale and maxScale 
        float k = (float)i / (float)nbrSamples;
        float sampleScale = minScale * k  + maxScale * (1-k);
 
        //Compute a sample vector. We use a random reflection plane for dithering
        float3 sampleOffset = sampleScale * reflect(samples[i%32].rgb, random);
 
        //We reflect the sample vector if needed to avoid self-occlusion
        if (dot(sampleOffset, fragmentNormal) < 0)
		{
            sampleOffset = reflect(sampleOffset , fragmentNormal);
		}
 
        //Compute the sample position
        float3 samplePos = fragmentPos.rgb + sampleOffset.rgb;
        //The corresponding depth
        float sampleDepth = dot(samplePos, forward);
 
        //The corresponding offset in pixel, in the screen space
        float4 screenOffset = mul(float4(sampleOffset, 1), SceneViewProj);
        float2 uvOffset = float2( screenOffset.x, -screenOffset.y) / screenOffset.w;
 
        //Read the corresponding pixel position in the scene
        float4 scenePos = rtDiffuse.Sample(samRT, input.UV + uvOffset);
        //The corresponding depth
        float sceneDepth = dot(scenePos, forward);
 
        //Put depth to infinity if no geometry is drawn (scenePos.a=0), to avoid occlusion from background
        if (scenePos.a < 0.5)
		{
            sceneDepth = -100000;
		}
 
        //Computing the relative depth
        float relativeDepth = (sampleDepth - sceneDepth) / (maxScale);
 
        //The sample contribution depends on its angle with surface normal
        float weight = dot( normalize(samplePos - fragmentPos), normalize(fragmentNormal));
        totalWeight += weight;
 
        //The final occlusion        
        float occlusionFactor =  weight * 1 / (1 + relativeDepth * relativeDepth);
 
        totalOcclusion += step(relativeDepth, -1 / (sampleScale * 1000)) * occlusionFactor;
    }        
 
    //Renormalize the total occlusion
    totalOcclusion = totalOcclusion / totalWeight;
 
    //Enhance the final contrast
    float finalOcclusion = pow(totalOcclusion, exponent);
 
    return 1 - finalOcclusion;
}

technique11 basic
{
    pass pass01
    {
        SetVertexShader(CompileShader(vs_5_0, VS_Main()));
        SetPixelShader(CompileShader(ps_5_0, PSPP_Main()));
    }
}