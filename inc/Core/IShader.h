#pragma once

#include "Core/TypeInc.h"

#include "Core/IResource.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	class GameObject;

	namespace Resources
	{
		enum ShaderType
		{
			ST_Object,
			ST_PostProcess,
			ST_Unknown = 0xFF
		};

		class IShader : public IResource
		{
		public:

			IShader(Engine* engine)
				: IResource(engine)
			{
			}
			~IShader() {}

			virtual void SelectSubByIndex(UInt32 index) = 0;
			virtual void SelectSubByName(cstring name) = 0;

			virtual void Apply() = 0;
			virtual void ApplyVars(GameObject* gameObject) = 0;

			virtual Int32 GetInt(cstring key) = 0;
			virtual Single GetSingle(cstring key) = 0;
			virtual Boolean GetBoolean(cstring key) = 0;
			virtual Vector2 GetVector2(cstring key) = 0;
			virtual Vector3 GetVector3(cstring key) = 0;
			virtual Vector4 GetVector4(cstring key) = 0;
			virtual Matrix GetMatrix(cstring key) = 0;

			virtual void SetInt(cstring key, Int32 value) = 0;
			virtual void SetSingle(cstring key, Single value) = 0;
			virtual void SetBoolean(cstring key, Boolean value) = 0;
			virtual void SetVector2(cstring key, const Vector2& value) = 0;
			virtual void SetVector3(cstring key, const Vector3& value) = 0;
			virtual void SetVector4(cstring key, const Vector4& value) = 0;
			virtual void SetMatrix(cstring key, const Matrix& value) = 0;
			virtual void SetTexture(cstring key, ITexture* value) = 0;
			virtual void SetTextureArray(cstring key, List<ITexture*>* array) = 0;

			virtual ShaderType GetShaderType() = 0;

			virtual bool GetReady() = 0;
		};
	}
}

