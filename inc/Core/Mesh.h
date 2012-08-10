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

			void GetVertexData(void** data, UInt32* dataLength);
			void SetVertexData(void* data, UInt32 dataLength);

			/*! @brief Get the Primitive Topology. Default value is PT_TriangleList. */ 
			PrimitiveTopologies GetPrimitiveTopology();
			void SetPrimitiveTopology(PrimitiveTopologies pt);

			List<InputElement>* GetVertexDeclaration();
			void SetVertexDeclaration(InputElement* elements, UInt32 count);

			virtual void* GetNativeResource();

			virtual bool GetReady();

		private:

			void* vertexData;
			UInt32 vertexDataLength;

			PrimitiveTopologies topology;

			List<InputElement> vertexDeclaration;

			virtual void loadFromStream(wcstring fileName, Stream* stream);
			virtual void saveToStream(wcstring fileName, Stream* stream);
		};
	}
}

