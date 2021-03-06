#pragma once

#include "Core/EngineObject.h"

#include "Core/PostProcessPass.h"
#include "Core/List.h"

#include "Core/DrawArgs.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Resources;

		class PostProcess : public EngineObject
		{
		public:

			PostProcess(Engine* engine);
			~PostProcess();

			PostProcessPass* AddPass(PostProcessPass* pass);
			void RemovePass(PostProcessPass* pass);

			inline const List<PostProcessPass*>& GetPasses() { return passes; }

			virtual void UpdatePass(UInt32 index, const DrawArgs& args);

		protected:

			List<PostProcessPass*> passes;

		};
	}
}
