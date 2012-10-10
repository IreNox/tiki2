
#include "Core/HelperPath.h"

#include <Windows.h>

namespace TikiEngine
{
	wstring HelperPath::workingPath = L"";

	wstring HelperPath::GetWorkingPath()
	{
		if (workingPath == L"")
		{
			WCHAR cd[MAX_PATH];
			GetModuleFileName(0, cd, MAX_PATH);

			workingPath = HelperPath::GetDirectoryName(cd);
		}

		return workingPath;
	}

	wstring HelperPath::GetFilename(wstring fullPath)
	{
		PInt i1 = fullPath.find_last_of(L'\\');
		PInt i2 = fullPath.find_last_of(L'/');
		PInt index = ++(i1 > i2 ? i1 : i2);

		return fullPath.substr(index, fullPath.size() - index);
	}

	wstring HelperPath::GetDirectoryName(wstring fullPath)
	{
		PInt i1 = fullPath.find_last_of(L'\\');
		PInt i2 = fullPath.find_last_of(L'/');
		PInt index = (i1 > i2 ? i1 : i2);

		return fullPath.substr(0, index);
	}
}