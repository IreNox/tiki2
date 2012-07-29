#pragma once

#include "Core/EngineObject.h"
#include "Core/InputElement.h"

#include "Core/List.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using TikiEngine::Vertices::InputElement;

		class Mesh : public EngineObject
		{
		public:

			Mesh(Engine* engine);
			~Mesh();

			void SetVertexData(void* data, UInt32 dataLength);
			void GetVertexData(void** data, UInt32* dataLength);

			List<InputElement>* GetVertexDeclaration();
			void SetVertexDeclaration(InputElement* elements, UInt32 count);

			virtual bool GetReady();

		private:

			void* vertexData;
			UInt32 vertexDataLength;

			List<InputElement> vertexDeclaration;
		};
	}
}

