#pragma once

#include "Game/Skill.h"
#include "Game/EventHeroEvents.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Game;

		class TikiBot;

		class SkillSystem
		{
		public:

			HeroLevelUpEvent LevelUp;

			SkillSystem(TikiBot* owner);
			~SkillSystem();

			void Init();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			inline void AddSkill(Skill* skill) { skills.Add(skill); }
			inline List<Skill*>& GetSkills() { return skills; }

			void IncementXP(double xp);

			inline double GetXP() const { return currentXp; }
			inline double GetXPLastLevel() const { return lastLevelXp; }
			inline double GetXPNextLevel() const { return nextLevelXp; }

			inline UInt32 GetLevel() const { return heroLevel; }

			inline void UpgradeSkill(UInt32 index) { skills[index]->Upgrade(); skillUpgrades--; }
			inline UInt32 GetSkillUpgrades() const { return skillUpgrades; }

		private:

			TikiBot* owner;

			double currentXp;
			double lastLevelXp;
			double nextLevelXp;

			UInt32 heroLevel;
			UInt32 skillUpgrades;
						
			List<Skill*> skills;

		};
	}
}
