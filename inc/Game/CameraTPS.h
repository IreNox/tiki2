#pragma once

#include "Core/IScript.h"
#include "Core/Vector2.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;

		class CameraTPS : public IScript
		{
		public:

			CameraTPS(Engine* engine, GameObject* gameObject, GameObject* attached);
			~CameraTPS();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			float distance;
			Vector2 rot;

			GameObject* attached;

		};
	}
}