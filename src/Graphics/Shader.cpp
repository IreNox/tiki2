#pragma comment(lib, "Effects11.lib")

#include "Graphics/Shader.h"
#include "Core/Console.h"

#include "Core/Engine.h"

#include "Core/HelperHash.h"
#include "Graphics/ConstantBuffer.h"

namespace TikiEngine
{
	namespace Effects
	{
		#pragma region Class
		Shader::Shader(Engine* engine, wstring fileName)
			: engine(engine)
		{
			ID3D10Blob *blob = 0;
			ID3D10Blob *errorBlob = 0;

			this->context = engine->graphics->GetDeviceContext();
	
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

			r = D3DX11CreateEffectFromMemory(
				blob->GetBufferPointer(),
				blob->GetBufferSize(),
				0,
				engine->graphics->GetDevice(),
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

			this->SelectTechniqueByIndex(0);
			this->SelectPassByIndex(0);

			this->SetConstantBuffer(
				"MatrixBuffer",
				engine->scene->GetCurrentCamera()->GetMatrixBuffer()->GetBuffer()
			);
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

		void Shader::ApplyVars(Element* element)
		{
			Matrix* worldMatrix = new Matrix(Matrix::Identity); //element->PRS.GetWorldMatrix();

			this->GetVariable(
				"worldMatrix"
			).SetMatrix(
				worldMatrix->Transpose()
			);

			delete(worldMatrix);
		}

		void Shader::CreateLayout(D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount, ID3D11InputLayout** layout, ULONG* hash)
		{
			D3DX11_PASS_SHADER_DESC effectVsDesc;
			pass->GetVertexShaderDesc(&effectVsDesc);

			D3DX11_EFFECT_SHADER_DESC effectVsDesc2;
			effectVsDesc.pShaderVariable->GetShaderDesc(effectVsDesc.ShaderIndex, &effectVsDesc2);

			UINT vsCodeLen = effectVsDesc2.BytecodeLength;
			const void* vsCodePtr = effectVsDesc2.pBytecode;

			HRESULT r = engine->graphics->GetDevice()->CreateInputLayout(
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
		void Shader::SelectPassByIndex(UINT index)
		{
			pass = technique->GetPassByIndex(index);
		}

		void Shader::SelectPassByName(string name)
		{
			pass = technique->GetPassByName(name.c_str());
		}

		void Shader::SelectTechniqueByIndex(UINT index)
		{
			technique = effect->GetTechniqueByIndex(index);
		}

		void Shader::SelectTechniqueByName(string name)
		{
			technique = effect->GetTechniqueByName(name.c_str());
		}
		#pragma endregion

		#pragma region Member - Variable
		Shader::Variable Shader::GetVariable(const char* key)
		{
			return Shader::Variable(
				effect,
				key
			);
		}

		void Shader::SetConstantBuffer(const char* key, ID3D11Buffer* constantBuffer)
		{
			HRESULT r = effect->GetConstantBufferByName(key)->SetConstantBuffer(constantBuffer);

			if (FAILED(r))
			{
				Console::WriteError("Can't set ConstantBuffer: " + string(key), r);
			}
		}
		#pragma endregion
	}
}