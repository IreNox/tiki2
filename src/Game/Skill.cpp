
#include "Game/Skill.h"

#include "Game/GameState.h"
#include "Game/TikiBot.h"

#include "Core/Camera.h"
#include "Core/IPhysics.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		Skill::Skill(TikiBot* owner, const SkillDescription& desc)
			: owner(owner), EngineObject(owner->GetEngine()), gameState(owner->GetGameState()), onActivation(false), isReady(true), atWork(false),
			  icon(0), crosshair(0), description(desc), inRange(false),
			  cooldownTimer(desc.Cooldown),	flags(desc.Flags)
		{
			if (wstring(desc.TexNameIcon) != L"")
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/icons/" + wstring(desc.TexNameIcon)),
					&icon
				);
			}

			if (wstring(desc.TexNameCrosshair) != L"" && !this->flags.HasFlag(ST_TargetAura))
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/crosshair/" + wstring(desc.TexNameCrosshair)),
					&crosshair
				);
			}
			else if (!this->flags.HasFlag(ST_TargetAura))
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
			if (isReady && !flags.HasFlag(ST_Passive))
			{
				onActivation = true;
			}
			else if (!isReady)
			{
				// play sound
			}
		}
		#pragma endregion

		#pragma region Member - Draw
		void Skill::Draw(const DrawArgs& args)
		{
			if (onActivation)
			{
				Ray r = args.CurrentCamera->ScreenPointToRay(args.Update.Input.MousePositionDisplay);
				RaycastHit hit;

				if (engine->physics->RayCast(r, &hit))
				{
					inRange = Vector2::Distance(hit.Point.XZ(), owner->Pos()) < description.ActivationRange;

					if (args.Update.Input.GetMousePressed(MB_Left) && inRange)
					{
						bool activated = false;
					
						if (flags.HasFlag(ST_TargetAOE))
						{
							activated = true;
							this->internActivation(hit.Point);
						}
						else if (flags.HasFlag(ST_TargetBot) || flags.HasFlag(ST_TargetNoBot))
						{
							GameObject* obj = hit.Collider->GetGameObject();

							if (obj->GetComponent<TikiBot>() != 0 && flags.HasFlag(ST_TargetBot))
							{
								activated = true;
								this->internActivation(obj);
							}
							else if (flags.HasFlag(ST_TargetNoBot))
							{
								activated = true;
								this->internActivation(hit.Point);
							}
						}
						else if (flags.HasFlag(ST_TargetAura))
						{
							activated = true;
							this->internActivation(owner->Pos3D());
						}

						if (activated)
						{
							onActivation = false;
							isReady = false;
						}
						// else play sound/throw exception???
					}
					else if (args.Update.Input.GetMousePressed(MB_Left) && !inRange)
					{
						onActivation = false;
					}
				}

				// TargetAOE - Drawing in FogOfWar-Shader
				if (flags.HasFlag(ST_TargetBot) || flags.HasFlag(ST_TargetNoBot))
				{
					args.SpriteBatch->Draw(
						crosshair,
						args.Update.Input.MousePositionDisplay,
						0.0f,
						crosshair->GetCenter(),
						1.0f,
						1.0f,
						(inRange ? Color::White : Color::Black)
					);
				}
			}

			internDraw(args);
		}
		#pragma endregion

		#pragma region Member - Update
		void Skill::Update(const UpdateArgs& args)
		{
			if (!isReady)
			{
				isReady = cooldownTimer.IsReady(args.Time);
			}
			else if (args.Input.GetMouse(MB_Right) || args.Input.GetKeyPressed(KEY_ESCAPE))
			{
				onActivation = false;
			}
			// Activation in Draw-Method because CurrentCamera

			internUpdate(args);
		}
		#pragma endregion
	}
}