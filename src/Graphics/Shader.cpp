#pragma comment(lib, "Effects11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "Core/TypeGlobals.h"
#include "Core/Engine.h"
#include "Core/HelperLog.h"
#include "Core/HelperHash.h"
#include "Core/HelperPath.h"
#include "Core/GameObject.h"
#include "Core/Material.h"
#include "Core/FileStream.h"
#include "Core/MemoryStream.h"

#include "Graphics/Shader.h"
#include "Graphics/ConstantBuffer.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

#if TIKI_DX10
#define TDX_EFFECT_COMPILE D3DX10CompileFromMemory
#define TDX_EFFECT_PROFILE "fx_4_0"
#define TDX_EFFECT_CREATE D3DX10CreateEffectFromMemory
#define TDX_EFFECT_TECHNIQUE "tiki10"
#else
#define TDX_EFFECT_COMPILE D3DX11CompileFromMemory
#define TDX_EFFECT_PROFILE "fx_5_0"
#define TDX_EFFECT_CREATE D3DX11CreateEffectFromMemory
#define TDX_EFFECT_TECHNIQUE "tiki11"
#endif

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		#pragma region Class
		Shader::Shader(Engine* engine)
			: IShader(engine), effect(0)
		{
		}

		Shader::~Shader()
		{
			SafeRelease(&effect);
		}
		#pragma endregion

		#pragma region Member
		bool Shader::GetReady()
		{
			return (effect != 0);
		}

		void* Shader::GetNativeResource()
		{
			return effect;
		}

		ShaderType Shader::GetShaderType()
		{
			return type;
		}

		void Shader::Apply()
		{
#if TIKI_DX10
			pass->Apply(0);
#else
			pass->Apply(0, DllMain::Context);
#endif
		}

		void Shader::ApplyVars(GameObject* gameObject, Material* material, const Matrix& localMatrix)
		{
			if (type == ST_Object)
			{
				CBObjectData* objData = DllMain::ModuleGraphics->GetCBufferObject()->MapTI();

				gameObject->PRS.FillWorldMatrix(&objData->WorldM);
				objData->WorldM = Matrix::Multiply(objData->WorldM, localMatrix);

				objData->WorldMIT = Matrix::Transpose(
					Matrix::Invert(objData->WorldM)
				);

				if (material)
				{
					objData->UseDiffuse = (material->TexDiffuse != 0);
					objData->UseLightMap = (material->TexLightMap != 0);
					objData->UseNormalMap = (material->TexNormalMap != 0);
					objData->UseSpecularMap = (material->TexSpecularMap != 0);
					//objData->FlipTexcoordV = material->FlipTexcorrdV;

					if (objData->UseDiffuse) this->SetTexture("TexDiffuse", material->TexDiffuse);
					if (objData->UseLightMap) this->SetTexture("TexLightMap", material->TexLightMap);
					if (objData->UseNormalMap) this->SetTexture("TexNormalMap", material->TexNormalMap);
					if (objData->UseSpecularMap) this->SetTexture("TexSpecularMap", material->TexSpecularMap);
				}

				DllMain::ModuleGraphics->GetCBufferObject()->Unmap();
			}
		}

		void Shader::CreateLayout(TDX_Input_Element_desc* elements, UINT elementsCount, TDX_InputLayout** layout, UInt32* hash)
		{
#if TIKI_DX10
			D3D10_PASS_DESC passDesc;
			pass->GetDesc(&passDesc);

			HRESULT r = DllMain::Device->CreateInputLayout(
				elements,
				elementsCount,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				layout
			);
#else
			D3DX11_PASS_SHADER_DESC effectVsDesc;
			D3DX11_EFFECT_SHADER_DESC effectVsDesc2;

			pass->GetVertexShaderDesc(&effectVsDesc);
			effectVsDesc.pShaderVariable->GetShaderDesc(effectVsDesc.ShaderIndex, &effectVsDesc2);

			UINT vsCodeLen = effectVsDesc2.BytecodeLength;
			const void* vsCodePtr = effectVsDesc2.pBytecode;

			HRESULT r = DllMain::Device->CreateInputLayout(
				elements,
				elementsCount,
				vsCodePtr,
				vsCodeLen,
				layout
			);
#endif
			
			if (hash)
			{
				*hash = HelperHash::Hash(
					(UCHAR*)elements,
					sizeof(D3D11_INPUT_ELEMENT_DESC) * elementsCount
				);
			}
		}
		#pragma endregion

		#pragma region Member - Select
		void Shader::SelectSubByIndex(UInt32 index)
		{
			pass = technique->GetPassByIndex(index);
		}

		void Shader::SelectSubByName(cstring name)
		{
			pass = technique->GetPassByName(name);
		}
		#pragma endregion

		#pragma region Member - Variable
		void Shader::SetConstantBuffer(cstring key, IConstantBuffer* constantBuffer)
		{
#if TIKI_DX10
			ID3D10Buffer* buffer = (ID3D10Buffer*)constantBuffer->GBuffer();
#else
			ID3D11Buffer* buffer = (ID3D11Buffer*)constantBuffer->GBuffer();
#endif

			HRESULT r = effect->GetConstantBufferByName(key)->SetConstantBuffer(buffer);

			if (FAILED(r))
			{
				engine->HLog.Write("Error: Can't set ConstantBuffer: " + string(key));
			}
		}
		#pragma endregion
		
		#pragma region Member - Variable - Get
		int Shader::GetInt(cstring key)
		{
			int value = 0;
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetInt(&value);

			return value;
		}

		Boolean Shader::GetBoolean(cstring key)
		{
			int value = 0;
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetBool(&value);

			return (value ? true : false);
		}

		float Shader::GetSingle(cstring key)
		{
			float* value = 0;
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetFloat(value);

			return *value;
		}

		Matrix Shader::GetMatrix(cstring key)
		{
			float data[16];
			auto matrix = effect->GetVariableByName(key)->AsMatrix();

			matrix->GetMatrix(data);

			return Matrix(data);
		}

		Vector2 Shader::GetVector2(cstring key)
		{
			float data[2];
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetFloatArray(data, 0, 2);

			return Vector2(data);
		}

		Vector3 Shader::GetVector3(cstring key)
		{
			float data[3];
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetFloatArray(data, 0, 3);

			return Vector3(data);
		}

		Vector4 Shader::GetVector4(cstring key)
		{
			float data[4];
			auto scalar = effect->GetVariableByName(key)->AsScalar();

			scalar->GetFloatArray(data, 0, 4);

			return Vector4(data);
		}
		#pragma endregion

		#pragma region Member - Variable - Set
		void Shader::SetInt(cstring key, int value)
		{
			auto cv = effect->GetVariableByName(key)->AsScalar();

			cv->SetInt(value);
		}

		void Shader::SetBoolean(cstring key, Boolean value)
		{
			auto cv = effect->GetVariableByName(key)->AsScalar();

			cv->SetBool(value);
		}

		void Shader::SetSingle(cstring key, Single value)
		{
			auto cv = effect->GetVariableByName(key)->AsScalar();

			cv->SetFloat(value);
		}

		void Shader::SetMatrix(cstring key, const Matrix& value)
		{
			Matrix m = value;

			effect->GetVariableByName(key)->AsMatrix()->SetMatrix(m.n);
		}

		void Shader::SetVector2(cstring key, const Vector2& value)
		{
			Vector2 v = value;

			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(v.arr);
		}

		void Shader::SetVector3(cstring key, const Vector3& value)
		{
			Vector3 v = value;

			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(v.arr);
		}

		void Shader::SetVector4(cstring key, const Vector4& value)
		{
			Vector4 v = value;

			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(v.arr);
		}

		void Shader::SetTexture(cstring key, ITexture* texture)
		{
#if TIKI_DX10
			ID3D10ShaderResourceView* tex = (ID3D10ShaderResourceView*)texture->GetNativeResource();
#else
			ID3D11ShaderResourceView* tex = (ID3D11ShaderResourceView*)texture->GetNativeResource();
#endif

			effect->GetVariableByName(key)->AsShaderResource()->SetResource(tex);
		}

		void Shader::SetTextureArray(cstring key, List<ITexture*>* array)
		{
#if TIKI_DX10
			ID3D10ShaderResourceView** data = new ID3D10ShaderResourceView*[array->Count()];

			UInt32 i = 0;
			while (i < array->Count())
			{
				data[i] = (ID3D10ShaderResourceView*)array->Get(i)->GetNativeResource();
				i++;
			}
#else
			ID3D11ShaderResourceView** data = new ID3D11ShaderResourceView*[array->Count()];

			UInt32 i = 0;
			while (i < array->Count())
			{
				data[i] = (ID3D11ShaderResourceView*)array->Get(i)->GetNativeResource();
				i++;
			}
#endif

			HRESULT r = effect->GetVariableByName(key)->AsShaderResource()->SetResourceArray(
				data,
				0,
				array->Count()
			);

			if (FAILED(r))
			{
				throw "Can't set Shader Variable of type TextureArray";
			}

			delete[](data);
		}
		#pragma endregion

		#pragma region Private Member
		void Shader::loadFromStream(wcstring fileName, Stream* stream)
		{
			bool readFromFile = true;
			ID3D10Blob *errorBlob = 0;

#if !_DEBUG
			wstring binFileName = engine->HPath.CombineWorkingPath(L"Data/BinShader/" + engine->HPath.GetFilenameWithoutExtension(fileName) + L".binfx");

			engine->HPath.CheckPath(
				engine->HPath.GetDirectoryName(binFileName)
			);

			if (!engine->HPath.FileExists(binFileName))
#endif
			{
				ID3D10Blob *blob = 0;

				UPInt size = stream->GetLength();
				char* data = new char[size];
				stream->Read(data, 0, (UInt32)size);

				HRESULT r = TDX_EFFECT_COMPILE(
					data,
					size,
					0,
					0,
					0,
					0,
					TDX_EFFECT_PROFILE,
					0,
					0,
					0,
					&blob,
					&errorBlob,
					0
				);

				if (FAILED(r))
				{
					if (r == D3D10_ERROR_FILE_NOT_FOUND)
					{
						engine->HLog.WriteError("Failed to compile effect. File not found", 0);
					}
					else
					{
						if (errorBlob)
						{
							char* error = (char*)errorBlob->GetBufferPointer();
							engine->HLog.WriteError("Failed to compile effect. Error Message: " + (string)error, 0);
						}
						else
						{
							engine->HLog.WriteError("Failed to compile effect", 0);
						}
					}

					throw "Shader: .ctor: An error was corrupted.";
				}

				delete[](data);

#if !_DEBUG
				FileStream* binShader = new FileStream(binFileName, FM_Write);

				binShader->Write(
					blob->GetBufferPointer(),
					0,
					blob->GetBufferSize()
				);
				delete(binShader);

				SafeRelease(&blob);
			}

			stream = new FileStream(binFileName, FM_Read);
#else
				stream = new MemoryStream(blob->GetBufferPointer(), blob->GetBufferSize());
				SafeRelease(&blob);
			}

			TDX_Effect* oldEffect = effect;
