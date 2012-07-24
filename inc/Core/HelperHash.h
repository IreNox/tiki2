#pragma once

#include "Window.h"

namespace TikiEngine
{
	class HelperHash
	{
	public:
		static ULONG Hash(UCHAR* str, UINT len)
		{
			int c = 0;
			ULONG hash = 0;
    
			for (UINT i = 0; i < len; i++)
			{
				c = *str++;
				hash = c + (hash << 6) + (hash << 16) - hash;
			}
    
			return hash;
		}
	};
}