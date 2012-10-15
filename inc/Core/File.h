#pragma once

#include "Core/TypeGlobals.h"

#include "Core/Stream.h"

namespace TikiEngine
{
	namespace IO
	{
		enum FileType
		{
			FT_Filesystem,
			FT_Database,
			FT_Kompressed
		};

		class File
		{
		public:

			~File();

			wstring GetFilename();
			FileType GetFileType();

			Stream* OpenStream();

			static bool Exists(const wstring& fileName);

			static File* CreateFile(const wstring& fileName);
			static File* CreateResourceFile(PInt typeHash, const wstring& name);

		private:

			File(wstring path, FileType type);

			wstring fileName;
			FileType fileType;

		};
	}
}