#pragma once

#include "Core/Stream.h"

namespace TikiEngine
{
	namespace IO
	{
		class MemoryStream : public Stream
		{
		public:

			MemoryStream();
			MemoryStream(void* data, UPInt length);
			~MemoryStream();

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

			union
			{
				void* dataVoid;
				Byte* dataByte;
			};
			UPInt length;

			UPInt position;

			void extendData(UPInt size);

		};
	}
}