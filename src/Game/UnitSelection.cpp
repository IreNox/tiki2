

#include "Game/UnitSelection.h"
#include "Game/GameState.h"

#include "Game/SensorMemory.h"
#include "Game/SceneLevel.h"
#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/BuildSlot.h"
#include "Game/GoalThink.h"
#include "Game/ProjectileManager.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"

#include "Game/GD.h"

namespace TikiEngine
{

	namespace Game
	{
		#pragma region Class
		UnitSelection::UnitSelection(GameState* gameState)
			: EngineObject(gameState->GetEngine()), gameState(gameState), 
			enabled(true), dirty(true), mouseButton(false), changed(false),
			TIKI_NEWDragging(false)
		{
			selectionRect = RectangleF::Create(0, 0, 0, 0);

			selectButton = TIKI_NEW GUIButton(gameState->GetEngine());
			selectButton->AddRef();
		}

		UnitSelection::~UnitSelection()
		{
			selectedUnits.Clear();
			selectedSlots.Clear();
			SafeRelease(&selectButton);
		}
		#pragma endregion

		#pragma region Member - Commands
		void UnitSelection::BuildCommand(BuildSlot* slot)
		{
			// only create once
			if (slot->Enabled())
			{
				if (gameState->GetResource() >= TOWER_BUILD_PRICE)
				{
					slot->Disable();
					gameState->GetBotFactory()->CreatePlayerTower(
						slot->GetGameObject()
					);

					gameState->DecrementResource(TOWER_BUILD_PRICE);
				}
				else
				{
					//engine->sound->Play(
					//	engine->content->LoadSound(L"no money")
					//);
				}
			}
		}

