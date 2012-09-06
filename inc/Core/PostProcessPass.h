#pragma once

#include "Core/EngineObject.h"

#include "Core/IShader.h"
#include "Core/IRenderTarget.h"

#include "Core/GameTime.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Resources;

		class PostProcessPass : public EngineObject
		{
		public:

			PostProcessPass(Engine* engine, IShader* shader);
			~PostProcessPass();

			void AddInput(string varName, IRenderTarget* target);
			void RemoveInput(IRenderTarget* target);

			void AddOutput(UInt32 slot, IRenderTarget* target);
			void RemoveOutput(IRenderTarget* target);

			IShader* GetShader();
			const Dictionary<IRenderTarget*, string>* GetInput();
			const Dictionary<IRenderTarget*, UInt32>* GetOutput();

			virtual void UpdateVars(const GameTime& time);

		private:

			IShader* shader;

			Dictionary<IRenderTarget*, string> inputTargets;
			Dictionary<IRenderTarget*, UInt32> outputTargets;

		};
	}
}