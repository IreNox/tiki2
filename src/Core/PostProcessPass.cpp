
#include "Core/PostProcessPass.h"
#include "Core/TypeGlobals.h"

#include "Core/HelperLog.h"

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
				IRenderTarget* target = inputTargets.GetKVP(i).GetValue();
				SafeRelease(&target);

				i++;
			}

			i = 0;
			while (i < outputTargets.Count())
			{
				IRenderTarget* target = outputTargets.GetKVP(i).GetValue();
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

		#pragma region Member - Add/Remove
		void PostProcessPass::AddInput(string varName, IRenderTarget* target)
		{
			inputTargets.Add(varName, target);
			SafeAddRef(&target);
		}

		void PostProcessPass::SetInput(string varName, IRenderTarget* target)
		{
			SafeRelease(&inputTargets[varName]);
			inputTargets[varName] = target;
			target->AddRef();
		}

		//void PostProcessPass::RemoveInput(IRenderTarget* target)
		//{
		//	inputTargets.Remove(target);
		//	SafeRelease(&target);
		//}

		void PostProcessPass::AddOutput(UInt32 slot, IRenderTarget* target)
		{
			outputTargets.Add(slot, target);
			SafeAddRef(&target);
		}

		void PostProcessPass::SetOutput(UInt32 slot, IRenderTarget* target)
		{
			SafeRelease(&outputTargets[slot]);
			outputTargets[slot] = target;
			outputTargets[slot]->AddRef();
		}

		//void PostProcessPass::RemoveOutput(IRenderTarget* target)
		//{
		//	outputTargets.Remove(target);
		//	SafeRelease(&target);
		//}
		#pragma endregion
	}
}
