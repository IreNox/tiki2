

#include "Core/FileStream.h"

namespace TikiEngine
{
	namespace IO
	{
		#pragma region Class
		FileStream::FileStream(wstring fileName, FileMode mode)
			: Stream(), handle(0)
		{
			switch (mode)
			{
			case FM_Read:
				handle = _wfopen(fileName.c_str(), L"r");
				break;
			case FM_ReadWrite:
				handle = _wfopen(fileName.c_str(), L"w+");
				break;
			case FM_Write:
				handle = _wfopen(fileName.c_str(), L"w");
				break;
			case FM_WriteAppend:
				handle = _wfopen(fileName.c_str(), L"a");
				break;
			}
		}

		FileStream::~FileStream()
		{
			this->Close();
		}
		#pragma endregion

		#pragma region Member
		void FileStream::Close()
		{
			if (handle != 0)
			{
				fclose(handle);
				handle = 0;
			}
		}
		#pragma endregion

		#pragma region Member - Read
		Byte FileStream::ReadByte()
		{
			Byte byte = 0;

			fread(&byte, 1, 1, handle);

			return byte;
		}

		void FileStream::Read(void* data, Int32 offset, UInt32 bytesCount)
		{
			Byte* ptr = (Byte*)data;
			ptr += offset;

			fread(ptr, bytesCount, 1, handle);
		}
		#pragma endregion

		#pragma region Member - Write
		void FileStream::WriteByte(Byte byte)
		{
			fwrite(&byte, 1, 1, handle);
		}

		void FileStream::Write(void* data, Int32 offset, UInt32 bytesCount)
		{
			Byte* ptr = (Byte*)data;
			ptr += offset;

			fwrite(ptr, bytesCount, 1, handle);
		}
		#pragma endregion

		#pragma region Member - Properties
		Int32 FileStream::GetLength()
		{
			fseek(handle, 0, SEEK_END);
			return ftell(handle);
			fseek(handle, 0, SEEK_SET);
		}

		void FileStream::SetLength(Int32 len)
		{
			throw "Not supported";
		}

		Int64 FileStream::GetPosition()
		{
			Int64 pos = 0;

			fgetpos( 
				handle,
				&pos 
			);

			return pos;
		}

		void FileStream::SetPosition(Int64 pos)
		{
			fsetpos( 
				handle,
				&pos
			);
		}
		#pragma endregion
	}
}