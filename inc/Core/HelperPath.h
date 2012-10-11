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
			//typeid(T).name(__type_info_root_node

			return workingPath;
		}

	private:

		HelperPath() {}
		~HelperPath() {}

		static wstring workingPath;

		static void checkPath(wstring path);

	};
}