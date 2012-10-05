#pragma once

#include "Core/Component.h"

#include "Core/Matrix.h"
#include "Core/Matrices.h"

#include "Core/IRenderTarget.h"

#include "Core/Ray.h"

namespace TikiEngine
{
	namespace Components
	{
		using TikiEngine::Resources::IRenderTarget;

		class Camera : public Component
		{
		public:

			Camera(Engine* engine, GameObject* gameObject);
			~Camera();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			Matrices* GetMatrices();
			Matrix* GetViewMatrix();
			Matrix* GetProjectionMatrix();
			IRenderTarget* GetRenderTarget();

			void SetProjectionMatrix(const Matrix& projection);
			void SetRenderTarget(IRenderTarget* renderTarget);

			bool GetReady();

		    Ray ScreenPointToRay(const Vector2& screenPos);

		private:

			Matrices matrices;
			IRenderTarget* renderTarget;

		};
	}
}

