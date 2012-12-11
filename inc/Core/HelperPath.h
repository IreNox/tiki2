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

		const wstring& GetBinaryPath() const;
		const wstring& GetWorkingPath() const;

		wstring Combine(const wstring& path1, const wstring& path2) const;
		wstring CombineWorkingPath(const wstring& path) const;

		wstring GetFilename(const wstring& fullPath) const;
		wstring GetFilenameWithoutExtension(const wstring& fullPath) const;
		wstring GetDirectoryName(const wstring& fullPath) const;

		bool FileExists(const wstring& fullPath) const;
		bool DirectoryExists(const wstring& fullPath) const;

		template<class T>
		wstring GetResourcePath(const wstring& fileName) const
		{
			return HelperPath::GetResourcePath(typeid(T).hash_code(), fileName);
		}
		wstring GetResourcePath(PInt typeHash, const wstring& fileName) const;

		void CheckPath(const wstring& path) const;

	private:

		wstring binaryPath;
		wstring workingPath;

		void checkSlashes(wstring& path) const;

	};
}