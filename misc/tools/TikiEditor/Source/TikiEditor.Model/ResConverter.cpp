
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
		UInt32 count = files->Count;

		files->Sort();

		System::Collections::Generic::List<int>^ fileLen = gcnew System::Collections::Generic::List<int>();
		System::Collections::Generic::List<System::String^>^ filesP = gcnew System::Collections::Generic::List<System::String^>();

		for each (System::String^ file in files)
		{
			System::String^ mFile = file->Replace(dataPath, "")->Substring(1);

			filesP->Add(mFile);

			fileLen->Add(mFile->Length + 1);
			len += mFile->Length + 1;						
		}
			
		UInt32 pos = 0;
		wchar_t* filelist = new wchar_t[len];

		int i = 0;	
		for each (System::String^ file in files)
		{
			wcstring cFile = (wcstring)Marshal::StringToHGlobalUni(filesP[i]).ToPointer();
			memcpy(filelist + pos, cFile, sizeof(wchar_t) * fileLen[i]);

			Marshal::Release(System::IntPtr((void*)cFile));

			pos += fileLen[i];
			i++;
		}

		context->GetHeader()->FileCount = files->Count;
		context->GetHeader()->FilelistId = context->AddPart(filelist, sizeof(wchar_t), PT_Array, PT_Widechar, len);

		UInt32* dataIds = new UInt32[count];

		i = 0;
		pos = 0;
		len = 0;
		for each (System::String^ file in files)
		{		
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
		}

		context->GetHeader()->DatalistId = context->AddPart(dataIds, sizeof(int), PT_Array, PT_UInt, count);

		wcstring fileName2 = (wcstring)Marshal::StringToHGlobalUni(fileName).ToPointer();

		FileStream* stream = new FileStream(fileName2, FM_Write);
		//CompressedStream* stream = new CompressedStream(fileName2, COM_Write);
		context->WriteToStream(stream);
		delete(stream);

		Marshal::Release(System::IntPtr((void*)fileName2));
	}
}