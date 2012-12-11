#pragma once

#define TIKI_EDITOR

#include "Core/TypeDef.h"

#include "Graphics/TikiMesh.h"

#include <d3d10.h>
#include <d3dx10mesh.h>

namespace TikiEditor
{
	using namespace TikiEngine::Resources;

	class D3DX10MeshLoader
	{
	public:

		D3DX10MeshLoader();
		~D3DX10MeshLoader();

		void ImportMesh(TikiMesh* m);

		void SetIndices(UInt32* indexData, UInt32 indexCount);
		void SetVertices(void* vertexData, UInt32 vertexCount);
		void SetLayout(D3D10_INPUT_ELEMENT_DESC* desc, UInt32 layoutCount);

		void ConvertToAdjacency(TikiMesh* m);
		void ConvertToAdjacency(UInt32** indexData, UInt32* indexCount);

	private:

		UInt32* indexData;
		UInt32 indexCount;

		void* vertexData;
		UInt32 vertexCount;

		UInt32 layoutCount;
		D3D10_INPUT_ELEMENT_DESC* layout;

		ID3DX10Mesh* mesh;
		ID3D10Device* device;

		void setData();

	};
}

