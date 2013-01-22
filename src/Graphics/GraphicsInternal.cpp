#pragma once

#include "Graphics/PPDefault.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region PPDefault
		PPDefault::PPDefault(Engine* engine, IRenderTarget* backBuffer)
			: PostProcess(engine)
		{
			shaderShadow = engine->content->LoadShader(L"pp_shadow");
			shaderShadow->SetVector2("ScreenSize", engine->graphics->GetViewPort()->GetSize());
			shaderShadow->AddRef();

			shaderDefault = engine->content->LoadShader(L"pp_default");
			shaderDefault->AddRef();

			shadowTarget = new RenderTarget(engine);
			shadowTarget->CreateScreenSize(false, PF_R8G8B8A8);
			shadowTarget->Clear(Color::White);
			shadowTarget->AddRef();

			PostProcessPass* pass;

#if TIKI_SHADOWS_ENABLED
			pass = new PostProcessPass(engine, shaderShadow);
			pass->AddOutput(0, shadowTarget);
			this->AddPass(pass);
#endif

			pass = new PostProcessPass(engine, shaderDefault);
			pass->AddInput("rtDepth", engine->graphics->GetDepthTarget());
			pass->AddInput("rtLight", engine->graphics->GetLightTarget());
			pass->AddInput("rtScreen", engine->graphics->GetScreenTarget());
			pass->AddInput("rtNormal", engine->graphics->GetNormalTarget());
			pass->AddInput("rtInterface", engine->graphics->GetInterfaceTarget());
			pass->AddInput("rtShadow", shadowTarget);
			pass->AddOutput(0, backBuffer);
			this->AddPass(pass);

			engine->graphics->ScreenSizeChanged.AddHandler(this);
		}

		PPDefault::~PPDefault()
		{
			SafeRelease(&shaderShadow);
			SafeRelease(&shaderDefault);

			SafeRelease(&shadowTarget);
		}

		void PPDefault::UpdatePass(UInt32 index, const DrawArgs& args)
		{
#if TIKI_SHADOWS_ENABLED
			if (index == 0)
			{
				shadowTarget->Clear(Color::White);
			}
#endif
		}

		void PPDefault::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			shadowTarget->Clear(Color::White);
		}
		#pragma endregion
	}
}