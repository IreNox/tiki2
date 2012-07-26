#pragma once

#include "Graphics/Shader.h"

namespace TikiEngine
{
	using namespace TikiEngine::Graphics;

	namespace Vertices
	{
		class VertexDeclaration : public Object
		{
		public:
			VertexDeclaration(TikiEngine::Engine* engine, Shader* shader, UINT elementSize);
			VertexDeclaration(TikiEngine::Engine* engine, Shader* shader, UINT elementSize, D3D11_INPUT_ELEMENT_DESC* elements, UINT elementCount);

			virtual ~VertexDeclaration();

			void Apply();
			
			UINT GetElementSize();
			ULONG GetDeclarationHash();
			Shader* GetShader();
			
		protected:
			Engine* engine;
			Shader* shader;

			UInt32 hash;
			ID3D11InputLayout* inputLayout;

			virtual void internalApply();

		private:
			UINT elementSize;
		};
	}
}