#pragma once

#include "Core/TypeInc.h"
#include "Core/IShader.h"
#include "Core/ITexture.h"

#include "Graphics/DllMain.h"

#if TIKI_DX10
typedef ID3D10Effect TDX_Effect;
typedef ID3D10EffectPass TDX_EffectPass;
typedef ID3D10EffectTechnique TDX_EffectTechnique;
#elif TIKI_DX11
#include "Graphics/D3dx11effect.h"

typedef ID3DX11Effect TDX_Effect;
typedef ID3DX11EffectPass TDX_EffectPass;
typedef ID3DX11EffectTechnique TDX_EffectTechnique;
#endif

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
			void ApplyVars(GameObject* gameObject, Material* material, const Matrix& localMatrix);

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
			void SetTextureArray(cstring key, List<ITexture*>& array);

			ShaderType GetShaderType();

			void* GetNativeResource();
			bool GetReady();
			
#if TIKI_DX10 || TIKI_DX11
			void CreateLayout(TDX_Input_Element_desc* elements, UINT elementsCount, TDX_InputLayout** layout, UInt32* hash);
#endif

		protected:
			
			ShaderType type;

#if TIKI_DX10 || TIKI_DX11
			TDX_Effect* effect;
			TDX_EffectPass* pass;
			TDX_EffectTechnique* technique;
#elif TIKI_OGL
			int vsId;
			int psId;
			int shaderId;

			bool getShaderInfo(int id, string& log, bool program);
#endif

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);
		};
	}
}