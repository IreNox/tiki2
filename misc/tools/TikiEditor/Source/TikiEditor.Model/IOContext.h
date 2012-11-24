#pragma once

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

#include "BinaryFileHeader.h"
#include "BinaryPart.h"
#include "MemoryPart.h"

#include "Core/Dictionary.h"

namespace TikiEditor
{
	public ref class IOContext
	{
	public:

		IOContext()			
		{
			data = 0;

			binaryHeader = new BinaryFileHeader();

			partPointer = new List<void*>();
			binaryParts = new List<BinaryPart>();
			memoryParts = new Dictionary<UInt32, MemoryPart>();
		}

		IOContext(System::String^ fileName)
		{
			// Not implemented
		}

		~IOContext()
		{
			delete(binaryHeader);

			delete(partPointer);
			delete(binaryParts);
			delete(memoryParts);
		}

		UInt32 AddPart(void* pointer, UInt32 length, PartType type)
		{
			return this->AddPart(pointer, length, type, PT_NoArray, 1);
		}

		UInt32 AddPart(void* pointer, UInt32 length, PartType type, PartType arrayOf, UInt32 arrayCount)
		{
			if (type == PT_String)
			{
				length = strlen((char*)pointer);
			}

			BinaryPart bp;
			bp.Id = binaryParts->Count();
			bp.Length = length;

			bp.Type = type;
			bp.ArrayOf = arrayOf;
			bp.ArrayCount = arrayCount;

			partPointer->Add(pointer);
			binaryParts->Add(bp);

			return bp.Id;
		}

		BinaryFileHeader* GetHeader()
		{
			return binaryHeader;
		}

		void WriteToFile(System::String^ fileName)
		{
			writeInitData();
			writeToData();

			array<System::Byte>^ bytes = gcnew array<System::Byte>(binaryHeader->FileLength);

			System::Runtime::InteropServices::Marshal::Copy(
				System::IntPtr(data),
				bytes,
				0,
				binaryHeader->FileLength
			);

			System::IO::File::WriteAllBytes(fileName, bytes);
		}

	protected:

		Byte* data;

		BinaryFileHeader* binaryHeader;
		
		List<void*>* partPointer;
		List<BinaryPart>* binaryParts;
		Dictionary<UInt32, MemoryPart>* memoryParts;

		#pragma region Protected Member - Read
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

				pos += bp.Length + bp.ArrayCount;
				i++;
			}

			binaryHeader->FileLength = pos;
		}

		void writeToData()
		{
			data = new Byte[binaryHeader->FileLength];

			UInt32 i = sizeof(BinaryFileHeader);
			memcpy(data, binaryHeader, i);
			data += i;

			i = sizeof(BinaryPart) * binaryHeader->PartCount;
			memcpy(data, binaryParts->GetInternalData(), i);
			data += i;

			i = 0;
			while (i < binaryParts->Count())
			{				
				BinaryPart& bp = binaryParts->GetRef(i);
				UInt32 len = bp.Length + bp.ArrayCount;

				memcpy(data, partPointer->Get(i), len);

				data += len;
				i++;
			}		
		}
		#pragma endregion

	};
}