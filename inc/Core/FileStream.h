#pragma once

#include "Core/TypeInc.h"
#include "Core/Stream.h"

#include <stdio.h>

namespace TikiEngine
{
	namespace IO
	{
		enum FileMode
		{
			FM_Read,
			FM_ReadWrite,
			FM_Write,
			FM_WriteAppend
		};

		class FileStream : public Stream
		{
		public:

			FileStream(wstring fileName, FileMode mode);
			~FileStream();

			void Close();

			Byte ReadByte();
			void Read(void* data, Int32 offset, UInt32 bytesCount);

			void WriteByte(Byte byte);
			void Write(void* data, Int32 offset, UInt32 bytesCount);

			Int32 GetLength();
			void SetLength(Int32 len);

			Int64 GetPosition();
			void SetPosition(Int64 pos);

		private:

			FILE* handle;
		};
	}
}