#endif

			UPInt size = stream->GetLength();
			char* data = new char[size];
			stream->Read(data, 0, size);

#ifdef TIKI_DX10
			HRESULT r = D3DX10CreateEffectFromMemory(
				data,
				size,
				NULL,
				NULL,
				0,
				TDX_EFFECT_PROFILE,
				0,
				0,
				DllMain::Device,
				0,
				0,
				&effect,
				&errorBlob,
				0
			);
#else
			HRESULT r = D3DX11CreateEffectFromMemory(
				data,
				size,
				0,
				DllMain::Device,
				&effect
			);
#endif
						
			if (FAILED(r))
			{
#if _DEBUG
				effect = oldEffect;
#endif

				engine->HLog.WriteError("Failed to create effect.", 0);
			}
#if _DEBUG
			SafeRelease(&oldEffect);
#endif
			SafeDelete(&stream);
			SafeDeleteArray(&data);

			wstring file = engine->HPath.GetFilename(fileName);

			switch (file[0])
			{
			case 'o':
			case 'O':
				type = ST_Object;

				this->SetConstantBuffer(
					"ObjectData",
					DllMain::ModuleGraphics->GetCBufferObject()
				);

				this->SetConstantBuffer(
					"LightBuffer",
					DllMain::ModuleGraphics->GetCBufferLight()
				);

				this->SetConstantBuffer(
					"MatrixBuffer",
					DllMain::ModuleGraphics->GetCBufferCamera()
				);
				break;
			case 'p':
			case 'P':
				type = ST_PostProcess;

				this->SetConstantBuffer(
					"LightBuffer",
					DllMain::ModuleGraphics->GetCBufferLight()
				);
				break;
			default:
				type = ST_Unknown;
				break;
			}

			technique = effect->GetTechniqueByName(TDX_EFFECT_TECHNIQUE);
			this->SelectSubByIndex(0);
		}

		void Shader::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}