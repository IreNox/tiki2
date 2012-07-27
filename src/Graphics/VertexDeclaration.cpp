
#include "Core/Engine.h"
#include "Graphics/VertexDeclaration.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Vertices
	{
		#pragma region Class
		VertexDeclaration::VertexDeclaration(TikiEngine::Engine* engine, Shader* shader, UINT elementSize)
			: engine(engine), shader(shader), elementSize(elementSize)
		{
		}

		VertexDeclaration::VertexDeclaration(TikiEngine::Engine* engine, Shader* shader, UINT elementSize, D3D11_INPUT_ELEMENT_DESC* elements, UINT elementsCount)
			: engine(engine), shader(shader), elementSize(elementSize)
		{
			shader->CreateLayout(
				elements,
				elementsCount,
				&this->inputLayout,
				&this->hash
			);
		}

		VertexDeclaration::~VertexDeclaration()
		{
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

			this->internalApply();
		}

		void VertexDeclaration::internalApply()
		{
		}
		#pragma endregion
	}
}