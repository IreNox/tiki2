
#include "Core/Engine.h"
#include "Core/Mesh.h"

#include "Core/HelperHash.h"
#include "Core/DefaultVertex.h"

#include <sstream>

namespace TikiEngine
{
	namespace Resources
	{
		using namespace std;
		using namespace TikiEngine::Vertices;

		#pragma region Class
		Mesh::Mesh(Engine* engine)
			: IResource(engine), vertexData(0), vertexDataLength(0), vertexDeclaration(), indexData(0), indexCount(0), topology(PT_TriangleList)
		{
		}

		Mesh::~Mesh()
		{
			SafeDeleteArray(&indexData);
			SafeDeleteArray(&vertexData);
		}
		#pragma endregion

		#pragma region Member
		bool Mesh::GetReady()
		{
			return (vertexData != 0) && (vertexDeclaration.Count() != 0) && (indexCount != 0 ? indexData != 0 : true);
		}

		bool Mesh::UseIndices()
		{
			return indexCount != 0;
		}

		void* Mesh::GetNativeResource()
		{
			return 0;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void Mesh::SetVertexData(void* data, UInt32 dataLength)
		{
			SafeDeleteArray(&vertexData);

			vertexData = new Byte[dataLength];
			vertexDataLength = dataLength;

			memcpy(vertexData, data, dataLength);
		}

		void Mesh::GetVertexData(void** data, UInt32* dataLength)
		{
			*data = vertexData;
			*dataLength = vertexDataLength;
		}

		void Mesh::SetIndexData(UInt32* data, UInt32 count)
		{
			SafeDeleteArray(&indexData);

			indexData = new UInt32[count];
			indexCount = count;

			memcpy(
				indexData,
				data,
				count * sizeof(UInt32)
			);
		}

		void Mesh::GetIndexData(UInt32** data, UInt32* count)
		{
			*data = indexData;
			*count = indexCount;
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
			UInt32 bufferIndex = 0;
			char buffer[256];
			ZeroMemory(buffer, 256);
		
			UPInt size = stream->GetLength();	
			char* file = new char[size + 1];
			stream->Read(file, 0, size);
			file[size] = 10;

			#pragma region Parse Data
			bool newLine = true;
			bool bufferWork = false;

			/* BlockMode:
			 *
			 * 0 - Comment
			 * 1 - v - Position
			 * 2 - vn - Normal
			 * 3 - vt - UV
			 * 4 - f - Vertex
			 */

			Vector3 vector;
			List<Vector3> positions;
			List<Vector3> normals;
			List<Vector2> uvs;

			Dictionary<UInt32, UInt32> vertexHash;

			List<UInt32> indices;
			List<DefaultVertex> vertices;

			DefaultVertex vertex;
			List<DefaultVertex> quad;
	
			int blockMode = 0;
			int blockCount = 0;

			int miscVar = 0;

			UInt32 i = 0;
			while (i <= size)
			{
				if (newLine)
				{
					if (file[i] == 'v')
					{
						blockCount = 3;
						if (file[i + 1 ] == ' ')
						{
							blockMode = 1;
						}
						else if (file[i + 1 ] == 'n')
						{
							blockMode = 2;
						}
						else if (file[i + 1 ] == 't')
						{
							blockMode = 3;
							blockCount = 2;
						}
					}
					else if (file[i] == 'f')
					{
						blockMode = 4;
						blockCount = 12;
					}
				}
				newLine = false;

				switch (file[i])
				{
				case '#':
					blockMode = 0;
					break;
				case 10:
				case 13:
					bufferWork = true;
					newLine = true;
					break;
				case '/':
				case ' ':
					bufferWork = true;
					break;
				default:
					if (bufferIndex == 256)
					{
						throw "Error buffer size";
					}

					buffer[bufferIndex++] = file[i];
					break;
				}

				if (bufferWork)
				{
					if (blockMode != 0)
					{
						if (blockMode != 4 && bufferIndex > 3)
						{
							float val;
							string str = buffer;
							istringstream is;

							is.str(str);
							is >> val;					

							switch (blockCount)
							{
							case 3:
								vector.X = val;
								break;
							case 2:
								vector.Y = val;
								break;
							case 1:
								vector.Z = val;
								break;
							}

							blockCount--;

							if (blockCount == 0)
							{
								switch (blockMode)
								{
								case 1:
									positions.Add(vector);
									break;
								case 2:
									normals.Add(vector);
									break;
								case 3:
									uvs.Add(Vector2(vector.Y, vector.Z));
									break;
								}
							}
						}
						else if (blockMode == 4 && buffer[0] != 'f')
						{
							if (bufferIndex > 0)
							{
								int val;
								string str = buffer;
								istringstream is;

								is.str(str);
								is >> val;
								val--;

								if (miscVar == 0)
								{
									vertex.Position[0] = positions[val].X;
									vertex.Position[1] = positions[val].Y;
									vertex.Position[2] = positions[val].Z;
								}
								else if (miscVar == 1)
								{
									vertex.UV[0] = uvs[val].X;
									vertex.UV[1] = uvs[val].Y;
								}
								else
								{
									vertex.Normal[0] = normals[val].X;
									vertex.Normal[1] = normals[val].Y;
									vertex.Normal[2] = normals[val].Z;

									miscVar = -1;
									quad.Add(vertex);
								}

								miscVar++;
							}

							if (newLine)
							{
								List<UInt32> data;

								if (quad.Count() == 4)
								{
									data.Add(0);
									data.Add(2);
									data.Add(1);
									data.Add(0);
									data.Add(3);
									data.Add(2);

								}
								else if (quad.Count() == 3)
								{
									data.Add(0);
									data.Add(2);
									data.Add(1);
								}
								else
								{
									throw "Face type not supported.";
								}

								UInt32 i = 0;
								while (i < data.Count())
								{
									UInt32 hash = HelperHash::Hash(quad[data[i]]);

									if (vertexHash.ContainsKey(hash))
									{
										indices.Add(vertexHash[hash]);
									}
									else
									{
										indices.Add(vertices.Count());
										vertices.Add(quad[data[i]]);
									}

									i++;
								}

								quad.Clear();
							}
						}
					}
			
					if (blockMode == 0 || newLine)
					{
						blockMode = 0;
						blockCount = 0;
					}

					bufferWork = false;

					bufferIndex = 0;
					ZeroMemory(buffer, 256);
				}

				i++;
			}
			#pragma endregion

			vertexData = vertices.ToArray();
			vertexDataLength = vertices.Count() * sizeof(DefaultVertex);

			indexData = indices.ToArray();
			indexCount = indices.Count();

			this->SetVertexDeclaration(
				DefaultVertex::Declaration,
				DefaultVertex::DeclarationCount
			);

			delete[](file);
		}

		void Mesh::saveToStream(wcstring fileName, Stream* stream)
		{
			//TODO: save mesh
		}
		#pragma endregion
	}
}