#pragma once

#include "Core/TypeGlobals.h"

#include "Core/IResource.h"
#include "Core/InputElement.h"
#include "Core/PrimitiveTopologies.h"

namespace TikiEngine
{
	namespace Resources
	{
		using TikiEngine::Vertices::InputElement;

		class Mesh : public IResource
		{
		public:

			Mesh(Engine* engine);
			~Mesh();

			void GetIndexData(UInt32** data, UInt32* count);
			virtual void SetIndexData(const UInt32* data, UInt32 count);

			void GetVertexData(void** data, UInt32* dataLength);
			virtual void SetVertexData(const void* data, UInt32 dataLength);

			/*! @brief Get the Primitive Topology. Default value is PT_TriangleList. */ 
			PrimitiveTopologies GetPrimitiveTopology();

			/*! @brief Set the Primitive Topology. */ 
			void SetPrimitiveTopology(PrimitiveTopologies pt);

			List<InputElement>* GetVertexDeclaration();
			void SetVertexDeclaration(InputElement* elements, UInt32 count);

			void* GetNativeResource();

			bool GetReady();
			bool UseIndices();

		protected:

			void* vertexData;
			UInt32 vertexDataLength;

			UInt32* indexData;
			UInt32 indexCount;

			PrimitiveTopologies topology;

			List<InputElement> vertexDeclaration;

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		};
	}
}

