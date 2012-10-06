#pragma once

#include "Core/EngineObject.h"
#include "Core/InputElement.h"

#include "Graphics/Shader.h"

namespace TikiEngine
{
	using namespace TikiEngine::Resources;

	namespace Vertices
	{
		class VertexDeclaration : public EngineObject
		{
		public:
			VertexDeclaration(Engine* engine, IShader* shader, List<InputElement>* elements);
			VertexDeclaration(Engine* engine, IShader* shader, InputElement* elements, UInt32 elementsCount);
			~VertexDeclaration();

			void Apply();
			
			UINT GetElementSize();
			ULONG GetDeclarationHash();
			Shader* GetShader();
			
		private:

			Shader* shader;

			UInt32 hash;
			UInt32 elementSize;
			ID3D11InputLayout* inputLayout;

			void createInputLayout(const InputElement* decl, UInt32 count);

		};
	}
}