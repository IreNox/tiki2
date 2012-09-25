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

			void AddInput(cstring varName, IRenderTarget* target);
			void RemoveInput(IRenderTarget* target);

			void AddOutput(UInt32 slot, IRenderTarget* target);
			void RemoveOutput(IRenderTarget* target);

			IShader* GetShader();
			const Dictionary<IRenderTarget*, cstring>* GetInput();
			const Dictionary<IRenderTarget*, UInt32>* GetOutput();

			virtual void UpdateVars(const DrawArgs& args);

		private:

			IShader* shader;

			Dictionary<IRenderTarget*, cstring> inputTargets;
			Dictionary<IRenderTarget*, UInt32> outputTargets;

		};
	}
}