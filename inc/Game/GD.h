#pragma once

#pragma region Skills
#define SKILL_FLASH_DESC \
	12.3, 	/* Cooldown */ \
	15.0f, 	/* Range */ \
	0.0f, 	/* AOERange */ \
	0.0,  	/* Duration */ \
	4		/* MaxLevel */
const float SkillFlashCooldown[] = { 11.0f, 9.0f, 7.0f, 5.0f };

#define SKILL_HEALAURA_DESC \
	9.0, 	/* Cooldown */ \
	0.0f, 	/* Range */ \
	15.0f, 	/* AOERange */ \
	5.0,  	/* Duration */ \
	4		/* MaxLevel */
const double SkillHealAuraHealPerSecound[] = { 6.0f, 9.0f, 12.0f, 16.0f };

#define SKILL_ROCKET_DESC \
	8.5f, 	/* Cooldown */ \
	27.0f, 	/* Range */ \
	10.0f, 	/* AOERange */ \
	2000.0,	/* Duration */ \
	4		/* MaxLevel */
const double SkillRocketDamage[] = { 25.0f, 40.0f, 55.0f, 70.0f };

#define SKILL_SPIDERMINE_DESC \
	5.0, 	/* Cooldown */ \
	25.0f, 	/* Range */ \
	0.0f, 	/* AOERange */ \
	10.0,  	/* Duration */ \
	2		/* MaxLevel */
const double SkillSpiderMineDamage[] = { 30.0f, 60.0f };
#pragma endregion

#pragma region Hero
const double HeroHP = 350.0;
const double HeroHPPerLevel = 20.0;
const double ArmorPerLevel = 3.5;

const double HeroNeededXPFirstLevelUp = 100.0;

#define HERO_XP_CALC_NEXTLEVEL(last_level_needed, level) \
	(last_level_needed * 1.9)/* + (level * 10)*/

#define HERO_CALC_DEADTIME(level) \
	10.0 * (level + 1)

#define HERO_CALC_DEADPRICE(money, level) \
	(money / 100.0) * (10.0 + level + 1)
	
#pragma endregion

#pragma region Rewards
const float ResKillBot = 7.0f;
const float ResKillMesh = 15.0f;
const float ResKillTower = 150.0f;
const float ResKillBuilding = 250.0f;

const double XPKillBot = 17.0;
const double XPKillMesh = 17.0;
const double XPKillTower = 75.0;
const double XPKillBuilding = 150.0;
#pragma endregion

#pragma region Camera
const float CameraSpeed = 30.0f;
const float CameraSpeedFast = 60.0f;
const float CameraMinDist = 20.0f;
const float CameraMaxDist = 50.0f;

//1 degree = 0.0175 radians
const float CameraMaxAngle = 1.225f; // 70°
const float CameraMinAngle = 0.788f; // 45°
#pragma endregion

#pragma region Spawn
#define SPAWN_PLAYER_COUNT 5
#define SPAWN_ENEMY_COUNT 7

#define SPAWN_INTERVAL 25.0
#define SPAWN_UNIT_INTERVAL 0.5
#pragma endregion

#pragma region Charges
#define TOWER_BUILD_PRICE 100.0
#pragma endregion
