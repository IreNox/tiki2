
#include "Core/MemoryStream.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace IO
	{
		#pragma region Class
		MemoryStream::MemoryStream()
			: dataByte(0), length(0), position(0)
		{
		}

		MemoryStream::MemoryStream(void* data, UPInt length)
			: dataByte(new Byte[length]), length(length), position(0)
		{
			memcpy(dataByte, data, length);
		}

		MemoryStream::~MemoryStream()
		{
			SafeDeleteArray(&dataByte);
		}
		#pragma endregion

		#pragma region Member - Stream
		void MemoryStream::Close()
		{
			position = 0;
		}

		Byte MemoryStream::ReadByte()
		{
			return dataByte[position++];
		}

		void MemoryStream::Read(void* data, Int32 offset, UPInt bytesCount)
		{
			position += offset;

			memcpy(data, dataByte + position, bytesCount);

			position += bytesCount;
		}

		void MemoryStream::WriteByte(Byte byte)
		{
			if (position > length)
			{
				extendData(position);
			}

			dataByte[position] = byte;
		}

		void MemoryStream::Write(void* data, Int32 offset, UPInt bytesCount)
		{
			UPInt index = position + offset;
			UPInt indexEnd = index + bytesCount;

			if (indexEnd > length)
			{
				extendData(indexEnd);
			}

			memcpy(dataByte + index, data, bytesCount);
		}

		UPInt MemoryStream::GetLength()
		{
			return length;
		}

		void MemoryStream::SetLength(UPInt len)
		{
			extendData(len);
		}

		Int64 MemoryStream::GetPosition()
		{
			return position;
		}

		void MemoryStream::SetPosition(Int64 pos)
		{
			position = (PInt)pos;
		}
		#pragma endregion

		#pragma region Private Member
		void MemoryStream::extendData(UPInt size)
		{
			Byte* newData = new Byte[size];

			if (dataByte != 0)
			{
				UPInt copySize = size < length ? size : length;

				memcpy(newData, dataByte, copySize);
				SafeDeleteArray(&dataByte);
			}

			length = size;
			dataByte = newData;
		}
		#pragma endregion
	}
}