
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"

#include "Graphics/DllMain.h"
#include "Graphics/FbxLoader.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Model::Model(Engine* engine)
			: IModel(engine), indices(0), indicesCount(0), vertices(0), verticesSize(0)
		{
		}

		Model::~Model()
		{
			SafeDelete(&indices);
			SafeDelete(&vertices);
		}
		#pragma endregion

		#pragma region Member
		bool Model::GetIndexData(UInt32** indices, UInt32* count)
		{
			*indices = this->indices;
			*count = indicesCount;

			return (indices != 0);
		}

		bool Model::GetVertexData(void** vertices, UInt32* size)
		{
			*vertices = this->vertices;
			*size = this->verticesSize;

			return (vertices != 0);
		}


		void* Model::GetNativeResource()
		{
			return NULL;
		}

		bool Model::GetReady()
		{
			return (indices != 0 && vertices != 0);
		}
		#pragma endregion

		#pragma region Protected Member - Load/Save
		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			DllMain::FBXLoader->LoadFile(
				fileName,
				&indices,
				&indicesCount,
				&vertices,
				&verticesSize,
				&scene
			);
		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}
