#pragma once

#include "Graphics/Shader.h"

namespace TikiEngine
{
	class Engine;

	using namespace TikiEngine::Effects;

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

			ULONG hash;
			ID3D11InputLayout* inputLayout;

			virtual void internalApply();

		private:
			UINT elementSize;
		};
	}
}