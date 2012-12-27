#pragma once

#include "Core/DrawArgs.h"

#include "Game/Skill.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Game;

		class TikiBot;

		class SkillSystem
		{
		public:

			SkillSystem(TikiBot* owner);
			~SkillSystem();

			void Init();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			inline void AddSkill(Skill* skill) { skills.Add(skill); }
			inline List<Skill*>& GetSkills() { return skills; }

		private:

			TikiBot* owner;
						
			List<Skill*> skills;

		};
	}
}
