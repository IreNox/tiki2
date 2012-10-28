/////////////
// GLOBALS //
/////////////

Texture2D<float3> tRandom;
Texture2D<float> tLinDepth;
Texture2D<float4> tNormal;

#define M_PI 3.14159265f

SamplerState samNearest
{    
    Filter   = MIN_MAG_MIP_POINT;
    AddressU = Clamp;
    AddressV = Clamp;
};

float  g_NumSteps = 8;
float  g_NumDir = 16;
float  g_R = 0;
float  g_inv_R = 0;
float  g_sqr_R = 0;
float  g_AngleBias = 30.0f;
float  g_TanAngleBias = -6.405331197f;
float  g_Attenuation = 1;
float  g_Contrast = 1.25f;
float  g_AspectRatio = 1.333333f;
float  g_InvAspectRatio = 0.7500001f;
float2 g_FocalLen = float2(1.333f, 2);
float2 g_InvFocalLen = float2(0.75f, 2);
float2 g_InvResolution = float2(0.25f, 0.33f);
float2 g_Resolution = float2(800, 600);
float2 g_ZLinParams = float2(10, 10);

 
float2 ScreenSize = float2(800.0f, 600.0f);
float farPlane = 1000.0f;

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
    float4 pos		: SV_POSITION;
	float2 tex		: TEXCOORD0;
    float2 texUV	: TEXCOORD1;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PS_INPUT VS_Main(uint id : SV_VertexID)
{
    PS_INPUT output = (PS_INPUT)0;    

    float2 tex = float2( (id << 1) & 2, id & 2 );
    output.tex = tex * float2( 2.0f, -2.0f ) + float2( -1.0f, 1.0f);
    output.pos = float4( output.tex, 0.0f, 1.0f );
    output.tex /= g_FocalLen;
    
    // Bottom left pixel is (0,0) and bottom right is (1,1)
    output.texUV = float2( (id << 1) & 2, id & 2 );
    
    return output;
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float tangent(float3 P, float3 S)
{
    return (P.z - S.z) / length(S.xy - P.xy);
}

//----------------------------------------------------------------------------------
float3 uv_to_eye(float2 uv, float eye_z)
{
    uv = (uv * float2(2.0, -2.0) - float2(1.0, -1.0));
    return float3(uv * g_InvFocalLen * eye_z, eye_z);
}

//----------------------------------------------------------------------------------
float3 fetch_eye_pos(float2 uv)
{
    float z = tLinDepth.SampleLevel(samNearest, float3(uv, 0), 0);
    return uv_to_eye(uv, z);
}

//----------------------------------------------------------------------------------
float3 tangent_eye_pos(float2 uv, float4 tangentPlane)
{
    // view vector going through the surface point at uv
    float3 V = fetch_eye_pos(uv);
    float NdotV = dot(tangentPlane.xyz, V);
    // intersect with tangent plane except for silhouette edges
    if (NdotV < 0.0) V *= (tangentPlane.w / NdotV);
    return V;
}

float length2(float3 v) { return dot(v, v); } 

//----------------------------------------------------------------------------------
float3 min_diff(float3 P, float3 Pr, float3 Pl)
{
    float3 V1 = Pr - P;
    float3 V2 = P - Pl;
    return (length2(V1) < length2(V2)) ? V1 : V2;
}

//----------------------------------------------------------------------------------
float falloff(float r)
{
    return 1.0f - g_Attenuation*r*r;
}

//----------------------------------------------------------------------------------
float2 snap_uv_offset(float2 uv)
{
    return round(uv * g_Resolution) * g_InvResolution;
}

float2 snap_uv_coord(float2 uv)
{
    //return (floor(uv * g_Resolution) + 0.5f) * g_InvResolution;
    return uv - (frac(uv * g_Resolution) - 0.5f) * g_InvResolution;
}

//----------------------------------------------------------------------------------
float tan_to_sin(float x)
{
    return x / sqrt(1.0f + x*x);
}

//----------------------------------------------------------------------------------
float3 tangent_vector(float2 deltaUV, float3 dPdu, float3 dPdv)
{
    return deltaUV.x * dPdu + deltaUV.y * dPdv;
}

//----------------------------------------------------------------------------------
float tangent(float3 T)
{
    return -T.z / length(T.xy);
}

//----------------------------------------------------------------------------------
float biased_tangent(float3 T)
{
    float phi = atan(tangent(T)) + g_AngleBias;
    return tan(min(phi, M_PI*0.5));
}

//----------------------------------------------------------------------------------
void integrate_direction(inout float ao, float3 P, float2 uv, float2 deltaUV,
                         float numSteps, float tanH, float sinH)
{
    for (float j = 1; j <= numSteps; ++j) {
        uv += deltaUV;
        float3 S = fetch_eye_pos(uv);
        
        // Ignore any samples outside the radius of influence
        float d2  = length2(S - P);
        if (d2 < g_sqr_R) {
            float tanS = tangent(P, S);

            [branch]
            if(tanS > tanH) {
                // Accumulate AO between the horizon and the sample
                float sinS = tanS / sqrt(1.0f + tanS*tanS);
                float r = sqrt(d2) * g_inv_R;
                ao += falloff(r) * (sinS - sinH);
                
                // Update the current horizon angle
                tanH = tanS;
                sinH = sinS;
            }
        }
    }
}

float AccumulatedHorizonOcclusion(float2 deltaUV, 
                                  float2 uv0, 
                                  float3 P, 
                                  float numSteps, 
                                  float randstep,
                                  float3 dPdu,
                                  float3 dPdv )
{
    // Randomize starting point within the first sample distance
    float2 uv = uv0 + snap_uv_offset( randstep * deltaUV );
    
    // Snap increments to pixels to avoid disparities between xy 
    // and z sample locations and sample along a line
    deltaUV = snap_uv_offset( deltaUV );

    // Compute tangent vector using the tangent plane
    float3 T = deltaUV.x * dPdu + deltaUV.y * dPdv;

    float tanH = biased_tangent(T);
    float sinH = tanH / sqrt(1.0f + tanH*tanH);

    float ao = 0;
    for(float j = 1; j <= numSteps; ++j) {
        uv += deltaUV;
        float3 S = fetch_eye_pos(uv);
        
        // Ignore any samples outside the radius of influence
        float d2  = length2(S - P);
        if (d2 < g_sqr_R) {
            float tanS = tangent(P, S);

            [branch]
            if(tanS > tanH) {
                // Accumulate AO between the horizon and the sample
                float sinS = tanS / sqrt(1.0f + tanS*tanS);
                float r = sqrt(d2) * g_inv_R;
                ao += falloff(r) * (sinS - sinH);
                
                // Update the current horizon angle
                tanH = tanS;
                sinH = sinS;
            }
        } 
    }

    return ao;
}

float2 rotate_direction(float2 Dir, float2 CosSin)
{
    return float2(Dir.x*CosSin.x - Dir.y*CosSin.y, 
                  Dir.x*CosSin.y + Dir.y*CosSin.x);
}

float4 PSPP_Main(PS_INPUT input) : SV_TARGET 
{	
    float3 P = fetch_eye_pos(input.texUV);
    
    // Project the radius of influence g_R from eye space to texture space.
    // The scaling by 0.5 is to go from [-1,1] to [0,1].
    float2 step_size = 0.5 * g_R  * g_FocalLen / P.z;

    // Early out if the projected radius is smaller than 1 pixel.
    float numSteps = min ( g_NumSteps, min(step_size.x * g_Resolution.x, step_size.y * g_Resolution.y));
    if( numSteps < 1.0 ) return 1.0;
    step_size = step_size / ( numSteps + 1 );

    // Nearest neighbor pixels on the tangent plane
    float3 Pr, Pl, Pt, Pb;
    float4 tangentPlane;
    if (false) {
        float3 N = normalize(tNormal.SampleLevel(samNearest, float3(input.texUV, 0), 0).xyz);
        tangentPlane = float4(N, dot(P, N));
        Pr = tangent_eye_pos(input.texUV + float2(g_InvResolution.x, 0), tangentPlane);
        Pl = tangent_eye_pos(input.texUV + float2(-g_InvResolution.x, 0), tangentPlane);
        Pt = tangent_eye_pos(input.texUV + float2(0, g_InvResolution.y), tangentPlane);
        Pb = tangent_eye_pos(input.texUV + float2(0, -g_InvResolution.y), tangentPlane);
    } else {
        Pr = fetch_eye_pos(input.texUV + float2(g_InvResolution.x, 0));
        Pl = fetch_eye_pos(input.texUV + float2(-g_InvResolution.x, 0));
        Pt = fetch_eye_pos(input.texUV + float2(0, g_InvResolution.y));
        Pb = fetch_eye_pos(input.texUV + float2(0, -g_InvResolution.y));
        float3 N = normalize(cross(Pr - Pl, Pt - Pb));
        tangentPlane = float4(N, dot(P, N));
    }
    
    // Screen-aligned basis for the tangent plane
    float3 dPdu = min_diff(P, Pr, Pl);
    float3 dPdv = min_diff(P, Pt, Pb) * (g_Resolution.y * g_InvResolution.x);

    // (cos(alpha),sin(alpha),jitter)
    float3 rand = tRandom.Load(int3((int)input.pos.x&63, (int)input.pos.y&63, 0)).xyz;

    float ao = 0;
    float d;
    float alpha = 2.0f * M_PI / g_NumDir;

    for (d = 0; d < g_NumDir; d++) {
        float angle = alpha * d;
        float2 dir = float2(cos(angle), sin(angle));
        float2 deltaUV = rotate_direction(dir, rand.xy) * step_size.xy;
        ao += AccumulatedHorizonOcclusion(deltaUV, input.texUV, P, numSteps, rand.z, dPdu, dPdv);
    }

    return 1.0 - ao / g_NumDir * g_Contrast;
}

BlendState DisableBlend
{
    BlendEnable[0] = false;
};

technique11 basic
{
    pass pass01
    {
        SetVertexShader(CompileShader(vs_5_0, VS_Main()));
		SetGeometryShader( NULL );
        SetPixelShader(CompileShader(ps_5_0, PSPP_Main()));
		SetBlendState( DisableBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }
}