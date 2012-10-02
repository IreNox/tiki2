// TikiEditor.Cloddy.h

#pragma once

namespace TikiEditor
{
	using namespace System;

	public ref class Heightmap
	{
	public:

		Heightmap();
			
		void LoadHeightmap(System::String^ fileName);
		void UnloadHeightmap();

		void FillData(array<Int32>^ data);

		Int32 GetWidth();
		Int32 GetHeight();

	private:

		Int32 width;
		Int32 height;

		IntPtr^ heightMap;

	};
}
