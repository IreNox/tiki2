#include "Graphics/FBXConverter.h"

Vector2 FBXConverter::Convert(const FbxVector2 &vector)
{
	Vector2 v = Vector2(
		(float)vector[0],
		(float)vector[1]
	);

	return v;
}


Vector4 FBXConverter::Convert(const FbxVector4 &vector)
{
	Vector4 v = Vector4(
		(float)vector[0],
		(float)vector[1],
		(float)vector[2],
		(float)vector[3]
	);

	return v;
}