#pragma once

#include "Core/Component.h"

#include "Core/EventScreenSizeChanged.h"

#include "Core/Ray.h"
#include "Core/Matrix.h"
#include "Core/Frustum.h"
#include "Core/CBMatrices.h"

#include "Core/IRenderTarget.h"

namespace TikiEngine
{
	namespace Components
	{
		using TikiEngine::Resources::IRenderTarget;

		class Camera : public Component, public ScreenSizeChangedEventHandler
		{
		public:

			Camera(Engine* engine, GameObject* gameObject);
			~Camera();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			CBMatrices& GetMatrices();
			inline const Matrix& GetViewMatrix() { return matrices.ViewMatrix; }
			inline const Matrix& GetProjectionMatrix() { return matrices.ProjectionMatrix; }
			const Matrix WorldToScreen();

			Frustum& GetFrustum();
			Ray ScreenPointToRay(const Vector2& screenPos);
			Vector3 GetViewDirection();

			IRenderTarget* GetRenderTarget();
			void SetRenderTarget(IRenderTarget* renderTarget);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);

			bool GetReady();

		private:

			Frustum frustum;
			CBMatrices matrices;

			IRenderTarget* renderTarget;

		};
	}
}

