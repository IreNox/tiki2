#pragma once

#include "Core/IModel.h"

#include "fbxsdk.h"

namespace TikiEngine
{
	namespace Resources
	{
		class Model : public IModel
		{
		public:

			Model(Engine* engine);
			~Model();

			void* GetNativeResource();

			bool GetIndexData(UInt32** indices, UInt32* count);
			bool GetVertexData(void** vertices, UInt32* size);

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			UInt32* indices;
			void* vertices;

			UInt32 indicesCount;
			UInt32 verticesSize;
			
			FbxScene* scene;

		};
	}
}