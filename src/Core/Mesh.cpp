
#include "Core/Engine.h"
#include "Core/Mesh.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: IResource(engine), vertexData(0), vertexDataLength(0), vertexDeclaration(), topology(PT_TriangleList)
		{
		}

		Mesh::~Mesh()
		{
			SafeDelete(&vertexData);
		}
		#pragma endregion

		#pragma region Member
		bool Mesh::GetReady()
		{
			return (vertexData != 0) && (vertexDeclaration.Count() != 0);
		}

		void* Mesh::GetNativeResource()
		{
			return 0;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void Mesh::SetVertexData(void* data, UInt32 dataLength)
		{
			SafeDelete(&vertexData);

			vertexData = new Byte[dataLength];
			vertexDataLength = dataLength;

			memcpy(vertexData, data, dataLength);
		}

		void Mesh::GetVertexData(void** data, UInt32* dataLength)
		{
			*data = vertexData;
			*dataLength = vertexDataLength;
		}

		PrimitiveTopologies Mesh::GetPrimitiveTopology()
		{
			return topology;
		}

		void Mesh::SetPrimitiveTopology(PrimitiveTopologies pt)
		{
			topology = pt;
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

		#pragma region Protected Member
		void Mesh::loadFromStream(wcstring fileName, Stream* stream)
		{
			//TODO: load mesh
		}

		void Mesh::saveToStream(wcstring fileName, Stream* stream)
		{
			//TODO: save mesh
		}
		#pragma endregion
	}
}