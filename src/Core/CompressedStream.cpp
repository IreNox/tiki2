
#include "Core/CompressedStream.h"
#include "extern/bzlib.h"

#include "Core/NotSupportedException.h"

namespace TikiEngine
{
	namespace IO
	{
		#pragma region Class
		CompressedStream::CompressedStream(wstring fileName, CompressedOpenMode mode)
			: Stream(), fileName(fileName), mode(mode), bzipFile(0), pos(0), file(0)
		{
			if (mode == COM_Write)
			{
				int r;				
				_wfopen_s(&file, fileName.c_str(), L"w");

				bzipFile = BZ2_bzWriteOpen(&r, file, 9, 0, 30);

				if (r != BZ_OK)
				{
					throw Exception("Can't open compressed file.");
				}
			}
		}

		CompressedStream::~CompressedStream()
		{
			if (mode == COM_Write)
			{
				int r;
				BZ2_bzWriteClose64(&r, bzipFile, 1, 0, 0, 0, 0);

				if (r != BZ_OK)
				{
					throw Exception("Can't close compressed file.");
				}

				fclose(file);
			}
		}
		#pragma endregion

		#pragma region Member
		void CompressedStream::Close()
		{
		}
		#pragma endregion

		#pragma region Member - Read
		Byte CompressedStream::ReadByte()
		{
			throw NotSupportedException();
		}

		void CompressedStream::Read(void* data, Int32 offset, UPInt bytesCount)
		{
			Byte* ptr = (Byte*)data;
			ptr += offset;

			int r;				
			_wfopen_s(&file, fileName.c_str(), L"r");

			bzipFile = BZ2_bzReadOpen(&r, file, 0, 0, 0, (int)pos);

			BZ2_bzRead(&r, bzipFile, ptr, bytesCount);

			if (r != BZ_OK)
			{
				throw Exception("Can't read from compressed file.");
			}

			BZ2_bzReadClose(&r, bzipFile);
			fclose(file);
		}
		#pragma endregion

		#pragma region Member - Write
		void CompressedStream::WriteByte(Byte byte)
		{
			throw NotSupportedException();
		}

		void CompressedStream::Write(void* data, Int32 offset, UPInt bytesCount)
		{
			Byte* ptr = (Byte*)data;
			ptr += offset;

			int r;
			BZ2_bzWrite(&r, bzipFile, ptr, bytesCount);

			if (r != BZ_OK)
			{
				throw Exception("Can't write to compressed file.");
			}
		}
		#pragma endregion

		#pragma region Member - Get/Set
		UPInt CompressedStream::GetLength()
		{
			throw NotSupportedException();
		}

		void CompressedStream::SetLength(UPInt len)
		{
			throw NotSupportedException();
		}

		Int64 CompressedStream::GetPosition()
		{
			return pos;
		}

		void CompressedStream::SetPosition(Int64 pos)
		{
			this->pos = pos;
		}
		#pragma endregion
	}
}