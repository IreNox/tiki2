#pragma once

#include "Core/EngineObject.h"

#include "Core/PostProcessPass.h"
#include "Core/IShader.h"
#include "Core/List.h"

#include "Core/GameTime.h"

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

			const List<PostProcessPass*>* GetPasses();

			virtual void UpdatePass(UInt32 index, const GameTime& time);

		protected:

			List<PostProcessPass*> passes;

		};
	}
}