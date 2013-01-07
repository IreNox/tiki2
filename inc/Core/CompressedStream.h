#pragma once

#include "Core/Stream.h"

namespace TikiEngine
{
	namespace IO
	{
		enum CompressedOpenMode
		{
			COM_Read,
			COM_Write
		};

		class CompressedStream : public Stream
		{
		public:

			CompressedStream(wstring fileName, CompressedOpenMode mode);
			~CompressedStream();

			void Close();

			Byte ReadByte();
			void Read(void* data, Int32 offset, UPInt bytesCount);

			void WriteByte(Byte byte);
			void Write(void* data, Int32 offset, UPInt bytesCount);

			UPInt GetLength();
			void SetLength(UPInt len);

			Int64 GetPosition();
			void SetPosition(Int64 pos);

		private:

			wstring fileName;
			CompressedOpenMode mode;

			FILE* file;
			void* bzipFile;

			UInt64 pos;

		};
	}
}