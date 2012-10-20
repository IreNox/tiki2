#pragma once

#include "Core/Component.h"

#include "Core/Matrix.h"
#include "Core/CBMatrices.h"

#include "Core/IRenderTarget.h"

#include "Core/Ray.h"
#include "Core/Frustum.h"

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
			
			CBMatrices* GetMatrices();
			Matrix* GetViewMatrix();
			Matrix* GetProjectionMatrix();
			IRenderTarget* GetRenderTarget();
			Frustum* GetFrustum();

			void SetProjectionMatrix(const Matrix& projection);
			void SetRenderTarget(IRenderTarget* renderTarget);

			bool GetReady();

		    Ray ScreenPointToRay(const Vector2& screenPos);

		private:

			CBMatrices matrices;
			IRenderTarget* renderTarget;
			Frustum frustum;
		};
	}
}

