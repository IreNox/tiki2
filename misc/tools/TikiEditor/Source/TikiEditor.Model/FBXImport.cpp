
#define TIKI_EDITOR

#include "FBXImport.h"

#include "FbxHelper.h"
#include "FbxLoader.h"
#include "D3DX10MeshLoader.h"

#include "Core/Material.h"
#include "Core/FileStream.h"
#include "Graphics/ModelConverter.h"

namespace TikiEditor
{
	using TikiEngine::string;
	using TikiEngine::wstring;
	using namespace TikiEngine::IO;
	using namespace TikiEngine::Resources;
	using namespace System::Runtime::InteropServices;

	FBXImport::FBXImport()
	{
		inputFiles = gcnew System::Collections::Generic::Dictionary<String^, String^>();
		inputMaterials = gcnew System::Collections::Generic::List<MeshMaterial^>();
	}

	FBXImport::~FBXImport()
	{
	}

	void FBXImport::Execute()
	{
		Model* model = new Model();
		FbxLoader* loader = new FbxLoader();

		UInt32 i = 0;
		for each (System::Collections::Generic::KeyValuePair<String^, String^>^ kvp in inputFiles)
		{
			wcstring name = (wcstring)Marshal::StringToHGlobalUni(kvp->Key).ToPointer();
			wcstring file = (wcstring)Marshal::StringToHGlobalUni(kvp->Value).ToPointer();

			FbxScene* scene; 
			FbxHelper* helper = new FbxHelper();

			loader->GetScene(file, &scene);
			helper->SetScene(scene);

			TikiAnimation* ani = helper->GetAnimation();
			ani->SetName(
				StringWtoA(name).CStr()
			);

			if (i == 0)
			{
				model->SetRootBone(helper->GetRootBone());
				model->SetConstantBufferIndices(helper->GetConstantBufferIndices());
				model->SetMeshes(helper->GetMeshes());
			}
			else
			{
				helper->MergeAnimation(
					ani,
					model->GetRootBone(),
					helper->GetRootBone()
				);
			}

			model->AddAnimation(ani);

			//delete(helper);

			i++;
		}

		for each (MeshMaterial^ meshMat in inputMaterials)
		{
			string str = (cstring)Marshal::StringToHGlobalAnsi(meshMat->Name).ToPointer();

			UInt32 i = 0;
			while (i < model->GetMeshes()->Count())
			{				
				TikiMesh* mesh = model->GetMeshes()->Get(i);

				if (mesh->GetName() == str)
				{
					mesh->SetAdjacencyIndices(
						meshMat->CreatetAdjacencyIndices
					);

					if (mesh->HasAdjacencyIndices())
					{
						D3DX10MeshLoader* indexGen = new D3DX10MeshLoader();
						indexGen->ImportMesh(mesh);
						indexGen->ConvertToAdjacency(mesh);

						delete(indexGen);
					}

					Material* mat = mesh->GetMaterial();

					if (mat == 0)
					{
						mat = new Material(0);
						mesh->SetMaterial(mat);
					}

					mat->TexDiffuse = createFakeTexture(meshMat->TextureDiffuse);
					mat->TexLightMap = createFakeTexture(meshMat->TextureLight);
					mat->TexNormalMap = createFakeTexture(meshMat->TextureNormal);
					mat->TexSpecularMap = createFakeTexture(meshMat->TextureSpec);
				}

				i++;
			}
		}

		wcstring outFile = (wcstring)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(outputFile).ToPointer();

		FileStream* stream = new FileStream(outFile, FM_Write);
		ModelConverter* convert = new ModelConverter(model);
		convert->WriteToStream(stream);

		delete(convert);
		delete(stream);

		delete(loader);
	}

	System::Collections::Generic::List<String^>^ FBXImport::GetNames(String^ fileName)
	{
		wcstring file = (wcstring)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(fileName).ToPointer();

		FbxScene* scene; 
		FbxLoader* loader = new FbxLoader();
		FbxHelper* helper = new FbxHelper();

		loader->GetScene(file, &scene);
		List<const char*> names = helper->GetMeshNames(scene);

		System::Collections::Generic::List<String^>^ list = gcnew System::Collections::Generic::List<String^>();

		UInt32 i = 0;
		while (i < names.Count())
		{
			String^ str = gcnew String(names[i]);

			list->Add(str);

			i++;
		}

		return list;
	}

	ITexture* FBXImport::createFakeTexture(String^ fileName)
	{
		wstring str = (wcstring)Marshal::StringToHGlobalUni(fileName).ToPointer();

		if (str == L"")
		{
			return 0;
		}

		ITexture* tex = new FakeTexture();
		tex->LoadFromFile(str.CStr());

		return tex;
	}
}

