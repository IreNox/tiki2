
#include "Core/HelperPath.h"

#include <Windows.h>

#include "Core/Mesh.h"
#include "Core/IModel.h"
#include "Core/ISound.h"
#include "Core/IShader.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	using namespace TikiEngine::Resources;

	#pragma region Init/Dispose
	HelperPath::HelperPath()
	{
		WCHAR cd[MAX_PATH];
		GetModuleFileName(0, cd, MAX_PATH);

		binaryPath = HelperPath::GetDirectoryName(cd);
		workingPath = HelperPath::GetDirectoryName(binaryPath);

		SetCurrentDirectory(
			workingPath.c_str()
		);
	}

	HelperPath::~HelperPath()
	{
		binaryPath.erase();
		workingPath.erase();
	}
	#pragma endregion

	#pragma region Member
	void HelperPath::CheckPath(const wstring& path) const
	{
		if (GetFileAttributes(path.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(path.c_str(), 0);
		}
	}
	#pragma endregion

	#pragma region Member - Part
	wstring HelperPath::GetFilename(const wstring& fullPath) const
	{
		wstring fileName = fullPath;
		checkSlashes(fileName);
		PInt index = fileName.find_last_of(L'/') + 1;

		return fileName.substr(index, fileName.size() - index);
	}

	wstring HelperPath::GetFilenameWithoutExtension(const wstring& fullPath) const
	{
		wstring fileName = fullPath;
		checkSlashes(fileName);

		PInt index = fileName.find_last_of(L'/') + 1;
		fileName = fullPath.substr(index, fileName.size() - index);
		
		index = fileName.find_last_of(L'.');
		fileName = fileName.substr(0, index);

		return fileName;
	}

	wstring HelperPath::GetDirectoryName(const wstring& fullPath) const
	{
		wstring dirName = fullPath;
		checkSlashes(dirName);

		return dirName.substr(0, dirName.find_last_of(L'/'));
	}
	#pragma endregion

	#pragma region Member - Exists
	bool HelperPath::FileExists(const wstring& fullPath) const
	{
		DWORD att = GetFileAttributes(fullPath.c_str());

		return (att != INVALID_FILE_ATTRIBUTES) && (att != FILE_ATTRIBUTE_DIRECTORY);
	}

	bool HelperPath::DirectoryExists(const wstring& fullPath) const
	{
		DWORD att = GetFileAttributes(fullPath.c_str());

		return (att != INVALID_FILE_ATTRIBUTES) && (att == FILE_ATTRIBUTE_DIRECTORY);
	}
	#pragma endregion

	#pragma region Member - Compine
	wstring HelperPath::Combine(const wstring& path1, const wstring& path2) const
	{
		wchar_t i1 = path1[path1.size() - 1];
		wchar_t i2 = path2[0];

		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring left = path1.substr(0, path1.size() - (i1 == '/' || i1 == '\\' ? -1 : 0));
		wstring right = path2.substr(rightV, path2.size() - rightV);

		wstring fullPath = left + L"/" + right;

		CheckPath(
			HelperPath::GetDirectoryName(fullPath)
			);
		checkSlashes(fullPath);

		return fullPath;
	}

	wstring HelperPath::CombineWorkingPath(const wstring& path) const
	{
		wchar_t i2 = path[0];
		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring right = path.substr(rightV, path.size() - rightV);

		return workingPath + L"/" + right;
	}
	#pragma endregion

	#pragma region Member - Resource
	wstring HelperPath::GetResourcePath(PInt typeHash, const wstring& fileName) const
	{
		wstring typeExt = L"";
		wstring typeName = L"";

		if (typeid(Mesh).hash_code() == typeHash)
		{
			typeExt = L"obj";
			typeName = L"Meshes";
		}
		else if (typeid(IModel).hash_code() == typeHash)
		{
			typeExt = L"tiki";
			typeName = L"Models";
		}
		else if (typeid(ISound).hash_code() == typeHash)
		{
			typeExt = L"wav";
			typeName = L"Sounds";
		}
		else if (typeid(IShader).hash_code() == typeHash)
		{
			typeExt = L"fx";
			typeName = L"Effects";
		}
		else if (typeid(ITexture).hash_code() == typeHash)
		{
			typeExt = L"dds";
			typeName = L"Textures";
		}
		else
		{
			throw "Resource type not found.";
		}

		return HelperPath::Combine(
			/* HelperPath::GetWorkingPath() + */ L"Data/" + typeName,
			fileName + L"." + typeExt
		);
	}
	#pragma endregion

	#pragma region Member - WorkingPath
	const wstring& HelperPath::GetBinaryPath() const
	{
		return binaryPath;
	}

	const wstring& HelperPath::GetWorkingPath() const
	{
		return workingPath;
	}
	#pragma endregion
	
	#pragma region Private Member
	void HelperPath::checkSlashes(wstring& path) const
	{
		static wchar_t mi = L'Z' - L'z';

		UInt32 i = 0;
		while (i < path.length())
		{
			wchar_t c = path[i];

			if (c == '\\') path[i] = '/';
			if(c <= 'Z' && c >= 'A') path[i] -= mi;

			i++;
		}		
	}
	#pragma endregion
}