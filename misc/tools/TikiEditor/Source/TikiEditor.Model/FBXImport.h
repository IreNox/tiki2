#pragma once

#include "Model.h"
#include "TikiConvert.h"

namespace TikiEditor
{
	public ref class FBXImport
	{
	public:

		FBXImport()
		{
			inputFiles = gcnew System::Collections::Generic::List<System::String^>();
		}
		~FBXImport() {}

		void Execute()
		{
			Model* model = new Model();

			for each (System::String^ file in inputFiles)
			{
				//fbxloader.load(file, model);
			}

			TikiConvert^ convert = gcnew TikiConvert(model);
			convert->WriteToFile(outputFile);
		}

		property System::String^ OutputFilename
		{
			System::String^ get() { return outputFile; }
			void set(System::String^ value) { outputFile = value; }
		}

		property System::Collections::Generic::List<System::String^>^ InputFilenames
		{
			System::Collections::Generic::List<System::String^>^ get() { return inputFiles; }
		}

	private:

		System::String^ outputFile;
		
		System::Collections::Generic::List<System::String^>^ inputFiles;

	};
}