#pragma once

#pragma region Skills
#define SKILL_FLASH_DESC \
	12.3, 	/* Cooldown */ \
	7.0f, 	/* Range */ \
	0.0f, 	/* AOERange */ \
	0.0,  	/* Duration */ \
	4		/* MaxLevel */
const float SkillFlashRange[] = { 4.0f, 5.0f, 6.0f, 7.0f };

#define SKILL_HEALAURA_DESC \
	9.0, 	/* Cooldown */ \
	0.0f, 	/* Range */ \
	15.0f, 	/* AOERange */ \
	5.0,  	/* Duration */ \
	4		/* MaxLevel */
const double SkillHealAuraHealPerSecound[] = { 4.0f, 6.0f, 8.0f, 10.0f };

#define SKILL_ROCKET_DESC \
	4.5, 	/* Cooldown */ \
	25.0f, 	/* Range */ \
	20.0f, 	/* AOERange */ \
	2000.0,	/* Duration */ \
	4		/* MaxLevel */
const double SkillRocketDamage[] = { 10.0f, 15.0f, 20.0f, 25.0f };

#define SKILL_SPIDERMINE_DESC \
	5.0, 	/* Cooldown */ \
	25.0f, 	/* Range */ \
	0.0f, 	/* AOERange */ \
	10.0,  	/* Duration */ \
	2		/* MaxLevel */
const double SkillSpiderMineDamage[] = { 4.0f, 6.0f };
#pragma endregion

#pragma region Hero
const double HeroMaxHealthIncement = 10.0;
const double HeroNeededXPFirstLevelUp = 100.0;

#define HERO_XP_CALC_NEXTLEVEL(last_level_needed, level) \
	(last_level_needed * 1.5784) + (level * 10)

#define HERO_CALC_DEADTIME(level) \
	10.0 * (level + 1)

#define HERO_CALC_DEADPRICE(money, level) \
	(money / 100.0) * (10.0 + level + 1)
#pragma endregion

#pragma region Rewards
const float ResKillBot = 1.0f;
const float ResKillMesh = 10.0f;
const float ResKillTower = 150.0f;
const float ResKillBuilding = 250.0f;

const double XPKillBot = 15.0;
const double XPKillMesh = 20.0;
const double XPKillTower = 25.0;
const double XPKillBuilding = 35.0;
#pragma endregion

#pragma region Spawn
#define SPAWN_PLAYER_COUNT 5
#define SPAWN_ENEMY_COUNT 7

#define SPAWN_INTERVAL 60.0
#define SPAWN_UNIT_INTERVAL 0.75
#pragma endregion

#pragma region Charges
#define TOWER_BUILD_PRICE 150.0
#pragma endregion