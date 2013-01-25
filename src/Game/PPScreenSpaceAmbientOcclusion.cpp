
#include "Game/PPScreenSpaceAmbientOcclusion.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"

#include "Core/Camera.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Core/Camera.h"
#include "Core/List.h"
#include "Core/Matrix.h"

namespace TikiEngine
{
	namespace Graphics
	{
		PPScreenSpaceAmbientOcclusion::PPScreenSpaceAmbientOcclusion(Engine* engine)
			: PostProcess(engine)
		{
			SafeAddRef(
				engine->content->LoadShader(L"pp_ssao"),
				&shader
			);

			aoTarget = engine->librarys->CreateResource<IRenderTarget>();
			aoTarget->CreateScreenSize();

			engine->graphics->AddDefaultProcessTarget("ambientLight", aoTarget);

			Vector2 screenSize = engine->graphics->GetViewPort()->GetSize();
			shader->SetVector2("ScreenSize", Vector2(screenSize.X, screenSize.Y));

			randomTexture = engine->content->LoadTexture(L"random");
			shader->SetTexture("tRandom", randomTexture);

			PostProcessPass* pass = TIKI_NEW PostProcessPass(engine, shader);
			pass->AddInput("rtNormal", engine->graphics->GetNormalTarget());
			pass->AddInput("tDepth", engine->graphics->GetDepthTarget());
			
			pass->AddOutput(0, aoTarget);
			this->AddPass(pass);
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
			shader->SetVector3("viewDirection", Vector3::Normalize(-engine->GetScene()->GetCameras()->Get(0)->GetViewDirection()));
		}
	}
}