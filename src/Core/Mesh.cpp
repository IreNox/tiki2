
#include "Core/Engine.h"
#include "Core/Mesh.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: EngineObject(engine), vertexData(0), vertexDataLength(0), vertexDeclaration()
		{
		}

		Mesh::~Mesh()
		{
			if (this->vertexData != 0)
			{
				delete(this->vertexData);
				this->vertexData = 0;
			}	
		}
		#pragma endregion

		#pragma region Member
		bool Mesh::GetReady()
		{
			return (vertexData != 0) && (vertexDeclaration.Count() != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void Mesh::SetVertexData(void* data, UInt32 dataLength)
		{
			if (vertexData != 0)
			{
				delete(vertexData);
				vertexData = 0;
			}

			vertexData = new Byte[dataLength];
			vertexDataLength = dataLength;

			memcpy(vertexData, data, dataLength);
		}

		void Mesh::GetVertexData(void** data, UInt32* dataLength)
		{
			*data = vertexData;
			*dataLength = vertexDataLength;
		}

		List<InputElement>* Mesh::GetVertexDeclaration()
		{
			return &vertexDeclaration;
		}

		void Mesh::SetVertexDeclaration(InputElement* elements, UInt32 count)
		{
			vertexDeclaration.Clear();

			UInt32 i = 0;
			while (i < count)
			{
				vertexDeclaration.Add(elements[i]);
				i++;
			}
		}
		#pragma endregion
	}
}