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

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		#pragma region Class
		Shader::Shader(Engine* engine)
			: IShader(engine), effect(0)
		{
			this->device = DllMain::Device;
			this->context = DllMain::Context;
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
			pass->Apply(0, context);
		}

		void Shader::ApplyVars(GameObject* gameObject, Material* material)
		{
			if (type == ST_Object)
			{
				CBObjectData* objData = DllMain::ModuleGraphics->GetCBufferObject()->MapTI();

				gameObject->PRS.FillWorldMatrix(&objData->WorldM);

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

		void Shader::CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, UInt32* hash)
		{
			D3DX11_PASS_SHADER_DESC effectVsDesc;
			pass->GetVertexShaderDesc(&effectVsDesc);

			D3DX11_EFFECT_SHADER_DESC effectVsDesc2;
			effectVsDesc.pShaderVariable->GetShaderDesc(effectVsDesc.ShaderIndex, &effectVsDesc2);

			UINT vsCodeLen = effectVsDesc2.BytecodeLength;
			const void* vsCodePtr = effectVsDesc2.pBytecode;

			HRESULT r = device->CreateInputLayout(
				elements,
				elementsCount,
				vsCodePtr,
				vsCodeLen,
				layout
			);

			*hash = HelperHash::Hash(
				(UCHAR*)elements,
				sizeof(D3D11_INPUT_ELEMENT_DESC) * elementsCount
			);
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
			HRESULT r = effect->GetConstantBufferByName(key)->SetConstantBuffer(
				(ID3D11Buffer*)constantBuffer->GBuffer()
			);

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
			effect->GetVariableByName(key)->AsMatrix()->SetMatrix(
				value.n
			);
		}

		void Shader::SetVector2(cstring key, const Vector2& value)
		{
			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(value.arr);
		}

		void Shader::SetVector3(cstring key, const Vector3& value)
		{
			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(value.arr);
		}

		void Shader::SetVector4(cstring key, const Vector4& value)
		{
			auto cv = effect->GetVariableByName(key)->AsVector();
			cv->SetFloatVector(value.arr);
		}

		void Shader::SetTexture(cstring key, ITexture* texture)
		{
			effect->GetVariableByName(key)->AsShaderResource()->SetResource(
				(ID3D11ShaderResourceView*)texture->GetNativeResource()
			);
		}

		void Shader::SetTextureArray(cstring key, List<ITexture*>* array)
		{
			ID3D11ShaderResourceView** data = new ID3D11ShaderResourceView*[array->Count()];

			UInt32 i = 0;
			while (i < array->Count())
			{
				data[i] = (ID3D11ShaderResourceView*)array->Get(i)->GetNativeResource();
				i++;
			}

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

#if !_DEBUG
			wstring binFileName = engine->HPath.CombineWorkingPath(L"Data/BinShader/" + engine->HPath.GetFilenameWithoutExtension(fileName) + L".binfx");

			engine->HPath.CheckPath(
				engine->HPath.GetDirectoryName(binFileName)
			);

			if (!engine->HPath.FileExists(binFileName))
			{
#else
			{
#endif

				ID3D10Blob *blob = 0;
				ID3D10Blob *errorBlob = 0;

				UPInt size = stream->GetLength();
				char* data = new char[size];
				stream->Read(data, 0, (UInt32)size);

				HRESULT r = D3DX11CompileFromMemory(
					data,
					size,
					0,
					0,
					0,
					0,
					"fx_5_0",
					0,
					0,
					0,
					&blob,
					&errorBlob,
					0
					);

				if (FAILED(r))
				{
					if (r == D3D11_ERROR_FILE_NOT_FOUND)
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

			ID3DX11Effect* oldEffect = effect;
#endif

			UPInt size = stream->GetLength();
			char* data = new char[size];
			stream->Read(data, 0, size);

			HRESULT r = D3DX11CreateEffectFromMemory(
				data,
				size,
				0,
				device,
				&effect
			);
			
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

			technique = effect->GetTechniqueByIndex(0);
			this->SelectSubByIndex(0);
		}

		void Shader::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}