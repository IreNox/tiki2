
#include "Graphics/ModelIOContext.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ModelIOContext::ModelIOContext()
			: binaryPartPointer(), binaryParts(), data(0)
		{
		}

		ModelIOContext::ModelIOContext(Stream* stream)
			: binaryParts(), binaryPartPointer()
		{
			UInt32 len = stream->GetLength();

			data = new Byte[len];
			stream->Read(data, 0, len);

			readHeader();
			readParts();
		}

		ModelIOContext::~ModelIOContext()
		{
			SafeDeleteArray(&data);
		}
		#pragma endregion

		#pragma region Member
		BinaryFileHeader* ModelIOContext::GetHeader()
		{
			return &binaryHeader;
		}
		#pragma endregion

		#pragma region Member - Read
		void* ModelIOContext::ReadPartPointer(UInt32 id)
		{
			return binaryPartPointer[id];
		}

		BinaryPart& ModelIOContext::ReadPart(UInt32 id)
		{
			return binaryParts[id];
		}
		#pragma endregion

		#pragma region Member - Write
		UInt32 ModelIOContext::AddPart(void* pointer, UInt32 length, PartType type)
		{
			return this->AddPart(pointer, length, type, PT_NoArray, 1);
		}

		UInt32 ModelIOContext::AddPart(void* pointer, UInt32 length, PartType type, PartType arrayOf, UInt32 arrayCount)
		{
			if (type == PT_String)
			{
				length = strlen((char*)pointer) + 1;
			}

			BinaryPart bp;
			bp.Id = binaryParts.Count();
			bp.Length = length;

			bp.Type = type;
			bp.ArrayOf = arrayOf;
			bp.ArrayCount = arrayCount;

			binaryPartPointer.Add(pointer);
			binaryParts.Add(bp);

			return bp.Id;
		}

		void ModelIOContext::WriteToStream(Stream* stream)
		{
			writeInitData();
			writeToData();

			stream->Write(data, 0, binaryHeader.FileLength);
		}
		#pragma endregion

		#pragma region Protected Member - Read
		void ModelIOContext::readHeader()
		{
			memcpy(&binaryHeader, data, sizeof(BinaryFileHeader));
		}

		void ModelIOContext::readParts()
		{
			BinaryPart* parts = new BinaryPart[binaryHeader.PartCount];
			memcpy(parts, data + sizeof(BinaryFileHeader), sizeof(BinaryPart) * binaryHeader.PartCount);

			UInt32 i = 0;
			while (i < binaryHeader.PartCount)
			{
				binaryPartPointer.Add(data + parts[i].Start);
				i++;
			}

			binaryParts = List<BinaryPart>(parts, binaryHeader.PartCount, false);
			delete[](parts);
		}
		#pragma endregion

		#pragma region Protected Member - Write
		void ModelIOContext::writeInitData()
		{
			binaryHeader.TIKI[0] = 'T';
			binaryHeader.TIKI[1] = 'I';
			binaryHeader.TIKI[2] = 'K';
			binaryHeader.TIKI[3] = 'I';
			binaryHeader.PartCount = binaryParts.Count();

			UInt32 pos = sizeof(BinaryFileHeader);
			pos += sizeof(BinaryPart) * binaryHeader.PartCount;

			UInt32 i = 0;
			while (i < binaryParts.Count())
			{
				BinaryPart& bp = binaryParts.GetRef(i);				
				bp.Start = pos;

				pos += bp.Length * bp.ArrayCount;
				i++;
			}

			binaryHeader.FileLength = pos;
		}

		void ModelIOContext::writeToData()
		{
			data = new Byte[binaryHeader.FileLength];
			Byte* writeTo = data;

			UInt32 i = sizeof(BinaryFileHeader);
			memcpy(writeTo, &binaryHeader, i);
			writeTo += i;

			i = sizeof(BinaryPart) * binaryHeader.PartCount;
			memcpy(writeTo, binaryParts.GetInternalData(), i);
			writeTo += i;

			i = 0;
			while (i < binaryParts.Count())
			{				
				BinaryPart& bp = binaryParts.GetRef(i);
				UInt32 len = bp.Length * bp.ArrayCount;

				if (len > 0)
				{
					memcpy(writeTo, binaryPartPointer.Get(i), len);
				}

				writeTo += len;
				i++;
			}		
		}
		#pragma endregion
	}
}