
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3D10.lib")
#pragma comment(lib, "D3DX10.lib")

#include "D3DX10MeshLoader.h"

float epsilon = 0.001f;

namespace TikiEditor
{
	#pragma region Class
	D3DX10MeshLoader::D3DX10MeshLoader(void)
		: indexData(0), indexCount(0), vertexData(0), vertexCount(0), layout(0), layoutCount(0), mesh(0)
	{
		IDXGIAdapter* adapter = 0;
		IDXGIFactory* factory = 0;
		CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);

		factory->EnumAdapters(0, &adapter);

		D3D10CreateDevice(adapter, D3D10_DRIVER_TYPE_HARDWARE, 0, 0, D3D10_SDK_VERSION, &device);
	}

	D3DX10MeshLoader::~D3DX10MeshLoader()
	{
		if (device) device->Release();
		if (mesh) mesh->Release();
	}
	#pragma endregion

	#pragma region Member - Set
	void D3DX10MeshLoader::ImportMesh(TikiMesh* m)
	{
		UInt32 vertenLen = 0;

		m->GetVertexData(&vertexData, &vertenLen);
		m->GetIndexData(&indexData, &indexCount);

		vertexCount = vertenLen / 64;

		D3D10_INPUT_ELEMENT_DESC desc[5] = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
		};

		layout = new D3D10_INPUT_ELEMENT_DESC[5];
		memcpy(layout, desc, sizeof(desc));
		layoutCount = 5;

		setData();
	}

	void D3DX10MeshLoader::SetIndices(UInt32* indexData, UInt32 indexCount)
	{
		this->indexData = indexData;
		this->indexCount = indexCount;

		setData();
	}

	void D3DX10MeshLoader::SetVertices(void* vertexData, UInt32 vertexCount)
	{
		this->vertexData = vertexData;
		this->vertexCount = vertexCount;

		setData();
	}

	void D3DX10MeshLoader::SetLayout(D3D10_INPUT_ELEMENT_DESC* desc, UInt32 layoutCount)
	{
		this->layout = desc;
		this->layoutCount = layoutCount;

		setData();
	}
	#pragma endregion

	#pragma region Member - Convert
	void D3DX10MeshLoader::ConvertToAdjacency(TikiMesh* m)
	{
		UInt32* iD;
		UInt32 iC;
		this->ConvertToAdjacency(&iD, &iC);

		m->SetAdjacencyIndexData(iD, iC);
	}

	void D3DX10MeshLoader::ConvertToAdjacency(UInt32** indexData, UInt32* indexCount)
	{
		if (mesh == 0) return;

		HRESULT r = mesh->GenerateAdjacencyAndPointReps(epsilon);
		if (FAILED(r))
			throw "Error";

		r = mesh->GenerateGSAdjacency();
		if (FAILED(r)) 
			throw "Error";

		ID3DX10MeshBuffer* buffer;
		r = mesh->GetIndexBuffer(&buffer);
		if (FAILED(r))
			throw "Error";

		Byte* data = 0;
		SIZE_T size = 0;
		buffer->Map((void**)&data, &size);

		*indexCount = size / 4;
		*indexData = new UInt32[*indexCount];
		memcpy(*indexData, data, size);

		buffer->Unmap();
		buffer->Release();
	}
	#pragma endregion

	#pragma region Private Member
	void D3DX10MeshLoader::setData()
	{
		if (indexData != 0 && indexCount != 0 &&
			vertexData != 0 && vertexCount != 0 &&
			layout != 0 && layoutCount != 0)
		{
			if (mesh)
			{
				mesh->Release();
				mesh = 0;
			}

			 HRESULT r = D3DX10CreateMesh(
				device,
				layout,
				layoutCount,
				layout[0].SemanticName,
				vertexCount,
				indexCount / 3,
				1,
				&mesh
			);
			if (FAILED(r))
				throw "Error";

			r = mesh->SetVertexData(0, vertexData);
			if (FAILED(r))
				throw "Error";
			
			r = mesh->SetIndexData(indexData, indexCount);
			if (FAILED(r)) 
				throw "Error";

		}
	}
	#pragma endregion
}


