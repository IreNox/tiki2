#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	class Exception
	{
	public:

		Exception() {}
		Exception(cstring message) : mes(message) {}
		virtual ~Exception()
		{
			if (alloc)
			{
				delete(mes);
			}
		}

		inline cstring GetMessage() { return mes; }

	protected:

		cstring mes;
		bool alloc;
	};
}