#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#include "Core/Vector2.h"
#include "Core/Vector3.h"
#include "Core/Vector4.h"
#include "Core/Quaternion.h"

class FBXConverter
{
public:

	static Vector2 Convert(const FbxVector2 &vector);
	static Vector4 Convert(const FbxVector4 &vector);

	static Vector3 ConvertDrop(const FbxVector4 &vector);

	static Vector2 Convert(const FbxDouble2 &vecotr);
	static Vector3 Convert(const FbxDouble3 &vector);
	static Vector4 Convert(const FbxDouble4 &vector);
	static Matrix Convert(const FbxAMatrix &mat);
	static Matrix ConvertTranspose(const FbxAMatrix& mat);

	static Quaternion Convert(const FbxQuaternion& quat);

};