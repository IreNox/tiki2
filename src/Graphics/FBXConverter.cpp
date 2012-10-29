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
Matrix FBXConverter::Convert(const FbxAMatrix& mat)
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

Matrix FBXConverter::ConvertTranspose(const FbxAMatrix& mat)
{
	return Matrix(
		(float)mat.mData[0].mData[0],
		(float)mat.mData[1].mData[0],
		(float)mat.mData[2].mData[0],
		(float)mat.mData[3].mData[0],

		(float)mat.mData[0].mData[1],
		(float)mat.mData[1].mData[1],
		(float)mat.mData[2].mData[1],
		(float)mat.mData[3].mData[1],

		(float)mat.mData[0].mData[2],
		(float)mat.mData[1].mData[2],
		(float)mat.mData[2].mData[2],
		(float)mat.mData[3].mData[2],

		(float)mat.mData[0].mData[3],
		(float)mat.mData[1].mData[3],
		(float)mat.mData[2].mData[3],
		(float)mat.mData[3].mData[3]);
}