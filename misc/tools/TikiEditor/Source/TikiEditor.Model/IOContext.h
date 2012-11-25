#pragma once

#include "BinaryFileHeader.h"
#include "BinaryPart.h"
#include "MemoryPart.h"

#include "Core/Dictionary.h"

#include <string.h>

#include "Core/FileStream.h"

namespace TikiEditor
{
	using namespace TikiEngine::IO;

	public ref class IOContext
	{
	public:

		#pragma region Class
		IOContext()			
		{
			data = 0;

			binaryHeader = new BinaryFileHeader();

			binaryPartPointer = new List<void*>();
			binaryParts = new List<BinaryPart>();
			memoryParts = new Dictionary<UInt32, MemoryPart>();
		}

		IOContext(System::String^ fileName)
		{
			binaryHeader = new BinaryFileHeader();

			binaryPartPointer = new List<void*>();
			memoryParts = new Dictionary<UInt32, MemoryPart>();

			array<System::Byte>^ bytes = System::IO::File::ReadAllBytes(fileName);
			data = new Byte[bytes->Length];

			System::Runtime::InteropServices::Marshal::Copy(
				bytes,
				0,
				System::IntPtr(data),
				bytes->Length
			);

			readHeader();
			readParts();
		}

		~IOContext()
		{
			delete(binaryHeader);

			delete(binaryPartPointer);
			delete(binaryParts);
			delete(memoryParts);
		}
		#pragma endregion

		#pragma region Member
		BinaryFileHeader* GetHeader()
		{
			return binaryHeader;
		}
		#pragma endregion

		#pragma region Member - Read
		void* ReadPartPointer(UInt32 id)
		{
			return binaryPartPointer->Get(id);
		}

		BinaryPart& ReadPart(UInt32 id)
		{
			return binaryParts->GetRef(id);
		}
		#pragma endregion

		#pragma region Member - Write
		UInt32 AddPart(void* pointer, UInt32 length, PartType type)
		{
			return this->AddPart(pointer, length, type, PT_NoArray, 1);
		}

		UInt32 AddPart(void* pointer, UInt32 length, PartType type, PartType arrayOf, UInt32 arrayCount)
		{
			if (type == PT_String)
			{
				length = strlen((char*)pointer) + 1;
			}

			BinaryPart bp;
			bp.Id = binaryParts->Count();
			bp.Length = length;

			bp.Type = type;
			bp.ArrayOf = arrayOf;
			bp.ArrayCount = arrayCount;

			binaryPartPointer->Add(pointer);
			binaryParts->Add(bp);

			return bp.Id;
		}

		void WriteToFile(System::String^ fileName)
		{
			writeInitData();
			writeToData();

			wcstring str = (wcstring)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(fileName).ToPointer();
			FileStream* stream = new FileStream(str, FM_Write);

			stream->Write(data, 0, binaryHeader->FileLength);

			delete(stream);
		}
		#pragma endregion
		
	protected:

		Byte* data;

		BinaryFileHeader* binaryHeader;
		
		List<void*>* binaryPartPointer;
		List<BinaryPart>* binaryParts;
		Dictionary<UInt32, MemoryPart>* memoryParts;

		#pragma region Protected Member - Read
		void readHeader()
		{
			memcpy(binaryHeader, data, sizeof(BinaryFileHeader));
		}

		void readParts()
		{
			UInt32 pos = sizeof(BinaryFileHeader);
			UInt32 size = sizeof(BinaryPart) * binaryHeader->PartCount;

			BinaryPart* parts = new BinaryPart[binaryHeader->PartCount];
			memcpy(parts, data + pos, size);
			pos += size;

			UInt32 i = 0;
			while (i < binaryHeader->PartCount)
			{
				binaryPartPointer->Add(data + parts[i].Start);
				i++;
			}

			binaryParts = new List<BinaryPart>(parts, binaryHeader->PartCount, false);
		}
		#pragma endregion

		#pragma region Protected Member - Write
		void writeInitData()
		{
			binaryHeader->TIKI[0] = 'T';
			binaryHeader->TIKI[1] = 'I';
			binaryHeader->TIKI[2] = 'K';
			binaryHeader->TIKI[3] = 'I';
			binaryHeader->PartCount = binaryParts->Count();

			UInt32 pos = sizeof(BinaryFileHeader);
			pos += sizeof(BinaryPart) * binaryHeader->PartCount;
			
			UInt32 i = 0;
			while (i < binaryParts->Count())
			{
				BinaryPart& bp = binaryParts->GetRef(i);				
				bp.Start = pos;

				pos += bp.Length * bp.ArrayCount;
				i++;
			}

			binaryHeader->FileLength = pos;
		}

		void writeToData()
		{
			data = new Byte[binaryHeader->FileLength];
			Byte* writeTo = data;

			UInt32 i = sizeof(BinaryFileHeader);
			memcpy(writeTo, binaryHeader, i);
			writeTo += i;

			i = sizeof(BinaryPart) * binaryHeader->PartCount;
			memcpy(writeTo, binaryParts->GetInternalData(), i);
			writeTo += i;

			i = 0;
			while (i < binaryParts->Count())
			{				
				BinaryPart& bp = binaryParts->GetRef(i);
				UInt32 len = bp.Length * bp.ArrayCount;

				if (len > 0)
				{
					memcpy(writeTo, binaryPartPointer->Get(i), len);
				}

				writeTo += len;
				i++;
			}		
		}
		#pragma endregion

	};
}