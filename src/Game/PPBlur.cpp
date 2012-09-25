
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

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\pp_blur.fx");
			SafeAddRef(mat->GetShader(), &shader);
			SafeRelease(&mat);

			shader->SetVector2("ScreenSize", Vector2((float)verticleTarget->GetWidth(), (float)verticleTarget->GetHeight()));

			PostProcessPass* pass = new PostProcessPass(engine, shader);
			pass->AddInput("tex", engine->graphics->GetScreenTarget());
			pass->AddOutput(0, verticleTarget);
			this->AddPass(pass);
			SafeRelease(&pass);

			pass = new PostProcessPass(engine, shader);
			pass->AddInput("tex", verticleTarget);
			pass->AddOutput(0, engine->graphics->GetScreenTarget());
			this->AddPass(pass);
			SafeRelease(&pass);
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