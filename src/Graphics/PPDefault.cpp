#pragma once

#include "Graphics/PPDefault.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Graphics
	{
		PPDefault::PPDefault(Engine* engine, IRenderTarget* backBuffer)
			: PostProcess(engine), shaderShadow(0)
		{
			shaderDefault = engine->content->LoadShader(L"pp_default");
			shaderDefault->AddRef();

			shadowTarget = TIKI_NEW RenderTarget(engine);
			shadowTarget->CreateScreenSize(false, PF_R8G8B8A8);
			shadowTarget->Clear(Color::White);
			shadowTarget->AddRef();

			PostProcessPass* pass;

			if (engine->GetShadowsEnabled())
			{
				shaderShadow = engine->content->LoadShader(L"pp_shadow");
				shaderShadow->SetVector2("ScreenSize", engine->graphics->GetViewPort()->GetSize());
				shaderShadow->AddRef();

				pass = TIKI_NEW PostProcessPass(engine, shaderShadow);
				pass->AddOutput(0, shadowTarget);
				this->AddPass(pass);
			}

			pass = TIKI_NEW PostProcessPass(engine, shaderDefault);
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
			if (index == 0 && engine->GetShadowsEnabled())
			{
				shadowTarget->Clear(Color::White);
			}
		}

		void PPDefault::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			shadowTarget->Clear(Color::White);
		}
	}
}