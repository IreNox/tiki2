
#include "Core/PostProcess.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		PostProcess::PostProcess(Engine* engine)
			: EngineObject(engine)
		{
		}

		PostProcess::~PostProcess()
		{
			UInt32 i = 0;
			while (i < passes.Count())
			{
				SafeRelease(&passes[i]);

				i++;
			}
		}
		#pragma endregion

		#pragma region Member
		PostProcessPass* PostProcess::AddPass(PostProcessPass* pass)
		{
			passes.Add(pass);
			SafeAddRef(&pass);

			return pass;
		}

		void PostProcess::RemovePass(PostProcessPass* pass)
		{
			passes.Remove(pass);
			SafeRelease(&pass);
		}

		const List<PostProcessPass*>* PostProcess::GetPasses()
		{
			return &passes;
		}

		void PostProcess::UpdatePass(UInt32 index, const DrawArgs& args)
		{
		}
		#pragma endregion
	}
}