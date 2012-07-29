
#include "Core/Engine.h"
#include "Core/InputElement.h"

#include "Graphics/VertexDeclaration.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Vertices
	{
		#pragma region Class
		VertexDeclaration::VertexDeclaration(Engine* engine, IShader* shader, List<InputElement>* elements)
			: EngineObject(engine)
		{
			this->shader = (Shader*)shader;

			this->shader->AddRef();
			createInputLayout(elements);
		}

		VertexDeclaration::~VertexDeclaration()
		{
			if (shader != 0)
			{
				shader->Release();
				shader = 0;
			}

			if (inputLayout != 0)
			{
				inputLayout->Release();
				inputLayout = 0;
			}
		}
		#pragma endregion

		#pragma region Member - Get
		UINT VertexDeclaration::GetElementSize()
		{
			return this->elementSize;
		}

		ULONG VertexDeclaration::GetDeclarationHash()
		{
			return this->hash;
		}

		Shader* VertexDeclaration::GetShader()
		{
			return shader;
		}
		#pragma endregion

		#pragma region Member - Apply
		void VertexDeclaration::Apply() 
		{
			DllMain::Context->IASetInputLayout(
				this->inputLayout
			);
		}
		#pragma endregion

		#pragma region Private Member - CreateInputLayout
		void VertexDeclaration::createInputLayout(List<InputElement>* decl)
		{
			elementSize = 0;
			D3D11_INPUT_ELEMENT_DESC* elements = new D3D11_INPUT_ELEMENT_DESC[decl->Count()];

			int i = 0;
			while (i < decl->Count())
			{
				InputElement input = decl->Get(i);
				D3D11_INPUT_ELEMENT_DESC element;

				switch (input.SemanticType)
				{
				case IST_Position:
					element.SemanticName = "POSITION";
					break;
				case IST_Normal:
					element.SemanticName = "NORMAL";
					break;
				case IST_TexCoord:
					element.SemanticName = "TEXCOORD";
					break;
				case IST_Tangent:
					element.SemanticName = "TANGENT";
					break;
				case IST_Color:
					element.SemanticName = "COLOR";
					break;
				case IST_Binormal:
					element.SemanticName = "BINORMAL";
					break;
				}
				element.SemanticIndex = input.SemanticIndex;

				switch (input.ElementFormat)
				{
				case IEF_UInt:
					switch (input.ElementSize)
					{
					case 1:
						element.Format = DXGI_FORMAT_R32_UINT;
						break;
					case 2:
						element.Format = DXGI_FORMAT_R32G32_UINT;
						break;
					case 3:
						element.Format = DXGI_FORMAT_R32G32B32_UINT;
						break;
					case 4:
						element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
						break;
					}

					elementSize += 4 * input.ElementSize;
					break;					
				case IEF_Float:
					switch (input.ElementSize)
					{
					case 1:
						element.Format = DXGI_FORMAT_R32_FLOAT;
						break;
					case 2:
						element.Format = DXGI_FORMAT_R32G32_FLOAT;
						break;
					case 3:
						element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					case 4:
						element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					}

					elementSize += 4 * input.ElementSize;
					break;
				case IEF_Bool:
					element.Format = DXGI_FORMAT_R8_UINT;
					elementSize += input.ElementSize;
					break;
				}

				element.InputSlot = 0;
				element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				element.InstanceDataStepRate = 0;

				elements[i] = element;

				i++;
			}

			shader->CreateLayout(
				elements,
				decl->Count(),
				&inputLayout,
				&hash
			);

			delete(elements);
		}
		#pragma endregion
	}
}