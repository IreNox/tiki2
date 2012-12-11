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
			shadowTarget->AddRef();

			PostProcessPass* pass = new PostProcessPass(engine, shaderShadow);
			pass->AddOutput(0, shadowTarget);
			this->AddPass(pass);

			pass = new PostProcessPass(engine, shaderShadow);
			pass->AddInput("tex", shadowTarget);
			pass->AddOutput(0, engine->graphics->GetUnusedScreenTarget());
			this->AddPass(pass);

			pass = new PostProcessPass(engine, shaderShadow);
			pass->AddInput("tex", engine->graphics->GetUnusedScreenTarget());
			pass->AddOutput(0, shadowTarget);
			this->AddPass(pass);

			pass = new PostProcessPass(engine, shaderDefault);
			pass->AddInput("rtDepth", engine->graphics->GetDepthTarget());
			pass->AddInput("rtLight", engine->graphics->GetLightTarget());
			pass->AddInput("rtScreen", engine->graphics->GetScreenTarget());
			pass->AddInput("rtNormal", engine->graphics->GetNormalTarget());
			pass->AddInput("rtInterface", engine->graphics->GetInterfaceTarget());
			pass->AddInput("rtShadow", shadowTarget);
			pass->AddOutput(0, backBuffer);
			this->AddPass(pass);
		}

		PPDefault::~PPDefault()
		{
			SafeRelease(&shaderShadow);
			SafeRelease(&shaderDefault);

			SafeRelease(&shadowTarget);
		}

		void PPDefault::UpdatePass(UInt32 index, const DrawArgs& args)
		{
			if (index == 0)
			{
				shadowTarget->Clear(Color::White);
			}
			else if (index == 1)
			{
				engine->graphics->SetStateDepthEnabled(false);

				passes[1]->SetOutput(0, engine->graphics->GetUnusedScreenTarget());
				passes[2]->SetInput("tex", engine->graphics->GetUnusedScreenTarget());
			}

			if (index < 3)
			{
				shaderShadow->SelectSubByIndex(index);
			}
		}
		#pragma endregion
	}
}