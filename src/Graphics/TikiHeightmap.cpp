
#include "Graphics/TikiHeightmap.h"

namespace TikiEngine
{
	TikiHeightmap::TikiHeightmap(int size)
		: size(size), color(0), detail(0), elevation(0)
	{
		this->InitializeCube(size);
	}

	TikiHeightmap::~TikiHeightmap()
	{
		if (color != 0) color->Dispose();
		if (detail != 0) detail->Dispose();
		if (elevation != 0) elevation->Dispose();
	}

	void TikiHeightmap::SetColor(IHeightmap* color)
	{
		this->color = color->Scale(size);
	}

	void TikiHeightmap::SetDetail(IHeightmap* detail)
	{
		this->detail = detail->Scale(size);
	}

	void TikiHeightmap::SetElevation(IHeightmap* elevation)
	{
		this->elevation = elevation->Scale(size);
	}

	HeightmapLayer TikiHeightmap::GetLayerMask()
	{
		return HeightmapLayer_None;
	}

	void TikiHeightmap::Get(Int32 x, Int32 y, HeightmapSample* sample)
	{
		this->Get(x, y, 0, sample);
	}

	void TikiHeightmap::Get(Int32 x, Int32 y, Int32 z, HeightmapSample* sample)
	{
		//HeightmapSample tmp = HeightmapSample();

		//color->Get(x, y, z, &tmp);
		//sample->Diffuse = RGB(x, y, z) || 0xFF000000; // 0xFF0000FF;

		elevation->Get(x, y, z, sample);
		//sample->Elevation = tmp.Elevation;

		//detail->Get(x, y, z, &tmp);
		//sample->Detail0 = tmp.Detail0;
		//sample->Detail1 = tmp.Detail1;
		//sample->Detail2 = tmp.Detail2;
		//sample->Detail3 = tmp.Detail3;
	}

	void TikiHeightmap::DisposeUnmanaged()
	{
		Disposable::DisposeUnmanaged();
	}

	void TikiHeightmap::DisposeManaged()
	{
		Disposable::DisposeManaged();
	}
}