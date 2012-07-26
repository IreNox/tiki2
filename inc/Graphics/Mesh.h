#pragma once

#include "Core/IMesh.h"

#include "Graphics/VertexData.h"
#include "Graphics/VertexDeclaration.h"

#include "Graphics/Shader.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Vertices;

		class Mesh : public IMesh
		{
		public:

			Mesh(Engine* engine);
			virtual ~Mesh();

			void SetVertexData(void* data, UInt32 dataLength);
			void SetVertexDeclaration(InputElement* elements, UInt32 count);

			void CreateInputLayout(Shader* shader, ID3D11InputLayout** layout, UInt32* hash);

			bool GetReady();

		private:

			VertexData* data;
			List<InputElement> decl;
		};
	}
}