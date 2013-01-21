#pragma once

#include "Core/TypeGlobals.h"
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

			inline bool IsOpen() { return handle != 0; }

			void Close();

			Byte ReadByte();
			void Read(void* data, Int32 offset, UPInt bytesCount);

			void WriteByte(Byte byte);
			void Write(const void* data, Int32 offset, UPInt bytesCount);

			UPInt GetLength();
			void SetLength(UPInt len);

			Int64 GetPosition();
			void SetPosition(Int64 pos);

		private:

			FILE* handle;
		};
	}
}