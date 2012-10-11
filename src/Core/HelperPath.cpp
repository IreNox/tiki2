
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

	wstring HelperPath::Combine(wstring path1, wstring path2)
	{
		wchar_t i1 = path1[path1.size() - 1];
		wchar_t i2 = path2[0];

		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring left = path1.substr(0, path1.size() - (i1 == '/' || i1 == '\\' ? -1 : 0));
		wstring right = path2.substr(rightV, path2.size() - rightV);

		wstring fullPath = left + L"/" + right;

		checkPath(
			HelperPath::GetDirectoryName(fullPath)
		);

		return fullPath;
	}

	wstring HelperPath::CombineWorkingPath(wstring path)
	{
		return HelperPath::Combine(
			HelperPath::GetWorkingPath(),
			path
		);
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

	#pragma region Private Member
	void HelperPath::checkPath(wstring path)
	{
		if (GetFileAttributes(path.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(path.c_str(), 0);
		}
	}
	#pragma endregion
}