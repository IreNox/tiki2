#pragma once

namespace TikiEngine
{
	namespace Resources
	{
		class IRenderTarget;
	}
	using TikiEngine::Resources::IRenderTarget;

	namespace Components
	{
		class Camera;
	}
	using TikiEngine::Components::Camera;

	struct DrawContext
	{
		Camera* CurrentCamera;
		IRenderTarget* RenderTarget;

		DrawContext(Camera* camera, IRenderTarget* renderTarget)
			: CurrentCamera(camera), RenderTarget(renderTarget)
		{
		}

		~DrawContext()
		{
		}
	};
}
