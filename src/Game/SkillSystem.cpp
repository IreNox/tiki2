
#include "Game/SkillSystem.h"
#include "Game/TikiBot.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace AI
	{
		#pragma region Class
		SkillSystem::SkillSystem(TikiBot* owner)
			: owner(owner), heroLevel(1), skillUpgrades(1), currentXp(0), nextLevelXp(HeroNeededXPFirstLevelUp), lastLevelXp(0),
			  attmodMaxHealth(TA_MaxHealth, AMT_PerPercent, HeroMaxHealthIncement, 0)
		{
		}

		SkillSystem::~SkillSystem()
		{
			FOREACH(skills, SafeRelease(&skills[i]));
		}
		#pragma endregion

		#pragma region Member
		void SkillSystem::Init()
		{

		}

		void SkillSystem::Draw(const DrawArgs& args)
		{
			FOREACH_PTR_CALL(skills, Draw(args));
		}

		void SkillSystem::Update(const UpdateArgs& args)
		{
			static Key keys[4] = { KEY_Q, KEY_W, KEY_E, KEY_R };

			UInt32 i = 0;
			while (i < skills.Count())
			{
				if (args.Input.GetKeyPressed(keys[i]))
				{
					skills[i]->Aktivate();
				}

				skills[i]->Update(args);
				i++;
			}
		}
		#pragma endregion

		#pragma region Member - XP
		void SkillSystem::IncementXP(double xp)
		{
			currentXp += xp;

			while (currentXp > nextLevelXp)
			{
				heroLevel++;
				skillUpgrades++;
				attmodMaxHealth.SetValue(10 + (2.1458 * heroLevel));
				
				owner->GetAttSys().UpdateModifier(&attmodMaxHealth);

				lastLevelXp = nextLevelXp;
				nextLevelXp = HERO_XP_CALC_NEXTLEVEL(lastLevelXp, heroLevel);

				this->LevelUp.RaiseEvent(
					owner,
					HeroLevelUpEventArgs(currentXp, nextLevelXp)
				);
			}
		}
		#pragma endregion
	}
}