
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
			Material* mat = engine->content->LoadMaterial(L"Data/Effects/pp_ssao.fx");
			SafeAddRef(mat->GetShader(), &shader);
			SafeRelease(&mat);

			aoTarget = engine->librarys->CreateResource<IRenderTarget>();
			aoTarget->CreateScreenSize();

			Vector2 screenSizeX2 = engine->graphics->GetViewPort()->GetSize() * 2;
			shader->SetVector2("HalfPixel", Vector2(1.0f / screenSizeX2.X, 1 / screenSizeX2.Y));

			randomTexture = engine->content->LoadTexture(L"Data/Resources/Textures/random.png");
			shader->SetTexture("texRandom", randomTexture);

			PostProcessPass* pass = new PostProcessPass(engine, shader);
			pass->AddInput("rtDiffuse", engine->graphics->GetScreenTarget());
			pass->AddInput("rtNormal", engine->graphics->GetNormalTarget());
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