
#include "Game/Skill.h"

#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/GoalThink.h"
#include "Game/SceneLevel.h"
#include "Game/UnitSelection.h"

#include "Core/Camera.h"
#include "Core/IPhysics.h"
#include "Core/ISpriteBatch.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		Skill::Skill(TikiBot* owner, const SkillDescription& desc)
			: owner(owner), EngineObject(owner->GetEngine()), gameState(owner->GetGameState()), onActivation(false), isReady(true), atWork(false), inRange(false),
			  icon(0), crosshair(0), description(desc), currentLevel(0), currentLevelString(L"0"), activateInRange(false),
			  workTimer(desc.DurationOfEffect), cooldownTimer(desc.Cooldown), flags(desc.Flags)
		{
			if (wstring(desc.TexNameIcon) != L"")
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/icons/" + wstring(desc.TexNameIcon)),
					&icon
				);
			}

			if (wstring(desc.TexNameCrosshair) != L"" && !this->flags.HasFlag(SF_TargetAura))
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/crosshair/" + wstring(desc.TexNameCrosshair)),
					&crosshair
				);
			}
			else if (!this->flags.HasFlag(SF_TargetAura))
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/crosshair/pointer"),
					&crosshair
				);
			}
		}

		Skill::~Skill()
		{
			SafeRelease(&icon);
			SafeRelease(&crosshair);
		}
		#pragma endregion

		#pragma region Member
		void Skill::Aktivate()
		{
			if (currentLevel < 1) return;

			if (isReady && flags.HasFlag(SF_Active))
			{
				if (flags.HasFlag(SF_TargetAura))
				{
					onActivation = false;
					isReady = false;
					atWork = true;
				}
				else
				{
					onActivation = true;

					targetPos = Vector3::Zero;
					targetBot = 0;
				}
			}
			else if (!isReady)
			{
				//TODO: Play Sound
			}
		}

		void Skill::Upgrade()
		{
			if (currentLevel < description.MaxLevel)
			{
				currentLevel++;

				wostringstream s;
				s << currentLevel;

				currentLevelString = s.str();

				internUpgrade();
			}
		}
		#pragma endregion

		#pragma region Member - Draw
		void Skill::Draw(const DrawArgs& args)
		{
			if (currentLevel < 1) return;

			if (onActivation && !activateInRange)
			{
				// TargetAOE - Drawing in FogOfWar-Shader
				if (flags.HasFlag(SF_TargetBot) || flags.HasFlag(SF_TargetPoint))
				{
					args.SpriteBatch->Draw(
						crosshair,
						args.Update.Input.MousePositionDisplay,
						0.0f,
						crosshair->GetCenter(),
						1.0f,
						1.0f,
						Color::White
					);
				}
			}

			internDraw(args);
		}
		#pragma endregion

		#pragma region Member - Update
		void Skill::Update(const UpdateArgs& args)
		{
			if (currentLevel < 1) return;

			if (atWork)
			{
				atWork = !workTimer.IsReady(args.Time);

				if (flags.HasFlag(SF_TargetAura))
				{					
					Vector2 pos = owner->GetController()->GetCenter().XZ();

					UInt32 i = 0;
					gameState->GetScene()->SceneGraph.Do([&](GameObject* go) {
						TikiBot* bot = go->GetComponent<TikiBot>();

						if (bot != 0 && bot->GetFaction() == owner->GetFaction())
						{
							float rad = description.AOERange + (float)bot->BRadius();

							float dist = Vector2::Distance(pos, bot->Pos());
							if (dist < rad)
							{
								internActivationAuraFrame(args, bot);
							}
						}

						i++;					
					});
				}
			}
			else if (!isReady)
			{
				isReady = cooldownTimer.IsReady(args.Time);
			}
			else if (args.Input.GetMouse(MB_Right) || args.Input.GetKeyPressed(KEY_ESCAPE))
			{
				onActivation = false;
				activateInRange = false;
			}
			else if (onActivation)
			{
				if (!activateInRange)
				{
					Ray r = gameState->GetScene()->GetMainCamera()->ScreenPointToRay(args.Input.MousePositionDisplay);
					RaycastHit hit;

					if (!engine->physics->RayCast(r, &hit))
					{
						TIKI_LOG("Error: Skill raycast failed.");
						return;
					}
					
					targetPos = hit.Point;
					targetBot = hit.Collider->GetGameObject()->GetComponent<TikiBot>();
				}

				inRange = Vector2::Distance(targetPos.XZ(), owner->Pos()) < description.ActivationRange;

				if ((args.Input.GetMousePressed(MB_Left) || activateInRange) && inRange)
				{
					bool activated = false;

					if (flags.HasFlag(SF_TargetAOE))
					{
						activated = true;
						this->internActivationPoint(targetPos);
					}
					else if (flags.HasFlag(SF_TargetBot) || flags.HasFlag(SF_TargetPoint))
					{
						if (targetBot != 0 && flags.HasFlag(SF_TargetBot))
						{
							activated = this->internActivationBot(targetBot);								
						}
						else if (flags.HasFlag(SF_TargetPoint))
						{
							activated = true;
							this->internActivationPoint(targetPos);
						}
					}

					if (activated)
					{
						owner->GetBrain()->RemoveAllSubgoals();

						activateInRange = false;
						onActivation = false;
						isReady = false;
						atWork = true;
					}
					// else play sound/throw exception???
				}
				else if (args.Input.GetMousePressed(MB_Left) && !inRange)
				{
					activateInRange = true;
					gameState->GetUnitSelection()->MoveCommand(targetBot, targetPos, false, false);
				}
			}

			internUpdate(args);
		}
		#pragma endregion
	}
}