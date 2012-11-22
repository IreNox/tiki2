[maxvertexcount(16)]
void GS_Main_LineList(line GS_INPUT input[2], inout TriangleStream<PS_INPUT> triStream )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Color = input[0].Color;

	float4 up = float4(0, 1 * input[0].ScaleRot.x, 0, 0);
	float4 right = float4(0, 0, 1 * input[0].ScaleRot.x, 0);

	// X-Asis
	output.Pos = input[0].Pos + up;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 0);
	triStream.Append(output);

	output.Pos = input[1].Pos + up;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos - up;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 1);
	triStream.Append(output);

	output.Pos = input[1].Pos - up;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 1);
	triStream.Append(output);

	triStream.RestartStrip();

	// Z-Asis
	output.Pos = input[0].Pos + right;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 0);
	triStream.Append(output);

	output.Pos = input[1].Pos + right;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos - right;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 1);
	triStream.Append(output);

	output.Pos = input[1].Pos - right;
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 1);
	triStream.Append(output);

	triStream.RestartStrip();

	// XZ-Asis - Back to Front
	output.Pos = input[0].Pos + (-right + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 0);
	triStream.Append(output);

	output.Pos = input[1].Pos + (-right + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos + (right - up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 1);
	triStream.Append(output);

	output.Pos = input[1].Pos + (right - up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 1);
	triStream.Append(output);

	triStream.RestartStrip();

	// XZ-Asis - Front to Back
	output.Pos = input[0].Pos + (right + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 0);
	triStream.Append(output);

	output.Pos = input[1].Pos + (right + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos + (-right - up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 1);
	triStream.Append(output);

	output.Pos = input[1].Pos + (-right - up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 1);
	triStream.Append(output);

	triStream.RestartStrip();
}