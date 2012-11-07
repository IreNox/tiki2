#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	class HelperThreading
	{
	public:

		static void InitThread(UInt32 id);

		static void Swap();

		static UInt32 GIndex();


	private:

#ifdef TIKI_MULTITHREADING
		static UInt32 threadId[2];
#else
		static UInt32 threadId[1];
#endif

	};
}