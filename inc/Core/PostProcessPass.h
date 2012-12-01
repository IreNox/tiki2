#pragma once

#include "Core/EngineObject.h"

#include "Core/IShader.h"
#include "Core/IRenderTarget.h"

#include "Core/GameTime.h"
#include "Core/Dictionary.h"

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
			void SetInput(string varName, IRenderTarget* target);
			//void RemoveInput(IRenderTarget* target);

			void AddOutput(UInt32 slot, IRenderTarget* target);
			void SetOutput(UInt32 slot, IRenderTarget* target);
			//void RemoveOutput(IRenderTarget* target);

			inline IShader* GetShader() { return shader; }
			inline const Dictionary<string, IRenderTarget*>& GetInput() { return inputTargets; }
			inline const Dictionary<UInt32, IRenderTarget*>& GetOutput() { return outputTargets; }

			virtual void UpdateVars(const DrawArgs& args);

		private:

			IShader* shader;

			Dictionary<string, IRenderTarget*> inputTargets;
			Dictionary<UInt32, IRenderTarget*> outputTargets;

		};
	}
}
