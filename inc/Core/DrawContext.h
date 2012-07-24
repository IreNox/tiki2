#pragma once

namespace TikiEngine
{
	namespace Graphics
	{
		class IRenderTarget;
	}
	using TikiEngine::Graphics::IRenderTarget;

	namespace Components
	{
		class ICamera;
	}
	using TikiEngine::Components::ICamera;

	struct DrawContext
	{
		ICamera* Camera;
		IRenderTarget* RenderTarget;

		DrawContext()
			: Camera(0), RenderTarget(0)
		{
		}

		DrawContext(ICamera* camera, IRenderTarget* renderTarget)
			: Camera(camera), RenderTarget(renderTarget)
		{
		}

		~DrawContext()
		{
		}
	};
}
