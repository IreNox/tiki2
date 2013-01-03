#pragma once

#include "Game/Skill.h"
#include "Game/PEHealAura.h"
#include "Core/IParticleRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
        using namespace TikiEngine::Components;
        using namespace TikiEngine::Particles;

		class SkillHealAura : public Skill
		{
		public:

			SkillHealAura(TikiBot* owner);
			~SkillHealAura();

		protected:

			void internActivationAuraFrame(const UpdateArgs& args, TikiBot* target);
            void internUpdate(const UpdateArgs& args);

		private:

			static SkillDescription Desc;
            //PEHealAura* peHeal;
            IParticleRenderer* prHeal;
		};
	}
}