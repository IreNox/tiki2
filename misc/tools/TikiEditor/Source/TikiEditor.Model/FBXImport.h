#pragma once

#include "FakeTexture.h"
#include "MeshMaterial.h"

using System::String;

namespace TikiEditor
{
	public ref class FBXImport
	{
	public:

		FBXImport();
		~FBXImport();

		void Execute();

		System::Collections::Generic::List<String^>^ GetNames(String^ fileName);

		property String^ OutputFilename
		{
			String^ get() { return outputFile; }
			void set(String^ value) { outputFile = value; }
		}

		property System::Collections::Generic::List<MeshMaterial^>^ InputMaterials
		{
			System::Collections::Generic::List<MeshMaterial^>^ get() { return inputMaterials; }
		}

		property System::Collections::Generic::Dictionary<String^, String^>^ InputFilenames
		{
			System::Collections::Generic::Dictionary<String^, String^>^ get() { return inputFiles; }
		}

	private:

		String^ outputFile;
		System::Collections::Generic::List<MeshMaterial^>^ inputMaterials;
		System::Collections::Generic::Dictionary<String^, String^>^ inputFiles;

		ITexture* createFakeTexture(String^ fileName);

	};
}