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

			void internActivation(const Vector3& target);

			void internDraw(const DrawArgs& args);
			void internUpdate(const UpdateArgs& args);

		private:

			static SkillDescription Desc;

		};
	}
}