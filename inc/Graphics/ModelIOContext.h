#pragma once

#include "Graphics/ModelBinaryData.h"

#include "Core/TypeDef.h"
#include "Core/Stream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		class ModelIOContext
		{
		public:

			ModelIOContext();
			ModelIOContext(Stream* stream);
			~ModelIOContext();

			BinaryFileHeader* GetHeader();

			void* ReadPartPointer(UInt32 id);
			BinaryPart& ReadPart(UInt32 id);

			UInt32 AddPart(void* pointer, UInt32 length, PartType type);
			UInt32 AddPart(void* pointer, UInt32 length, PartType type, PartType arrayOf, UInt32 arrayCount);

			void WriteToStream(Stream* stream);

		protected:

			Byte* data;

			BinaryFileHeader binaryHeader;

			List<void*> binaryPartPointer;
			List<BinaryPart> binaryParts;

			void readHeader();
			void readParts();

			void writeInitData();
			void writeToData();

		};
	}
}