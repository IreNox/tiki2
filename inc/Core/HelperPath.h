#pragma once

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	class HelperPath
	{
	public:

		static wstring GetFilename(wstring fullPath);
		static wstring GetDirectoryName(wstring fullPath);

	private:

		HelperPath() {}
		~HelperPath() {}
	};
}