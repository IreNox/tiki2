#pragma once

#include "Core/ICamera.h"

namespace TikiEngine
{
	namespace Components
	{
		class Camera : public ICamera
		{
		public:

			Camera(Engine* engine);
			~Camera();

			Matrices* GetMatrices();
			Matrix* GetViewMatrix();
			Matrix* GetProjectionMatrix();

			void SetProjectionMatrix(Matrix* projection);

		private:

			float g_fX;
			float g_fY;

		};
	}
}