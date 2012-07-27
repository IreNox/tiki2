#pragma once

#include "Core/IMeshRenderer.h"

namespace TikiEngine
{
	namespace Components
	{
		class MeshRenderer : public IMeshRenderer
		{
		public:
			MeshRenderer(Engine* engine, GameObject* gameObject);
			~MeshRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			IMesh* GetMesh();
			Material* GetMaterial();

			void SetMesh(IMesh* mesh);
			void SetMaterial(Material* material);
		};
	}
}