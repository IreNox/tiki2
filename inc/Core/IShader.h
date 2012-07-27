#pragma once

#include "Core/TypeInc.h"

#include "Core/EngineObject.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IShader : public EngineObject
		{
		public:

			IShader(Engine* engine)
				: EngineObject(engine)
			{
			}
			~IShader() {}

			virtual void LoadFromFile(string fileName) = 0;
			virtual void CompileFromFile(string fileName) = 0;

			virtual void SelectSubByIndex(UInt32 index) = 0;
			virtual void SelectSubByName(string name) = 0;

			virtual void Apply() = 0;

			virtual Int32 GetInt(string key) = 0;
			virtual Single GetSingle(string key) = 0;
			virtual Boolean GetBoolean(string key) = 0;
			virtual Vector2 GetVector2(string key) = 0;
			virtual Vector3 GetVector3(string key) = 0;
			virtual Vector4 GetVector4(string key) = 0;
			virtual Matrix GetMatrix(string key) = 0;

			virtual void SetInt(string key, Int32 value) = 0;
			virtual void SetSingle(string key, Single value) = 0;
			virtual void SetBoolean(string key, Boolean value) = 0;
			virtual void SetVector2(string key, const Vector2& value) = 0;
			virtual void SetVector3(string key, const Vector3& value) = 0;
			virtual void SetVector4(string key, const Vector4& value) = 0;
			virtual void SetMatrix(string key, const Matrix& value) = 0;
			virtual void SetTexture(string key, ITexture* value) = 0;

			virtual bool GetReady() = 0;
		};
	}
}
