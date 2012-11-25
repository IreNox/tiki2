#pragma once

using System::String;

namespace TikiEditor
{
	public ref class FBXImport
	{
	public:

		FBXImport();
		~FBXImport();

		void Execute();

		property String^ OutputFilename
		{
			String^ get() { return outputFile; }
			void set(String^ value) { outputFile = value; }
		}

		property System::Collections::Generic::Dictionary<String^, String^>^ InputFilenames
		{
			System::Collections::Generic::Dictionary<String^, String^>^ get() { return inputFiles; }
		}

	private:

		String^ outputFile;		
		System::Collections::Generic::Dictionary<String^, String^>^ inputFiles;

	};
}