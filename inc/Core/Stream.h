#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	namespace IO
	{
		class Stream
		{
		public:

			Stream() {}
			~Stream() {}

			virtual void Close() = 0;

			virtual Byte ReadByte() = 0;
			virtual void Read(void* data, Int32 offset, UPInt bytesCount) = 0;

			virtual void WriteByte(Byte byte) = 0;
			virtual void Write(void* data, Int32 offset, UPInt bytesCount) = 0;

			virtual UPInt GetLength() = 0;
			virtual void SetLength(UPInt len) = 0;

			virtual Int64 GetPosition() = 0;
			virtual void SetPosition(Int64 pos) = 0;
		};
	}
}