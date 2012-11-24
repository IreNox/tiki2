#pragma once

#include "Model.h"

namespace TikiEditor
{
	public ref class FBXImport
	{
	public:

		FBXImport() {}
		~FBXImport() {}

		void Execute()
		{
			Model* model = new Model();

			for each (System::String^ file in inputFiles)
			{
			//	//fbxloader.load(file, model);
			}


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