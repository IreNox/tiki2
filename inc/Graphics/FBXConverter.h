#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#include "Core/Vector2.h"
#include "Core/Vector3.h"
#include "Core/Vector4.h"

class FBXConverter
{
public:

	static Vector2 Convert(const FbxVector2 &vector);
	static Vector4 Convert(const FbxVector4 &vector);

};