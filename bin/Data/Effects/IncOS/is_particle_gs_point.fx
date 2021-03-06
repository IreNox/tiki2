[maxvertexcount(4)]
void GS_Main_Point(point GS_INPUT input[1], inout TriangleStream<PS_INPUT> triStream )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Color = input[0].Color;

	matrix view = transpose(ViewM);

	float3 a = view[2].xyz;
	float s = sin(input[0].ScaleRot.z);
	float c = cos(input[0].ScaleRot.z);

	float xx = a.x * a.x;
	float yy = a.y * a.y;
	float zz = a.z * a.z;
	float xy = a.x * a.y;
	float xz = a.x * a.z;
	float yz = a.y * a.z;

	matrix rot = matrix(
		xx + c * (1 - xx),		xy - c * xy + s * a.z,	xz - c * xz - s * a.y,	0,
		xy - c * xy - s * a.z,	yy + c * (1 - yy),		yz - c * yz + s * a.x,	0,
		xz - c * xz + s * a.y,	yz + c * yz - s * a.x,	zz + c * (1 - zz),		0,
		0,						0,						0,						1
	);

	float4 right = float4(normalize(view[0].xyz), 0) * input[0].ScaleRot.x;
	float4 up = float4(normalize(view[1].xyz), 0) * input[0].ScaleRot.y;

	right = mul(right, rot);
	up = mul(up, rot);

	output.Pos = input[0].Pos + ((-right) + (-up));
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos + ((-right) + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(0, 1);
	triStream.Append(output);

	output.Pos = input[0].Pos + (right + (-up));
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 0);
	triStream.Append(output);

	output.Pos = input[0].Pos + (right + up);
    output.Pos = mul(output.Pos, ViewM);
    output.Pos = mul(output.Pos, ProjectionM);
	output.UV = float2(1, 1);
	triStream.Append(output);

	triStream.RestartStrip();
}