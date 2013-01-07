#pragma once

#include "Core/Stream.h"

namespace TikiEngine
{
	namespace IO
	{
		using namespace TikiEngine::IO;

		#pragma region Struct - TikiBinaryPart
		template <typename TPartType>
		struct TikiBinaryPart
		{
			UInt32 Id;

			TPartType Type;
			TPartType ArrayOf;
			UInt32 ArrayCount;

			UInt32 Start;
			UInt32 Length;
		};
		#pragma endregion

		template <typename THeaderType, typename TPartType, TPartType TNoArray>
		class TikiIOContext
		{
		public:

			#pragma region Class
			TikiIOContext()
				: binaryPartPointer(), binaryParts(), data(0)
			{
			}

			TikiIOContext(Stream* stream, bool readFullFile = true)
				: binaryParts(), binaryPartPointer(), data(0)
			{
				UInt32 len = (UInt32)stream->GetLength();

				if (readFullFile)
				{
					data = new Byte[len];
					stream->Read(data, 0, len);
					stream->SetPosition(0);
				}

				readHeader(stream);
				readParts(stream, readFullFile);
			}

			~TikiIOContext()
			{
				SafeDeleteArray(&data);
			}
			#pragma endregion

			#pragma region Member
			THeaderType* GetHeader()
			{
				return &binaryHeader;
			}
			#pragma endregion

			#pragma region Member - Read
			void* ReadPartPointer(UInt32 id)
			{
				if (data == 0)
				{
									
				}
				else
				{
					return binaryPartPointer[id];
				}
			}

			TikiBinaryPart<TPartType>& ReadPart(UInt32 id)
			{
				return binaryParts[id];
			}
			#pragma endregion

			#pragma region Member - Write
			UInt32 AddPart(void* pointer, UInt32 length, TPartType type)
			{
				return this->AddPart(pointer, length, type, TNoArray, 1);
			}

			UInt32 AddPart(void* pointer, UInt32 length, TPartType type, TPartType arrayOf, UInt32 arrayCount)
			{
				TikiBinaryPart<TPartType> bp;
				bp.Id = binaryParts.Count();
				bp.Length = length;

				bp.Type = type;
				bp.ArrayOf = arrayOf;
				bp.ArrayCount = arrayCount;

				binaryPartPointer.Add(pointer);
				binaryParts.Add(bp);

				return bp.Id;
			}

			void WriteToStream(Stream* stream)
			{
				writeInitData();
				writeToData();

				stream->Write(data, 0, binaryHeader.FileLength);
			}
			#pragma endregion

		protected:

			Byte* data;
			Stream* stream;

			THeaderType binaryHeader;

			List<void*> binaryPartPointer;
			List<TikiBinaryPart<TPartType>> binaryParts;

			#pragma region Protected Member - Read
			void readHeader(Stream* stream)
			{
				stream->Read(&binaryHeader, 0, sizeof(THeaderType));
			}

			void readParts(Stream* stream, bool readFullFile)
			{
				TikiBinaryPart<TPartType>* parts = new TikiBinaryPart<TPartType>[binaryHeader.PartCount];
				stream->Read(parts, 0, sizeof(TikiBinaryPart<TPartType>) * binaryHeader.PartCount);

				if (readFullFile)
				{
					UInt32 i = 0;
					while (i < binaryHeader.PartCount)
					{
						binaryPartPointer.Add(data + parts[i].Start);
						i++;
					}
				}

				binaryParts = List<TikiBinaryPart<TPartType>>(parts, binaryHeader.PartCount, false);
				delete[](parts);
			}
			#pragma endregion

			#pragma region Protected Member - Write
			void writeInitData()
			{
				binaryHeader.TIKI[0] = 'T';
				binaryHeader.TIKI[1] = 'I';
				binaryHeader.TIKI[2] = 'K';
				binaryHeader.TIKI[3] = 'I';
				binaryHeader.PartCount = binaryParts.Count();

				UInt32 pos = sizeof(THeaderType);
				pos += sizeof(TikiBinaryPart<TPartType>) * binaryHeader.PartCount;

				UInt32 i = 0;
				while (i < binaryParts.Count())
				{
					TikiBinaryPart<TPartType>& bp = binaryParts.GetRef(i);				
					bp.Start = pos;

					pos += bp.Length * bp.ArrayCount;
					i++;
				}

				binaryHeader.FileLength = pos;
			}

			void writeToData()
			{
				data = new Byte[binaryHeader.FileLength];
				Byte* writeTo = data;

				UInt32 i = sizeof(THeaderType);
				memcpy(writeTo, &binaryHeader, i);
				writeTo += i;

				i = sizeof(TikiBinaryPart<TPartType>) * binaryHeader.PartCount;
				memcpy(writeTo, binaryParts.GetInternalData(), i);
				writeTo += i;

				i = 0;
				while (i < binaryParts.Count())
				{				
					TikiBinaryPart<TPartType>& bp = binaryParts.GetRef(i);
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
		};
	}
}