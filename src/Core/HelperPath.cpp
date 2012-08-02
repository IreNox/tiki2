
#include "Core/HelperPath.h"

namespace TikiEngine
{
	wstring HelperPath::GetFilename(wstring fullPath)
	{
		Int32 i1 = fullPath.find_last_of(L'\\');
		Int32 i2 = fullPath.find_last_of(L'/');
		Int32 index = ++(i1 > i2 ? i1 : i2);

		return fullPath.substr(index, fullPath.size() - index);
	}

	wstring HelperPath::GetDirectoryName(wstring fullPath)
	{
		return L"";
	}
}