#pragma once

#include "Core/DrawArgs.h"

//#include "Game/Skill.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		class SkillSystem
		{
		public:
			SkillSystem(TikiBot* owner) { this->owner = owner; }
			~SkillSystem() { }

			void Init() { }

			void Update(const UpdateArgs& args) { }

			void Draw(const DrawArgs& args) { }


		private:
			TikiBot* owner;
			//List<Skill> skills;


		};
	}
}
