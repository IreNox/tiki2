#pragma comment(lib, "Effects11.lib")

#include "Graphics/Shader.h"
#include "Core/Console.h"

#include "Core/Engine.h"

#include "Core/HelperHash.h"
#include "Graphics/ConstantBuffer.h"

#include <d3d11.h>
#include <D3Dcompiler.h>

namespace TikiEngine
{
	namespace Effects
	{
		#pragma region Class
		Shader::Shader(Engine* engine)
			: engine(engine)
		{
			this->device = 0;
			this->context = 0;

			technique = effect->GetTechniqueByIndex(0);
			this->SelectSubByIndex(0);
		}

		Shader::~Shader()
		{
			if (effect != 0)
			{
				effect->Release();
				effect = 0;
			}
		}
		#pragma endregion

		#pragma region Member
		void Shader::Apply()
		{
			pass->Apply(0, context);
		}

		//void Shader::ApplyVars(Element* element)
		//{
		//	Matrix* worldMatrix = new Matrix(Matrix::Identity); //element->PRS.GetWorldMatrix();

		//	this->GetVariable(
		//		"worldMatrix"
		//	).SetMatrix(
		//		worldMatrix->Transpose()
		//	);

		//	delete(worldMatrix);
		//}

		void Shader::CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, ULONG* hash)
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

		void Shader::SelectSubByName(string name)
		{
			pass = technique->GetPassByName(name.c_str());
		}
		#pragma endregion

		#pragma region Member - Variable
		//void Shader::SetConstantBuffer(const char* key, ID3D11Buffer* constantBuffer)
		//{
		//	HRESULT r = effect->GetConstantBufferByName(key)->SetConstantBuffer(constantBuffer);

		//	if (FAILED(r))
		//	{
		//		Console::WriteError("Can't set ConstantBuffer: " + string(key), r);
		//	}
		//}
		#pragma endregion
		
		#pragma region Member - Variable - Get
		int Shader::GetInt(string key)
		{
			int* value = 0;
			auto scalar = effect->GetVariableByName(key.c_str())->AsScalar();

			scalar->GetInt(value);

			return *value;
		}

		float Shader::GetSingle(string key)
		{
			float* value = 0;
			auto scalar = effect->GetVariableByName(key.c_str())->AsScalar();

			scalar->GetFloat(value);

			return *value;
		}

		Matrix Shader::GetMatrix(string key)
		{
			float data[16];
			auto matrix = effect->GetVariableByName(key.c_str())->AsMatrix();

			matrix->GetMatrix(data);

			return Matrix(data);
		}

		Vector2 Shader::GetVector2(string key)
		{
			float data[2];
			auto scalar = effect->GetVariableByName(key.c_str())->AsScalar();

			scalar->GetFloatArray(data, 0, 2);

			return Vector2(data);
		}

		Vector3 Shader::GetVector3(string key)
		{
			float data[3];
			auto scalar = effect->GetVariableByName(key.c_str())->AsScalar();

			scalar->GetFloatArray(data, 0, 3);

			return Vector3(data);
		}

		Vector4 Shader::GetVector4(string key)
		{
			float data[4];
			auto scalar = effect->GetVariableByName(key.c_str())->AsScalar();

			scalar->GetFloatArray(data, 0, 4);

			return Vector4(data);
		}
		#pragma endregion

		#pragma region Member - Variable - Set
		void Shader::SetInt(string key, int value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsScalar();

			cv->SetInt(value);
		}

		void Shader::SetSingle(string key, Single value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsScalar();

			cv->SetFloat(value);
		}

		void Shader::SetMatrix(string key, const Matrix& value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsMatrix();

			cv->SetMatrix((float*)&value);
		}

		void Shader::SetVector2(string key, const Vector2& value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 2);
		}

		void Shader::SetVector3(string key, const Vector3& value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 3);
		}

		void Shader::SetVector4(string key, const Vector4& value)
		{
			auto cv = effect->GetVariableByName(key.c_str())->AsScalar();

			cv->SetFloatArray((float*)&value, 0, 4);
		}

		void Shader::SetTexture(string key, ITexture* texture)
		{
			effect->GetVariableByName(key.c_str())->AsShaderResource()->SetResource(
				(ID3D11ShaderResourceView*)texture->GetResource()
			);
		}
		#pragma endregion

		#pragma region Private Member
		void Shader::compileShader(string fileName)
		{
			ID3D10Blob *blob = 0;
			ID3D10Blob *errorBlob = 0;

			HRESULT r = D3DX11CompileFromFile(
				fileName.c_str(),
				0,
				0,
				0,
				"fx_5_0",
				D3D10_SHADER_ENABLE_STRICTNESS,
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
					Console::WriteError("Failed to compile effect. File not found", r);
				}
				else
				{
					if (errorBlob)
					{
						char* error = (char*)errorBlob->GetBufferPointer();
						Console::WriteError("Failed to compile effect. %s\n" + (string)error, r);
					}
					else
					{
						Console::WriteError("Failed to compile effect", r);
					}
				}

				throw "Shader: .ctor: An error was corrupted.";
			}

			createEffect(blob);
		}

		void Shader::createEffect(ID3D10Blob* blob)
		{
			HRESULT r = D3DX11CreateEffectFromMemory(
				blob->GetBufferPointer(),
				blob->GetBufferSize(),
				0,
				device,
				&effect
			);

			if (blob != 0)
			{
				blob->Release();
				blob = 0;
			}

			if (FAILED(r))
			{
				Console::Write("Failed to create effect. Error code: %d\n" + HRESULT_CODE(r));

				throw "Shader: .ctor: An error was corrupted.";
			}
		}
		#pragma endregion
	}
}