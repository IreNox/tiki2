#pragma once

#include "Core/ITexture.h"

namespace TikiEditor
{
	using namespace TikiEngine;
	using namespace TikiEngine::Resources;

	class FakeTexture : public ITexture
	{
	public:

		FakeTexture() : ITexture(0) {}
		~FakeTexture() {}

		void Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format) {}

		Int32 GetWidth() { return 0; }
		Int32 GetHeight() { return 0; }
		Vector2 GetSize() { return Vector2(); }
		TikiEngine::Rectangle GetRectangle() { return TikiEngine::Rectangle(); }

		bool GetDynamic() { return false; }

		void GetData(PixelFormat format, void** data, UInt32* dataLength) {}
		void SetData(PixelFormat format, void* data, UInt32 dataLength) {}

		void* GetNativeResource() { return 0; }
		bool GetReady() { return false; }

	protected:
		
		void loadFromStream(wcstring fileName, Stream* stream) {}
		void saveToStream(wcstring fileName, Stream* stream) {}

	};

}

