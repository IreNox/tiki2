
#include "Core/HelperPath.h"

#include <Windows.h>

#include "Core/Mesh.h"
#include "Core/IModel.h"
#include "Core/ISound.h"
#include "Core/IShader.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	#pragma region Vars
	using namespace TikiEngine::Resources;
	#pragma endregion

	#pragma region Init/Dispose
	HelperPath::HelperPath()
	{
		WCHAR cd[MAX_PATH];
		GetModuleFileName(0, cd, MAX_PATH);

		workingPath = HelperPath::GetDirectoryName(
			HelperPath::GetDirectoryName(cd)
		);
		checkSlashes(workingPath);	
	}

	HelperPath::~HelperPath()
	{
		workingPath.erase();
	}
	#pragma endregion

	#pragma region Member - WorkingPath
	wstring HelperPath::GetWorkingPath() const
	{
		return workingPath;
	}
	#pragma endregion

	#pragma region Member - Compine
	wstring HelperPath::Combine(wstring path1, wstring path2) const
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
		checkSlashes(fullPath);

		return fullPath;
	}

	wstring HelperPath::CombineWorkingPath(wstring path) const
	{
		wchar_t i2 = path[0];
		int rightV = (i2 == '/' || i2 == '\\' ? 1 : 0);

		wstring right = path.substr(rightV, path.size() - rightV);

		return workingPath + L"/" + right;
	}
	#pragma endregion

	#pragma region Member - Part
	wstring HelperPath::GetFilename(wstring fullPath) const
	{
		PInt i1 = fullPath.find_last_of(L'\\');
		PInt i2 = fullPath.find_last_of(L'/');
		PInt index = ++(i1 > i2 ? i1 : i2);

		return fullPath.substr(index, fullPath.size() - index);
	}

	wstring HelperPath::GetDirectoryName(wstring fullPath) const
	{
		checkSlashes(fullPath);

		PInt i1 = fullPath.find_last_of(L'\\');
		PInt i2 = fullPath.find_last_of(L'/');
		PInt index = (i1 > i2 ? i1 : i2);

		return fullPath.substr(0, index);
	}
	#pragma endregion

	#pragma region Member - Resource
	wstring HelperPath::GetResourcePath(PInt typeHash, wstring fileName) const
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
			typeExt = L"fbx";
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
			HelperPath::GetWorkingPath() + L"/Data/" + typeName,
			fileName + L"." + typeExt
		);
	}
	#pragma endregion

	#pragma region Private Member
	void HelperPath::checkPath(wstring path) const
	{
		if (GetFileAttributes(path.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(path.c_str(), 0);
		}
	}

	void HelperPath::checkSlashes(wstring& path) const
	{
		UInt32 i = 0;
		while (i < path.length())
		{
			if (path[i] == '\\') path[i] = '/';

			i++;
		}
	}
	#pragma endregion
}