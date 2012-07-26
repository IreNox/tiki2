#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	class HelperHash
	{
	public:
		static UInt32 Hash(Byte* str, UInt32 len)
		{
			Int32 c = 0;
			UInt32 hash = 0;
    
			for (UInt32 i = 0; i < len; i++)
			{
				c = *str++;
				hash = c + (hash << 6) + (hash << 16) - hash;
			}
    
			return hash;
		}
	};
}