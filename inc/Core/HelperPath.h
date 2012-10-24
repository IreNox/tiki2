#pragma once

#include "Core/TypeGlobals.h"

#include <typeinfo.h>

namespace TikiEngine
{
	class HelperPath
	{
	public:

		static wstring GetWorkingPath();

		static wstring Combine(wstring path1, wstring path2);
		static wstring CombineWorkingPath(wstring path);

		static wstring GetFilename(wstring fullPath);
		static wstring GetDirectoryName(wstring fullPath);

		template<class T>
		static wstring GetResourcePath(wstring fileName)
		{
			return HelperPath::GetResourcePath(typeid(T).hash_code(), fileName);
		}
		static wstring GetResourcePath(PInt typeHash, wstring fileName);

	private:

		HelperPath() {}
		~HelperPath() {}

		static wstring workingPath;

		static void checkPath(wstring path);
		static void checkSlashes(wstring& path);

	};
}