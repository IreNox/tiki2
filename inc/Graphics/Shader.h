#pragma once

#include "Core/TypeInc.h"
#include "Core/IShader.h"
#include "Core/ITexture.h"

#include "Graphics/D3dx11effect.h"

namespace TikiEngine
{
	namespace Resources
	{
		class Shader : public IShader
		{
		public:

			Shader(Engine* engine);
			~Shader();

			void SelectSubByIndex(UInt32 index);
			void SelectSubByName(cstring name);

			void Apply();
			void ApplyVars(GameObject* gameObject, Material* material);

			void SetConstantBuffer(cstring key, IConstantBuffer* constantBuffer);

			Int32 GetInt(cstring key);
			Single GetSingle(cstring key);
			Boolean GetBoolean(cstring key);
			Vector2 GetVector2(cstring key);
			Vector3 GetVector3(cstring key);
			Vector4 GetVector4(cstring key);
			Matrix GetMatrix(cstring key);

			void SetInt(cstring key, Int32 value);
			void SetSingle(cstring key, Single value);
			void SetBoolean(cstring key, Boolean value);
			void SetVector2(cstring key, const Vector2& value);
			void SetVector3(cstring key, const Vector3& value);
			void SetVector4(cstring key, const Vector4& value);
			void SetMatrix(cstring key, const Matrix& value);
			void SetTexture(cstring key, ITexture* value);
			void SetTextureArray(cstring key, List<ITexture*>* array);

			ShaderType GetShaderType();

			void* GetNativeResource();
			bool GetReady();

			void CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, UInt32* hash);

		protected:
			
			ShaderType type;

			ID3D11Device* device;
			ID3D11DeviceContext* context;

			ID3DX11Effect* effect;

			ID3DX11EffectPass* pass;
			ID3DX11EffectTechnique* technique;

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);
		};
	}
}