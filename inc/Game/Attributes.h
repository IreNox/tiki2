#pragma once

#define TIKI_ALL_ATTRIBUTES \
	TA_MaxHealth, \
	TA_HealthRegValue, \
	TA_HealthRegPercent, \
	TA_MaxSpeed, \
	TA_Armor, \
	TA_TurnRate, \
	TA_Loot, \
	TA_SightRadius, \
	TA_WeaponDamage, \
	TA_WeaponFireSpeed

namespace TikiEngine
{
	namespace AI
	{
		enum Attributes
		{
			TA_MaxHealth, 
			TA_HealthRegValue, 
			TA_HealthRegPercent, 
			TA_MaxSpeed, 
			TA_Armor, 
			TA_TurnRate, 
			TA_Loot, 
			TA_SightRadius, 
			TA_WeaponDamage, 
			TA_WeaponFireSpeed
		};
	}
}