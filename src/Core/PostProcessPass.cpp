
#include "Core/PostProcessPass.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		PostProcessPass::PostProcessPass(Engine* engine, IShader* shader)
			: EngineObject(engine)
		{
			SafeAddRef(shader, &this->shader);
		}

		PostProcessPass::~PostProcessPass()
		{
			SafeRelease(&shader);

			UInt32 i = 0;
			while (i < inputTargets.Count())
			{
				IRenderTarget* target = inputTargets.GetKVP(i).GetKey();
				SafeRelease(&target);

				i++;
			}

			i = 0;
			while (i < outputTargets.Count())
			{
				IRenderTarget* target = outputTargets.GetKVP(i).GetKey();
				SafeRelease(&target);

				i++;
			}
		}
		#pragma endregion
		
		#pragma region Member
		void PostProcessPass::UpdateVars(const DrawArgs& args)
		{
		}
		#pragma endregion

		#pragma region Member - Get
		IShader* PostProcessPass::GetShader()
		{
			return shader;
		}

		const Dictionary<IRenderTarget*, cstring>* PostProcessPass::GetInput()
		{
			return &inputTargets;
		}

		const Dictionary<IRenderTarget*, UInt32>* PostProcessPass::GetOutput()
		{
			return &outputTargets;
		}
		#pragma endregion

		#pragma region Member - Add/Remove
		void PostProcessPass::AddInput(cstring varName, IRenderTarget* target)
		{
			inputTargets.Add(target, varName);
			SafeAddRef(&target);
		}

		void PostProcessPass::RemoveInput(IRenderTarget* target)
		{
			inputTargets.Remove(target);
			SafeRelease(&target);
		}

		void PostProcessPass::AddOutput(UInt32 slot, IRenderTarget* target)
		{
			outputTargets.Add(target, slot);
			SafeAddRef(&target);
		}

		void PostProcessPass::RemoveOutput(IRenderTarget* target)
		{
			outputTargets.Remove(target);
			SafeRelease(&target);
		}
		#pragma endregion
	}
}
