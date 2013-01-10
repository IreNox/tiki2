#pragma once

#include "Game/Skill.h"

#include "Core/IContentManager.h"
#include "Core/IParticleRenderer.h"
#include "Game/PEFlash.h"

namespace TikiEngine
{
	namespace Game
	{
		class SkillFlash : public Skill
		{
		public:

			SkillFlash(TikiBot* owner);
			~SkillFlash();

		protected:

			void internActivationPoint(const Vector3& target);

			void internUpgrade();

		private:
			IParticleRenderer* prFlash;
			static SkillDescription Desc;

		};
	}
}