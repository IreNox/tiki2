#pragma once

#include "Core/IMesh.h"

#include "Graphics/VertexData.h"
#include "Graphics/VertexDeclaration.h"

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
			void SetVertexDeclaration(void* data, UInt32 dataLength);

			bool GetReady();

		private:

			VertexData* data;
			VertexDeclaration* decl;
		};
	}
}