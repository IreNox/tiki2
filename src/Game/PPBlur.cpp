
#include "Game/PPBlur.h"

#include "Core/IGraphics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Graphics
	{
		PPBlur::PPBlur(Engine* engine)
			: PostProcess(engine)
		{
			verticleTarget = engine->librarys->CreateResource<IRenderTarget>();
			verticleTarget->CreateScreenSize();
			verticleTarget->AddRef();

			SafeAddRef(
				engine->content->LoadShader(L"pp_blur"),
				&shader
			);

			shader->SetVector2("ScreenSize", engine->graphics->GetViewPort()->GetSize());

			PostProcessPass* pass = TIKI_NEW PostProcessPass(engine, shader);
			pass->AddInput("tex", engine->graphics->GetScreenTarget());
			pass->AddOutput(0, verticleTarget);
			this->AddPass(pass);

			pass = TIKI_NEW PostProcessPass(engine, shader);
			pass->AddInput("tex", verticleTarget);
			pass->AddOutput(0, engine->graphics->GetScreenTarget());
			this->AddPass(pass);
		}

		PPBlur::~PPBlur()
		{
			SafeRelease(&shader);
			SafeRelease(&verticleTarget);
		}

		void PPBlur::UpdatePass(UInt32 index, const DrawArgs& args)
		{
			shader->SelectSubByIndex(index);
		}
	}
}