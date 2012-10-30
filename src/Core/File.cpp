
#include "Core/File.h"

#include "Core/FileStream.h"
#include "Core/MemoryStream.h"

#include "Core/sqlite3.h"
#include "Core/HelperPath.h"

namespace TikiEngine
{
	namespace IO
	{
		#pragma region Class
		File::File(wstring path, FileType type)
			: fileName(path), fileType(type)
		{
		}

		File::~File()
		{
		}
		#pragma endregion

		#pragma region Member - Get
		wstring File::GetFilename()
		{
			return fileName;
		}

		FileType File::GetFileType()
		{
			return fileType;
		}
		#pragma endregion

		#pragma region Member - Open
		Stream* File::OpenStream()
		{
			switch (fileType)
			{
			case FT_Database:
				return 0;
			case FT_Filesystem:
				return new FileStream(fileName, FM_Read);
			default:
				throw "Not supported";
			}
		}
		#pragma endregion

		#pragma region Static Member
		bool File::Exists(const wstring& fileName)
		{
			return false;
		}
		#pragma endregion

		#pragma region Static Member - Create
		File* File::CreateFile(const wstring& fileName)
		{
			return 0;
		}

		File* File::CreateResourceFile(PInt typeHash, const wstring& name)
		{
			return File::CreateFile(
				 L"" //HelperPath::GetResourcePath(typeHash, name)
			);
		}
		#pragma endregion

	}
}