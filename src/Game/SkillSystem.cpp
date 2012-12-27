
#include "Game/SkillSystem.h"

namespace TikiEngine
{
	namespace AI
	{
		#pragma region Class
		SkillSystem::SkillSystem(TikiBot* owner)
			: owner(owner)
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
			FOREACH_PTR_CALL(skills, Update(args));
		}
		#pragma endregion
	}
}