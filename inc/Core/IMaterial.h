#pragma once

#include "Core/EngineObject.h"

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IMaterial : EngineObject
		{
		public:

			IMaterial(Engine* engine)
				: EngineObject(engine)
			{
			}
			~IMaterial();

			virtual Int32 GetInt(string key) = 0;
			virtual Boolean GetBoolean(string key) = 0;
			virtual Vector2 GetVector2(string key) = 0;
			virtual Vector3 GetVector3(string key) = 0;
			virtual Vector4 GetVector4(string key) = 0;
			virtual Matrix GetMatrix(string key) = 0;

			virtual void SetInt(string key, Int32 value) = 0;
			virtual void SetBoolean(string key, Boolean value) = 0;
			virtual void SetVector2(string key, const Vector2& value) = 0;
			virtual void SetVector3(string key, const Vector3& value) = 0;
			virtual void SetVector4(string key, const Vector4& value) = 0;
			virtual void SetMatrix(string key, const Matrix& value) = 0;
		};
	}
}

