// Dies ist die Haupt-DLL.

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Cloddy.Kernel.lib")
#pragma comment(lib, "Cloddy.API.lib")
#pragma comment(lib, "Cloddy.Core.lib")
#pragma comment(lib, "Cloddy.CodeX.lib")
#pragma comment(lib, "Cloddy.Extensions.lib")

#include "TikiEditor.Cloddy.h"

#include "Cloddy/CloddyLocalDataset.h"
#include "Cloddy/HeightmapSample.h"

namespace TikiEditor
{
	using namespace Cloddy::Extensions;
	using namespace Cloddy::API::Heightmaps;
	using namespace ::System::Runtime::InteropServices;

	Heightmap::Heightmap()
	{
		heightMap = nullptr;
	}

	void Heightmap::LoadHeightmap(::System::String^ fileName)
	{
		this->UnloadHeightmap();

		char* file = (char*)Marshal::StringToHGlobalAnsi(fileName).ToPointer();
		CodeX::String test = CodeX::String(file);
		
		CloddyLocalDataset* dataSet = new CloddyLocalDataset(test, true, 13);
		
		width = dataSet->GetHeightmap()->GetWidth();
		height = dataSet->GetHeightmap()->GetHeight();

		heightMap = gcnew ::System::IntPtr(dataSet);
	}

	void Heightmap::UnloadHeightmap()
	{
		if (heightMap == nullptr) return;

		CloddyLocalDataset* dataSet = (CloddyLocalDataset*)heightMap->ToPointer();
		dataSet->Dispose();

		heightMap = nullptr;
	}

	void Heightmap::FillData(array<::System::Int32>^ data)
	{
		CloddyLocalDataset* dataSet = (CloddyLocalDataset*)heightMap->ToPointer();
		IHeightmap* heightmap = dataSet->GetHeightmap();
		HeightmapSample sample;

		::System::UInt64 i = 0;
		::System::UInt64 c = width * height;

		while (i < c)
		{
			::System::UInt64 x = i % width;
			::System::UInt64 y = height - (i / width);

			heightmap->Get(
				(int)x,
				(int)y,
				&sample
			);

			data[i] = sample.Elevation;

			i++;
		}
	}

	::System::Int32 Heightmap::GetWidth()
	{
		return width;
	}

	::System::Int32 Heightmap::GetHeight()
	{
		return height;
	}

}