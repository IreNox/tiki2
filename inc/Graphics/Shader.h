#pragma once

#include <string>

#include "Graphics/D3dx11effect.h"
#include <d3dx10math.h>

#include "Core\Matrix.h"
#include "Core\Vector2.h"
#include "Core\Vector3.h"
#include "Core\Vector4.h"

#include "Core/Object.h"
#include "Core/Element.h"
#include "Core/Texture.h"

using namespace std;

namespace TikiEngine
{
	class Engine;

	namespace Effects
	{
		using namespace TikiEngine::Elements;
		using namespace TikiEngine::Resources;

		class Shader : public Object
		{
		public:
			#pragma region Class - Variable
			class Variable
			{
			public:
				Variable(ID3DX11Effect* effect, const char* key);
				~Variable();

				int GetInt();
				float GetFloat();		
				Matrix GetMatrix();
				Vector2 GetVector2();
				Vector3 GetVector3();
				Vector4 GetVector4();

				void SetInt(int value);
				void SetFloat(float value);
				void SetMatrix(const Matrix& value);
				void SetVector2(const Vector2& value);
				void SetVector3(const Vector3& value);
				void SetVector4(const Vector4& value);
				void SetTexture(Texture* trexture);

			private:
				ID3DX11EffectVariable* var;
			};
			#pragma endregion

			Shader(Engine* g, wstring fileName);
			~Shader();

			virtual void LoadFromFile(string fileName) = 0;
			virtual void CompileFromFile(string fileName) = 0;

			void SelectPassByIndex(UINT index);
			void SelectPassByName(string name);

			void SelectTechniqueByIndex(UINT index);
			void SelectTechniqueByName(string name);

			virtual void Apply() = 0;

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

			virtual bool GetReady() = 0;

			void CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, ULONG* hash);

			//void SetConstantBuffer(const char* key, ID3D11Buffer* constantBuffer);

		protected:
			Engine* engine;
			ID3D11DeviceContext* context;

			ID3DX11Effect* effect;

			ID3DX11EffectPass* pass;
			ID3DX11EffectTechnique* technique;
		};
	}
}