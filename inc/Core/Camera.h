#pragma once

#include "Core/Component.h"

#include "Core/EventScreenSizeChanged.h"

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

		class Camera : public Component, public ScreenSizeChangedEventHandler
		{
		public:

			Camera(Engine* engine, GameObject* gameObject);
			~Camera();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			CBMatrices* GetMatrices();
			Matrix* GetViewMatrix();
			Matrix* GetProjectionMatrix();

			Frustum* GetFrustum();
			Ray ScreenPointToRay(const Vector2& screenPos);

			IRenderTarget* GetRenderTarget();
			void SetRenderTarget(IRenderTarget* renderTarget);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);

			bool GetReady();

		private:

			Frustum frustum[2];
			CBMatrices matrices[2];

			IRenderTarget* renderTarget;

		};
	}
}

