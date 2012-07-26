
#include "Core/Engine.h"
#include "Graphics/Mesh.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: IMesh(engine), data(0), decl()
		{
		}

		Mesh::~Mesh()
		{
			if (this->data != 0)
			{
				delete(this->data);
			}	
		}
		#pragma endregion

		#pragma region Member
		bool Mesh::GetReady()
		{
			return (data != 0) && (decl.Count() != 0);
		}
		#pragma endregion

		#pragma region Member
		void Mesh::SetVertexData(void* data, UInt32 dataLength)
		{

		}

		void Mesh::SetVertexDeclaration(InputElement* elements, UInt32 count)
		{
			decl = List<InputElement>(elements, count, true);
		}

		//void Mesh::Init(VertexDeclaration* decl)
		//{
		//	if (this->data != 0) return;

		//	shader = decl->GetShader();

		//	this->data = new VertexData(
		//		engine,
		//		shader,
		//		decl
		//	);
		//}
		#pragma endregion

		#pragma region Member - CreateInputLayout
		void Mesh::CreateInputLayout(Shader* shader, ID3D11InputLayout** layout, UInt32* hash)
		{
			D3D11_INPUT_ELEMENT_DESC* elements = new D3D11_INPUT_ELEMENT_DESC[decl.Count()];

			int i = 0;
			while (i < decl.Count())
			{
				InputElement input = decl[i];
				D3D11_INPUT_ELEMENT_DESC element;
				
				switch (input.SemanticType)
				{
					case InputElementType::Position:
						element.SemanticName = "POSITION";
						break;
					case InputElementType::Normal:
						element.SemanticName = "NORMAL";
						break;
					case InputElementType::TexCoord:
						element.SemanticName = "TEXCOORD";
						break;
					case InputElementType::Tangent:
						element.SemanticName = "TANGENT";
						break;
					case InputElementType::Color:
						element.SemanticName = "COLOR";
						break;
					case InputElementType::Binormal:
						element.SemanticName = "BINORMAL";
						break;
				}
				element.SemanticIndex = input.SemanticIndex;

				switch (input.ElementFormat)
				{
					case InputElementFormat::UInt:
						switch (input.ElementSize)
						{
							case 1:
								element.Format = DXGI_FORMAT_R32_UINT;
								break;
							case 2:
								element.Format = DXGI_FORMAT_R32G32_UINT;
								break;
							case 4:
								element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
								break;
						}
						break;
					case InputElementFormat::Float:
						switch (input.ElementSize)
						{
						case 1:
							element.Format = DXGI_FORMAT_R32_FLOAT;
							break;
						case 2:
							element.Format = DXGI_FORMAT_R32G32_FLOAT;
							break;
						case 4:
							element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
							break;
						}
						break;
					case InputElementFormat::Bool:
						element.Format = DXGI_FORMAT_R8_UINT;
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
				decl.Count(),
				layout,
				hash
			);

			delete(elements);
		}

		//void Mesh::Draw(const FrameArgs& args)
		//{
		//	data->Apply();
		//	
		//	context->DrawIndexed(
		//		data->countIndex,
		//		data->indexIndex,
		//		data->indexVertex
		//	);
		//}
		#pragma endregion
	}
}