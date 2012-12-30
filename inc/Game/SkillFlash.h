#pragma once

#include "Game/Skill.h"

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

		private:

			static SkillDescription Desc;

		};
	}
}