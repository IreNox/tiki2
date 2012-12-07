
const float amt = 120.0f - 0.1f;
const float bias = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////

GS_INPUT_SHADOW VS_Main_Shadow(VS_INPUT input)
{
	GS_INPUT_SHADOW output = (GS_INPUT_SHADOW)0;

	output.Pos = float4(input.Pos, 1.0f);
	output.Pos = mul(output.Pos, WorldM);

	output.Normal = mul(input.Normal, (float3x3)WorldM);

	return output;
}

////////////////////////////////////////////////////////////////////////////////
// Geometry Shader
////////////////////////////////////////////////////////////////////////////////

void DetectAndProcessSilhouette(float3 N, GS_INPUT_SHADOW v1, GS_INPUT_SHADOW v2, GS_INPUT_SHADOW vAdj, inout TriangleStream<PS_INPUT_SHADOW> ShadowTriangleStream)
{    
    float3 NAdj = cross(v2.Pos - vAdj.Pos, v1.Pos - vAdj.Pos);
    
    float3 outpos[4];
	float3 lightPos = Lights[0].Position;
    float3 extrude1 = normalize(v1.Pos - lightPos);
    float3 extrude2 = normalize(v2.Pos - lightPos);
    
	outpos[0] = v1.Pos + bias*extrude1;
    outpos[1] = v1.Pos + amt*extrude1;
    outpos[2] = v2.Pos + bias*extrude2;
    outpos[3] = v2.Pos + amt*extrude2;
        
    PS_INPUT_SHADOW output;
    for(int v=0; v<4; v++)
    {
        output.Pos = mul(float4(outpos[v],1), ViewM);
		output.Pos = mul(output.Pos, ProjectionM);

        ShadowTriangleStream.Append(output);
    }
    ShadowTriangleStream.RestartStrip();
}

[maxvertexcount(18)]
void GS_Main_Shadow(triangleadj GS_INPUT_SHADOW input[6], inout TriangleStream<PS_INPUT_SHADOW> triStream)
{
	float3 N = cross(input[2].Pos - input[0].Pos, input[4].Pos - input[0].Pos);
	float3 lightDir = Lights[0].Position - input[0].Pos; //Lights[0].Direction;

	if (dot(N, lightDir) > 0.0f)
	{
        // For each edge of the triangle, determine if it is a silhouette edge
        DetectAndProcessSilhouette(lightDir, input[0], input[2], input[1], triStream);
        DetectAndProcessSilhouette(lightDir, input[2], input[4], input[3], triStream);
        DetectAndProcessSilhouette(lightDir, input[4], input[0], input[5], triStream);
        
        //near cap
        PS_INPUT_SHADOW output;
        for(int v=0; v<6; v+=2)
        {
            float3 extrude = normalize(input[v].Pos - Lights[0].Position);
            
            float3 pos = input[v].Pos + bias * extrude;
            output.Pos = mul(float4(pos, 1), ViewM);
			output.Pos = mul(output.Pos, ProjectionM);

            triStream.Append(output);
        }
        triStream.RestartStrip();
        
        //far cap (reverse the order)
        for(int v=4; v>=0; v-=2)
        {
            float3 extrude = normalize(input[v].Pos - Lights[0].Position);
        
            float3 pos = input[v].Pos + amt * extrude;
            output.Pos = mul(float4(pos, 1), ViewM);
			output.Pos = mul(output.Pos, ProjectionM);

            triStream.Append(output);
        }
        triStream.RestartStrip();
	}
}

////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////

float4 PS_Main_Shadow(PS_INPUT_SHADOW input) : SV_TARGET
{
	return float4(0, 0, 0, 1.0f);
}