		void UnitSelection::MoveCommand(TikiBot* target, const Vector3& pos, bool attackMove, bool addWaypoint)
		{
			UInt32 i = 0;
			while (i < selectedUnits.Count())
			{
				TikiBot* bot = selectedUnits[i]->GetComponent<TikiBot>();

				if (bot != 0 && bot->GetBrain() != 0)
				{
					//bot->TakePossession();

					// if the shift key is pressed down at the same time as clicking then the
					// movement command will be queued
					if (addWaypoint)
					{
						if (bot->EntityType() != ET_Tower)
						{
							if (attackMove)
								bot->GetBrain()->QueueGoalAttackMove(pos);
							else
								bot->GetBrain()->QueueGoalMoveToPosition(pos);
						}

					}
					else if (attackMove)
					{
						bot->GetBrain()->RemoveAllSubgoals();
						bot->GetBrain()->AddGoalAttackMove(pos);
					}
					else
					{
						if (target != 0)
						{
							// don't attack yourself dude
							if (target->ID() != bot->ID())
							{
								bot->GetBrain()->RemoveAllSubgoals();
								//engine->HLog.Write("Target found.");
								bot->GetBrain()->AddGoalAttackGlobalTarget(target);

							}
						}
						else
						{
							if (bot->EntityType() != ET_Tower)
							{
								bot->GetBrain()->RemoveAllSubgoals();
								bot->GetBrain()->AddGoalMoveToPosition(pos);
							}
						}

					}

				}

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Get/Draw
		List<GameObject*>* UnitSelection::GetSelectedUnits()
		{
			return &selectedUnits;
		}

		List<GameObject*>* UnitSelection::GetSelectedSlots()
		{
			return &selectedSlots;
		}

		void UnitSelection::Draw(const DrawArgs& args)
		{
			if(enabled && selectionRect.Width != 0 && selectionRect.Height != 0)
				selectButton->Draw(args);
		}
		#pragma endregion

		#pragma region Member - Update
		void UnitSelection::Update(const UpdateArgs& args)
		{
			if (!enabled) return;

			this->changed = false;
			this->dirty = false;

			// Handle Rectangle
			// Mouse left button has just been pressed down
			if (args.Input.GetMousePressed(MB_Left))
			{
				if (selectedUnits.Count() != 0) changed = true;

				selectionStartPoint = args.Input.MousePositionDisplay;

				// Set the selection box starting point
				selectionRect.X = args.Input.MousePositionDisplay.X;
				selectionRect.Y = args.Input.MousePositionDisplay.Y;
				selectButton->SPosition() = Vector2(selectionRect.X, selectionRect.Y);
			
				TIKI_NEWDragging = true;
			}

			if(args.Input.GetMouse(MB_Left))
			{
				// Mouse left button is being held down ( dragging )
				// Calculate TIKI_NEW width,height
				selectionRect.Width = abs(args.Input.MousePositionDisplay.X - selectionStartPoint.X);
				selectionRect.Height = abs(args.Input.MousePositionDisplay.Y - selectionStartPoint.Y);

				if (selectionStartPoint.X > args.Input.MousePositionDisplay.X)
				{
					selectionRect.X = args.Input.MousePositionDisplay.X;
				}

				if (selectionStartPoint.Y > args.Input.MousePositionDisplay.Y)
				{
					selectionRect.Y = args.Input.MousePositionDisplay.Y;
				}

				selectButton->SPosition() = Vector2(selectionRect.X, selectionRect.Y);
				selectButton->SSize() = Vector2(selectionRect.Width, selectionRect.Height);
			}

			if (args.Input.GetMouseRelease(MB_Left))
			{
				selectionRect = RectangleF::Create(0, 0, 0, 0);
			}

			UInt32 i = 0;
			List<GameObject*> gos;
			gameState->GetScene()->SceneGraph.FindInFrustum(gos);

			while (i < gos.Count())
			{
				int found = 0;
				GameObject* go = gos[i];

				#pragma region SlotSelection
				BuildSlot* slot = 0;
				slot = go->GetComponent<BuildSlot>();
				if(slot != 0)
				{
					Camera* cam = gameState->GetScene()->GetMainCamera();
					Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();

					Matrix vp = cam->WorldToScreen();
					Vector3 screenPos = Matrix::Project(slot->GetGameObject()->PRS.GPosition(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

					if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && (!selectedSlots.Contains(go) || TIKI_NEWDragging))
					{
						engine->HLog.Write("Rect-Select slot.");
						selectedSlots.Add(go);
						changed = true;
						found = 1;
					}

					float eps = 15.0f;
					if (args.Input.GetMousePressed(MB_Left))
					{
						if(screenPos.X <= selectionRect.X + eps && 
							screenPos.X >= selectionRect.X - eps &&
							screenPos.Y <= selectionRect.Y + eps && 
							screenPos.Y >= selectionRect.Y - eps)
						{
							engine->HLog.Write("click-Select slot.\n");
							selectedSlots.Add(go);
							changed = true;
							found = 1;
						}

					}

				}
				#pragma endregion

				#pragma region UnitSelection
				TikiBot* ent = go->GetComponent<TikiBot>();
				if(ent != 0)
				{				
					// select player units only
					if (ent->GetFaction() == 0)
					{
						Camera* cam = gameState->GetScene()->GetMainCamera();
						Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();

						Matrix vp = cam->WorldToScreen(); //Matrix::CreateTranslation(cam->GetGameObject()->PRS.GPosition()) *
						//Matrix::Transpose(cam->GetViewMatrix()) * 
						//Matrix::Transpose(cam->GetProjectionMatrix());

						Vector3 screenPos = Matrix::Project(ent->Pos3D(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

						if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && (!selectedUnits.Contains(go) || TIKI_NEWDragging))
						{
							//engine->HLog.Write("Rect-Select unit.");
							selectedUnits.Add(go);
							changed = true;
							found = 2;
						}

						float eps = 15.0f;
						if (args.Input.GetMousePressed(MB_Left))
						{
							if(screenPos.X <= selectionRect.X + eps && 
								screenPos.X >= selectionRect.X - eps &&
								screenPos.Y <= selectionRect.Y + eps && 
								screenPos.Y >= selectionRect.Y - eps)
							{
								//engine->HLog.Write("click-Select unit.\n");
								// clear list from last selection								
								selectedUnits.Add(go);
								changed = true;
								found = 2;
							}

						}
					}

					// check if dead and clear from list
					if (ent->IsDead())
					{
						RemoveBot(ent, args);
						changed = true;
					}
				}
				#pragma endregion

				if (found && TIKI_NEWDragging && !args.Input.GetKey(KEY_LSHIFT))
				{
					selectedUnits.Clear();
					selectedSlots.Clear();
					(found == 1 ? selectedSlots : selectedUnits).Add(go);
					TIKI_NEWDragging = false;
				}

				i++;
			}

			if (changed)
				gameState->UnitSelectionChanged.RaiseEvent(gameState, UnitSelectionChangedArgs(selectedUnits, selectedSlots));

			selectButton->Update(args);
		}
		#pragma endregion

		#pragma region Member - RemoveBot
		void UnitSelection::RemoveBot(TikiBot* bot, const UpdateArgs& args)
		{
			UInt32 i = 0;
			while (i < gameState->GetScene()->SceneGraph.GetAllGameObjects().Count())
			{
				GameObject* go = gameState->GetScene()->SceneGraph.GetAllGameObjects()[i];

				TikiBot* ent = go->GetComponent<TikiBot>();
				if(ent != 0 && ent->EntityType() != ET_Building)
				{
					ent->GetSensorMem()->RemoveBotFromMemory(bot);

					// if the removed bot is the target, clear targets
					if (ent->GetTargetSys()->GetTarget() == bot)
						ent->GetTargetSys()->ClearTarget();

					if (ent->GetTargetSys()->GetGlobalTarget() == bot)
						ent->GetTargetSys()->ClearGlobalTarget();
				}

				i++;
			}

			// remove bot from lists
			//engine->HLog.Write("Removed dead bot.");

			if (selectedUnits.Contains(bot->GetGameObject()))
			{
				//engine->HLog.Write("Removed dead bot from selction.");
				selectedUnits.Remove(bot->GetGameObject());
			}

			if (bot->EntityType() == ET_Tower)
			{
				//engine->HLog.Write("Dead tower, Adding Player BuiltSlot");

				// Save old tower position
				Vector3 towerPos = bot->GetController()->GetCenter();
				towerPos.Y -= (bot->GetController()->GetHeight() * 0.5f + bot->GetController()->GetRadius());

				gameState->GetProjectiles()->AddExplosionEffect(towerPos, true);

				// Clear old GameObject
				gameState->GetScene()->RemoveElement(bot->GetGameObject());

				// Create TIKI_NEW GameObject and BuildSlot
				GameObject* go = TIKI_NEW GameObject(engine);
				gameState->GetBotFactory()->CreateBuildSlot(go);
				go->PRS.SPosition() = towerPos;

				BuildSlot* slot = go->GetComponent<BuildSlot>();
				slot->Enable();
			}
			else if(bot->EntityType() == ET_Building)
			{
				Vector3 buildingPos = bot->GetController()->GetCenter();
				buildingPos.Y -= (bot->GetController()->GetHeight() * 0.5f + bot->GetController()->GetRadius());


				gameState->GetProjectiles()->AddExplosionEffect(buildingPos, true);

				gameState->GetScene()->RemoveElement(bot->GetGameObject());
			}
			else if (bot->EntityType() == ET_Bot || bot->EntityType() == ET_Hero)
			{
				bot->IncreaseTimeSInceDead(args.Time.ElapsedTime);
				
				const double DeathAnimationDuration = 2.0f;
				if (bot->GetTimeSinceDead() >= DeathAnimationDuration)
				{
					bot->SetTimeSinceDead(0);
					gameState->GetScene()->RemoveElement(bot->GetGameObject());
				}
			}
			else
			{
				gameState->GetScene()->RemoveElement(bot->GetGameObject());
			}
		}
		#pragma endregion 
	}
}
