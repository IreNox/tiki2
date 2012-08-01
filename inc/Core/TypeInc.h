#pragma once

//#include <crtdbg.h>
#include "Core/TypeDef.h"

#include "Core/Vector2.h"
#include "Core/Vector3.h"
#include "Core/Vector4.h"
#include "Core/Quaternion.h"

#include "Core/Matrix2x2.h"
#include "Core/Matrix3x3.h"
#include "Core/Matrix.h"

#include "Core/Key.h"

#include "Core/List.h"
#include "Core/Dictionary.h"

#include <string>
using std::string;
using std::wstring;

typedef string  String;
typedef wstring StringW;

//#if defined(DEBUG) || defined(_DEBUG)
//#define TIKINEW new (_NORMAL_BLOCK, __FILE__,__LINE__)
//#else 
//#define TIKINEW new
//#endif