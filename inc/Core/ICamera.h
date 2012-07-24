#pragma once

#include "Core/IComponent.h"

#include "Core/Matrix.h"
#include "Core/Matrices.h"

namespace TikiEngine
{
	namespace Components
	{
		class ICamera : IComponent
		{
		public:

			ICamera(Engine* engine)
				: IComponent(engine, ComponentType::Camera)
			{
			}
			virtual ~ICamera();
			
			virtual Matrices* GetMatrices() = 0;
			virtual Matrix* GetViewMatrix() = 0;
			virtual Matrix* GetProjectionMatrix() = 0;

			virtual void SetProjectionMatrix(Matrix* projection)  = 0;

		protected:

			Matrices matrices;

		};
	}
}

