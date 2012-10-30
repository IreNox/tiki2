#pragma once

#include "Core/TypeGlobals.h"

#include <typeinfo.h>

namespace TikiEngine
{
	class HelperPath
	{
	public:

		HelperPath();
		~HelperPath();

		wstring GetWorkingPath();

		wstring Combine(wstring path1, wstring path2);
		wstring CombineWorkingPath(wstring path);

		wstring GetFilename(wstring fullPath);
		wstring GetDirectoryName(wstring fullPath);

		template<class T>
		wstring GetResourcePath(wstring fileName)
		{
			return HelperPath::GetResourcePath(typeid(T).hash_code(), fileName);
		}
		wstring GetResourcePath(PInt typeHash, wstring fileName);

	private:

		wstring workingPath;

		void checkPath(wstring path);
		void checkSlashes(wstring& path);

	};
}