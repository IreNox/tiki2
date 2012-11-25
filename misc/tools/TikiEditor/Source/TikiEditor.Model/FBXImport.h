#pragma once

#include "Model.h"
#include "TikiConvert.h"

#include "FbxHelper.h"
#include "FbxLoader.h"

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
			FbxLoader* loader = new FbxLoader();

			UInt32 i = 0;
			for each (System::String^ file in inputFiles)
			{
				wcstring str = (wcstring)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(file).ToPointer();

				FbxScene* scene; 
				FbxHelper* helper = new FbxHelper();

				loader->GetScene(str, &scene);
				helper->SetScene(scene);

				if (i == 0)
				{
					model->SetRootBone(helper->GetRootBone());
					model->AddAnimation(helper->GetAnimation());
					model->SetConstantBufferIndices(helper->GetConstantBufferIndices());
					model->SetMeshes(helper->GetMeshes());
				}
				else
				{
					/*helper->MergeAnimation(
						helper->GetAnimation(),
						model->GetRootBone(),
						helper->GetRootBone()
					)*/
				}

				//delete(helper);

				i++;
			}

			//delete(loader);

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