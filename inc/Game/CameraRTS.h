#pragma once

#include "Core/IScript.h"

namespace TikiEngine
{
	namespace Scripts
	{
		class CameraRTS : public IScript
		{
		public:

			CameraRTS(Engine* engine, GameObject* gameObject);
			~CameraRTS();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		};
	}
}