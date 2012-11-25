
#include "Graphics/TikiMesh.h"


namespace TikiEngine
{
	namespace Resources
	{
		TikiMesh::TikiMesh()
			: material(0), hasDeformation(false)
		{
		}

		TikiMesh::~TikiMesh()
		{
			SafeRelease(&material);
		}

		string TikiMesh::GetName()
		{
			return this->name;
		}

		void TikiMesh::SetName(string name)
		{
			this->name = name;
		}
		
		void TikiMesh::SetDeformation(bool b)
		{
			hasDeformation = b;
		}

		bool TikiMesh::UseDeformation()
		{
			return hasDeformation;
		}

		Material* TikiMesh::GetMaterial()
		{
			return material;
		}

		void TikiMesh::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);
		}

		bool TikiMesh::GetReady()
		{
			return this->verticesList.Count() != 0 && this->indicesList.Count() != 0;
		}
		
		void TikiMesh::SetIndices(List<UInt32>& indices)
		{
			this->indicesList = indices;
		}

		void TikiMesh::SetSkinningVertexData(List<SkinningVertex>& skinning)
		{
			this->verticesList = skinning;
		}
		#pragma endregion
	}
}
