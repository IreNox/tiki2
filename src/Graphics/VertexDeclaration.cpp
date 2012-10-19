
#include "Core/Engine.h"
#include "Core/InputElement.h"

#include "Graphics/VertexDeclaration.h"

#include "Graphics/DllMain.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Vertices
	{
		#pragma region Class
		VertexDeclaration::VertexDeclaration(Engine* engine, IShader* shader, List<InputElement>* elements)
			: EngineObject(engine)
		{
			SafeAddRef((Shader*)shader, &this->shader);
			createInputLayout(elements->GetInternalData(), elements->Count());
		}

		VertexDeclaration::VertexDeclaration(Engine* engine, IShader* shader, InputElement* elements, UInt32 elementsCount)
			: EngineObject(engine)
		{
			SafeAddRef((Shader*)shader, &this->shader);
			createInputLayout(elements, elementsCount);
		}

		VertexDeclaration::~VertexDeclaration()
		{
			SafeRelease(&shader);
			SafeRelease(&inputLayout);
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
		void VertexDeclaration::createInputLayout(const InputElement* decl, UInt32 count)
		{
			elementSize = 0;
			D3D11_INPUT_ELEMENT_DESC* elements = new D3D11_INPUT_ELEMENT_DESC[count];

			UInt32 i = 0;
			while (i < count)
			{
				InputElement input = decl[i];
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
				case IST_SV_RenderTargetArrayIndex:
					element.SemanticName = "SV_RenderTargetArrayIndex";
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
				count,
				&inputLayout,
				&hash
			);

			delete(elements);
		}
		#pragma endregion
	}
}