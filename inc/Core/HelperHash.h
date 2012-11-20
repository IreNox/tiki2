#pragma once

#include "Core/TypeDef.h"

#include <stdio.h>

namespace TikiEngine
{
	class HelperHash
	{
	public:
		
		#define UPDC32(octet,crc) ()

		inline static UInt32 Hash(Byte* buf, UInt32 len)
		{
			register UInt32 oldcrc32;

			oldcrc32 = 0xFFFFFFFF;

			for ( ; len; --len, ++buf)
			{
				oldcrc32 = crc_32_tab[(oldcrc32 ^ *buf) & 0xff] ^ (oldcrc32 >> 8);
			}

			return ~oldcrc32;
		}

		template <typename T>
		inline static UInt32 Hash(const T& val)
		{
			return HelperHash::Hash(
				(Byte*)&val,
				sizeof(T)
				);
		}

	private:

		static UInt32 crc_32_tab[];

	};
}