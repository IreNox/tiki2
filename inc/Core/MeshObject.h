#pragma once;

#include "Core/GameObject.h"
#include "Core/Material.h"
#include "Core/IMeshRenderer.h"

namespace TikiEngine
{
	namespace Objects
	{
		class MeshObject : public GameObject
		{
		public:
			MeshObject(Engine* engine);
			virtual ~MeshObject();

			virtual void Draw(const DrawArgs& args);
			virtual void Update(const UpdateArgs& args);

		protected:

			Material* material;
			IMeshRenderer* renderer;
		};
	}
}