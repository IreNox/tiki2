
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
		Skill::Skill(TikiBot* owner, SkillFlags flags, double cooldown, float crosshairSize, wstring texture)
			: owner(owner), EngineObject(owner->GetEngine()), gameState(owner->GetGameState()), cooldownTimer(cooldown),
			flags(flags), crosshairSize(crosshairSize), onActivation(false), isReady(false), atWork(false)
		{
			if (texture != L"" && this->flags.HasFlag(ST_TargetAOE))
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/" + texture),
					&crosshair
				);
			}
			else
			{
				SafeAddRef(
					engine->content->LoadTexture(L"hud/mouse_crosshair"),
					&crosshair
				);
			}
		}

		Skill::~Skill()
		{
			SafeRelease(&crosshair);
		}

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

		void Skill::Draw(const DrawArgs& args)
		{
			if (onActivation)
			{
				if (flags.HasFlag(ST_TargetBot))
				{
					args.SpriteBatch->Draw(
						crosshair,
						args.Update.Input.MousePositionDisplay,
						0.0f,
						crosshair->GetCenter(),
						1.0f,
						1.0f
					);
				}
				// TargetAOE - Drawing in FOW-Shader
				
				if (args.Update.Input.GetMousePressed(MB_Left))
				{
					bool activated = false;

					Ray r = args.CurrentCamera->ScreenPointToRay(args.Update.Input.MousePositionDisplay);
					RaycastHit hit;

					if (engine->physics->RayCast(r, &hit))
					{
						if (flags.HasFlag(ST_TargetAOE))
						{
							activated = true;
							this->internActivation(args.Update, hit.Point);
						}
						else
						{
							GameObject* obj = hit.Collider->GetGameObject();

							if (obj->GetComponent<TikiBot>() != 0)
							{
								activated = true;
								this->internActivation(args.Update, obj);
							}
						}
					}

					if (activated)
					{
						onActivation = false;
						isReady = false;
					}
					// else play sound/throw exception???
				}
			}
		}

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
			// Activation in Draw-Method
			// TODO: only for debugging!!!!
			else if (args.Input.GetKeyPressed(KEY_Q))
			{
				this->Aktivate();
			}
		}
	}
}