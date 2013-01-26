
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
			workingPath.CStr()
		);
	}

	HelperPath::~HelperPath()
	{
		//binaryPath.erase();
		//workingPath.erase();
	}
	#pragma endregion

	#pragma region Member - Check
	void HelperPath::CheckPath(const wstring& path) const
	{
		if (GetFileAttributes(path.CStr()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(path.CStr(), 0);
		}
	}

	void HelperPath::CheckSlashes(wstring& path) const
	{
		path = path.Replace('\\', '/');
		path = path.ToLower();
	}
	#pragma endregion

	#pragma region Member - Part
	wstring HelperPath::GetFilename(const wstring& fullPath) const
	{
		wstring fileName = fullPath;
		CheckSlashes(fileName);
		Int32 index = fileName.LastIndexOf(L'/') + 1;

		return fileName.Substring(index, fileName.Length() - index);
	}

	wstring HelperPath::GetFilenameWithoutExtension(const wstring& fullPath) const
	{
		wstring fileName = fullPath;
		CheckSlashes(fileName);

		Int32 index = fileName.LastIndexOf(L'/') + 1;
		fileName = fullPath.Substring(index, fileName.Length() - index);
		
		index = fileName.LastIndexOf(L'.');
		fileName = fileName.Substring(0, index);

		return fileName;
	}

	wstring HelperPath::GetDirectoryName(const wstring& fullPath) const
	{
		wstring dirName = fullPath;
		CheckSlashes(dirName);

		return dirName.Substring(0, dirName.LastIndexOf(L'/'));
	}
	#pragma endregion

	#pragma region Member - Exists
	bool HelperPath::FileExists(const wstring& fullPath) const
	{
		DWORD att = GetFileAttributes(fullPath.CStr());

		return (att != INVALID_FILE_ATTRIBUTES) && (att != FILE_ATTRIBUTE_DIRECTORY);
	}

	bool HelperPath::DirectoryExists(const wstring& fullPath) const
	{
		DWORD att = GetFileAttributes(fullPath.CStr());

		return (att != INVALID_FILE_ATTRIBUTES) && (att == FILE_ATTRIBUTE_DIRECTORY);
	}
	#pragma endregion

	#pragma region Member - Combine
	wstring HelperPath::Combine(const wstring& path1, const wstring& path2) const
	{
		wchar_t i1 = path1[path1.Length() - 1];
		wchar_t i2 = path2[0];

		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring left = path1.Substring(0, path1.Length() - (i1 == '/' || i1 == '\\' ? -1 : 0));
		wstring right = path2.Substring(rightV, path2.Length() - rightV);

		wstring fullPath = left + L"/" + right;

		CheckSlashes(fullPath);
		return fullPath;
	}

	wstring HelperPath::CombineWorkingPath(const wstring& path) const
	{
		wchar_t i2 = path[0];
		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring right = path.Substring(rightV, path.Length() - rightV);

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
}