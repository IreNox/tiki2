#pragma once

#if _DEBUG
#include "Core/Dictionary.h"

#include "Core\GameObject.h"
#include "Core\IMeshRenderer.h"

namespace TikiEngine
{
	namespace Objects
	{
		class DebugPhysicRenderer : public GameObject
		{
		public:

			DebugPhysicRenderer(Engine* engine);
			~DebugPhysicRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			Dictionary<PrimitiveTopologies, Mesh*> meshes;
			Dictionary<PrimitiveTopologies, IMeshRenderer*> renderer;
		};
	}
}
#endif