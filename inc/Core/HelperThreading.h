#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	class HelperThreading
	{
	public:

		static void InitThread(UInt32 id);

		static UInt32 GIndex();


	private:

		static UInt32 id;

	};
}