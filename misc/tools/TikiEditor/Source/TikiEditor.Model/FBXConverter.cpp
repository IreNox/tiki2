
#define TIKI_EDITOR

#include "FBXConverter.h"

namespace TikiEditor
{
	Vector2 FBXConverter::Convert(const FbxVector2 &vector)
	{
		return Vector2(
			(float)vector[0],
			(float)vector[1]
		);
	}

	Vector4 FBXConverter::Convert(const FbxVector4 &vector)
	{
		return Vector4(
			(float)vector[0],
			(float)vector[1],
			(float)vector[2],
			(float)vector[3]
		);
	}

	Vector2 FBXConverter::Convert(const FbxDouble2 &vector)
	{
		return Vector2((float)vector[0], (float)vector[1]);
	}

	Vector3 FBXConverter::Convert(const FbxDouble3 &vector)
	{
		return Vector3((float)vector[0], (float)vector[1], (float)vector[2]);
	}

	Vector4 FBXConverter::Convert(const FbxDouble4 &vector)
	{
		return Vector4((float)vector[0], (float)vector[1], (float)vector[2], (float)vector[3]);
	}

	Vector3 FBXConverter::ConvertDrop(const FbxVector4 &vector)
	{
		return Vector3(
			(float)vector[0] / 100,
			(float)vector[1] / 100,
			(float)vector[2] / 100
		);
	}

	Matrix FBXConverter::Convert(const FbxAMatrix& mat)
	{
		return Matrix(
			(float)mat[0][0],
			(float)mat[1][0],
			(float)mat[2][0],
			(float)mat[3][0],

			(float)mat[0][1],
			(float)mat[1][1],
			(float)mat[2][1],
			(float)mat[3][1],

			(float)mat[0][2],
			(float)mat[1][2],
			(float)mat[2][2],
			(float)mat[3][2],

			(float)mat[0][3],
			(float)mat[1][3],
			(float)mat[2][3],
			(float)mat[3][3]);
	}

	Matrix FBXConverter::ConvertTranspose(const FbxAMatrix& mat)
	{
		return Matrix(
			(float)mat[0][0],
			(float)mat[0][1],
			(float)mat[0][2],
			(float)mat[0][3],

			(float)mat[1][0],
			(float)mat[1][1],
			(float)mat[1][2],
			(float)mat[1][3],

			(float)mat[2][0],
			(float)mat[2][1],
			(float)mat[2][2],
			(float)mat[2][3],

			(float)mat[3][0],
			(float)mat[3][1],
			(float)mat[3][2],
			(float)mat[3][3]);
	}

	Quaternion FBXConverter::Convert(const FbxQuaternion& quat)
	{
		return Quaternion((float)quat[0], (float)quat[1], (float)quat[2], (float)quat[3]);
	}
}