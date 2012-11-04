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

		wstring GetWorkingPath() const;

		wstring Combine(wstring path1, wstring path2) const;
		wstring CombineWorkingPath(wstring path) const;

		wstring GetFilename(wstring fullPath) const;
		wstring GetDirectoryName(wstring fullPath) const;

		template<class T>
		wstring GetResourcePath(wstring fileName) const
		{
			return HelperPath::GetResourcePath(typeid(T).hash_code(), fileName);
		}
		wstring GetResourcePath(PInt typeHash, wstring fileName) const;

	private:

		wstring workingPath;

		void checkPath(wstring path) const;
		void checkSlashes(wstring& path) const;

	};
}