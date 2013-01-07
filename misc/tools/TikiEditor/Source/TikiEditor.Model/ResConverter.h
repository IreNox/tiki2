#pragma once

#include "ContentManager/ResourceBinaryData.h"

namespace TikiEditor
{
	using namespace TikiEngine::IO;
	using namespace TikiEngine::Resources;

	public ref class ResConverter
	{
	public:

		ResConverter(System::String^ dataPath);
		~ResConverter();

		void AddFile(System::String^ fileName);

		void WriteToFile(System::String^ fileName);

	private:

		System::String^ dataPath;

		ResIOContext* context;
		System::Collections::Generic::List<System::String^>^ files;

	};
}