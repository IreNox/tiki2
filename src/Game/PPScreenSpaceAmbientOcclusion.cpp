
#include "Game/PPScreenSpaceAmbientOcclusion.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"

#include "Core/Camera.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Graphics
	{
		PPScreenSpaceAmbientOcclusion::PPScreenSpaceAmbientOcclusion(Engine* engine)
			: PostProcess(engine)
		{
			SafeAddRef(
				engine->content->LoadShader(L"Data/Effects/pp_ssao.fx"),
				&shader
			);

			aoTarget = engine->librarys->CreateResource<IRenderTarget>();
			aoTarget->CreateScreenSize();

			Vector2 screenSize = engine->graphics->GetViewPort()->GetSize();
			shader->SetVector2("ScreenSize", Vector2(screenSize.X, screenSize.Y));

			randomTexture = engine->content->LoadTexture(L"Data/Resources/Textures/random.png");
			shader->SetTexture("tRandom", randomTexture);

			PostProcessPass* pass = new PostProcessPass(engine, shader);
			pass->AddInput("tNormal", engine->graphics->GetNormalTarget());
			pass->AddInput("tDepth", engine->graphics->GetDepthTarget());
			pass->AddOutput(0, aoTarget);
			this->AddPass(pass);
			SafeRelease(&pass);
		}

		PPScreenSpaceAmbientOcclusion::~PPScreenSpaceAmbientOcclusion()
		{
			SafeRelease(&shader);
			SafeRelease(&aoTarget);
			SafeRelease(&randomTexture);
		}

		IRenderTarget* PPScreenSpaceAmbientOcclusion::GetAO()
		{
			return aoTarget;
		}

		void PPScreenSpaceAmbientOcclusion::UpdatePass(UInt32 index, const DrawArgs& args)
		{
			shader->SetVector3(
				"ViewForward",
				args.CurrentCamera->GetGameObject()->PRS.GetForward()
			);

			shader->SetMatrix(
				"SceneViewProj",
				Matrix::Identity
			);
		}
	}
}