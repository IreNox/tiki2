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

			void Apply();
			void ApplyVars(Element* element);

			void SelectPassByIndex(UINT index);
			void SelectPassByName(string name);

			void SelectTechniqueByIndex(UINT index);
			void SelectTechniqueByName(string name);

			void CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, ULONG* hash);

			Shader::Variable GetVariable(const char* key);
			void SetConstantBuffer(const char* key, ID3D11Buffer* constantBuffer);

		protected:
			Engine* engine;
			ID3D11DeviceContext* context;

			ID3DX11Effect* effect;

			ID3DX11EffectPass* pass;
			ID3DX11EffectTechnique* technique;
		};
	}
}