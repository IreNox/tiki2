
#include "ResConverter.h"

#include "Core/FileStream.h"
#include "Core/CompressedStream.h"

namespace TikiEditor
{
	using namespace System::Runtime::InteropServices;

	ResConverter::ResConverter(System::String^ dataPath)
	{
		this->dataPath = dataPath->ToLower()->Replace('\\', '/');

		context = new ResIOContext();
		files = gcnew System::Collections::Generic::List<System::String^>();
	}

	ResConverter::~ResConverter()
	{
		delete(context);
	}

	void ResConverter::AddFile(System::String^ fileName)
	{
		files->Add(fileName->ToLower()->Replace('\\', '/'));
	}

	void ResConverter::WriteToFile(System::String^ fileName)
	{
		UInt32 len = 0;
		UInt32 count = 0;

		files->Sort();

		System::Collections::Generic::List<int>^ fileLen = gcnew System::Collections::Generic::List<int>();
		System::Collections::Generic::List<System::String^>^ filesP = gcnew System::Collections::Generic::List<System::String^>();

		for each (System::String^ file in files)
		{
			if (!useFile(file))
			{
				continue;
			}

			System::String^ mFile = file->Replace(dataPath, "")->Substring(1);

			filesP->Add(mFile);

			fileLen->Add(mFile->Length + 1);
			len += mFile->Length + 1;	
			count++;
		}
			
		UInt32 pos = 0;
		wchar_t* filelist = new wchar_t[len];

		int i = 0;	
		for each (System::String^ file in files)
		{
			if (!useFile(file))
			{
				continue;
			}

			wcstring cFile = (wcstring)Marshal::StringToHGlobalUni(filesP[i]).ToPointer();
			memcpy(filelist + pos, cFile, sizeof(wchar_t) * fileLen[i]);

			Marshal::Release(System::IntPtr((void*)cFile));

			pos += fileLen[i];
			i++;
		}

		context->GetHeader()->FileCount = count;
		context->GetHeader()->FilelistId = context->AddPart(filelist, sizeof(wchar_t), PT_Array, PT_Widechar, len);

		UInt32* dataIds = new UInt32[count];

		i = 0;
		pos = 0;
		len = 0;
		for each (System::String^ file in files)
		{
			if (!useFile(file))
			{
				continue;
			}

			bool deleteMe = false;
			if (System::IO::Path::GetExtension(file) == ".fx")
			{
				System::String^ content = System::IO::File::ReadAllText(file);

				System::Text::RegularExpressions::Regex^ regex = gcnew System::Text::RegularExpressions::Regex("#include \"([a-zA-Z0-9_/.]+)\"");
																											   
				System::Text::RegularExpressions::MatchCollection^ matches;
				
				while ((matches = regex->Matches(content, 0))->Count != 0)
				{
					System::Collections::Generic::Dictionary<System::String^, System::String^>^ dict = gcnew System::Collections::Generic::Dictionary<System::String^, System::String^>();

					for each (System::Text::RegularExpressions::Match^ match in matches)
					{
						dict->Add(
							content->Substring(match->Index, match->Length),
							System::IO::File::ReadAllText(
								System::IO::Path::Combine(
									dataPath,
									match->Groups[1]->Value
								)
							)
						);
					}

					for each (System::Collections::Generic::KeyValuePair<System::String^, System::String^>^ kvp in dict)
					{
						content = content->Replace(kvp->Key, kvp->Value);
					}
				}

				file = System::IO::Path::GetTempFileName();
				System::IO::File::WriteAllText(file, content);
				deleteMe = true;
			}

			wcstring cFile = (wcstring)Marshal::StringToHGlobalUni(file).ToPointer();
			FileStream* stream = new FileStream(cFile, FM_Read);
			UInt32 fLen = stream->GetLength();
			len += fLen;

			Byte* fData = new Byte[fLen];
			stream->Read(fData, 0, fLen);

			dataIds[i] = context->AddPart(fData, 1, PT_Array, PT_Byte, fLen);

			delete(stream);
			Marshal::Release(System::IntPtr((void*)cFile));

			pos += fileLen[i];
			i++;

			if (deleteMe)
				System::IO::File::Delete(file);
		}

		context->GetHeader()->DatalistId = context->AddPart(dataIds, sizeof(int), PT_Array, PT_UInt, count);

		wcstring fileName2 = (wcstring)Marshal::StringToHGlobalUni(fileName).ToPointer();

		FileStream* stream = new FileStream(fileName2, FM_Write);
		//CompressedStream* stream = new CompressedStream(fileName2, COM_Write);
		context->WriteToStream(stream);
		delete(stream);

		Marshal::Release(System::IntPtr((void*)fileName2));
	}

	bool ResConverter::useFile(System::String^ file)
	{
		if (System::IO::Path::GetFileName(file)->StartsWith("is") && (System::IO::Path::GetExtension(file) == ".fx" || System::IO::Path::GetExtension(file) == ".glsl"))
		{
			return false;
		}

		if ((System::IO::Path::GetExtension(file) == ".dat" && System::IO::Path::GetFileNameWithoutExtension(file) != "licence") || System::IO::Path::GetExtension(file) == ".sqlite")
		{
			return false;
		}

		return true;
	}
}