#pragma once

#include "Core/TypeInc.h"
#include "Core/IShader.h"
#include "Core/ITexture.h"

#include "Graphics/D3dx11effect.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class Shader : public IShader
		{
		public:

			Shader(Engine* engine);
			~Shader();

			void LoadFromFile(wstring fileName);
			void CompileFromFile(wstring fileName);

			void SelectSubByIndex(UInt32 index);
			void SelectSubByName(string name);

			void Apply();

			Int32 GetInt(string key);
			Single GetSingle(string key);
			Boolean GetBoolean(string key);
			Vector2 GetVector2(string key);
			Vector3 GetVector3(string key);
			Vector4 GetVector4(string key);
			Matrix GetMatrix(string key);

			void SetInt(string key, Int32 value);
			void SetSingle(string key, Single value);
			void SetBoolean(string key, Boolean value);
			void SetVector2(string key, const Vector2& value);
			void SetVector3(string key, const Vector3& value);
			void SetVector4(string key, const Vector4& value);
			void SetMatrix(string key, const Matrix& value);
			void SetTexture(string key, ITexture* value);

			bool GetReady();

			void CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, UInt32* hash);

		protected:
			Engine* engine;
			ID3D11Device* device;
			ID3D11DeviceContext* context;

			ID3DX11Effect* effect;

			ID3DX11EffectPass* pass;
			ID3DX11EffectTechnique* technique;

			void compileShader(wstring fileName);
			void createEffect(ID3D10Blob* blob);
		};
	}
}