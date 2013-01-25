
#include "Game/PPDepthOfField.h"

#include "Core/IGraphics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Graphics
	{
		PPDepthOfField::PPDepthOfField(Engine* engine)
			: PostProcess(engine)
		{
			verticleTarget = engine->librarys->CreateResource<IRenderTarget>();
			verticleTarget->CreateScreenSize();
			verticleTarget->AddRef();

			SafeAddRef(
				engine->content->LoadShader(L"pp_depth_of_field"),
				&shader
			);

			shader->SetVector2("ScreenSize", engine->graphics->GetViewPort()->GetSize());

			PostProcessPass* pass = TIKI_NEW PostProcessPass(engine, shader);
			pass->AddInput("rtScene", engine->graphics->GetScreenTarget());
			pass->AddInput("rtDepth", engine->graphics->GetDepthTarget());
			pass->AddOutput(0, verticleTarget);
			this->AddPass(pass);

			pass = TIKI_NEW PostProcessPass(engine, shader);
			pass->AddInput("rtScene", verticleTarget);
			pass->AddInput("rtDepth", engine->graphics->GetDepthTarget());
			pass->AddOutput(0, engine->graphics->GetScreenTarget());
			this->AddPass(pass);
		}

		PPDepthOfField::~PPDepthOfField()
		{
			SafeRelease(&shader);
			SafeRelease(&verticleTarget);
		}

		void PPDepthOfField::UpdatePass(UInt32 index, const DrawArgs& args)
		{
#if _DEBUG
			shader->SetVector2("ScreenSize", args.Graphics->GetViewPort()->GetSize());
#endif

			if (index == 0)
			{
				passes[0]->SetInput("rtScene", engine->graphics->GetScreenTarget());
				verticleTarget->ApplyFirstAndOnly();
			}
			else
			{
				passes[1]->SetOutput(0, engine->graphics->GetScreenTarget());
			}

			shader->SelectSubByIndex(index);
		}
	}
}