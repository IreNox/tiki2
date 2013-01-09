#pragma once

#include "Core/Mesh.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IModelMesh : public Mesh
		{
		public:

			IModelMesh(Engine* engine) : Mesh(engine) {}
			~IModelMesh() {}

			virtual bool GetVisible() = 0;
			virtual void SetVisible(bool vis) = 0;

			virtual Material* GetMaterial() = 0;
			virtual void SetMaterial(Material* material) = 0;

			virtual Matrix& GetLocalMatrix() = 0;
			virtual void SetLocalMatrix(const Matrix& matrix) = 0;

			virtual const string& GetName() = 0;

		};
	}
}