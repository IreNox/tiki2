

#include "Game/UnitSelection.h"
#include "Game/GameState.h"

#include "Game/SensorMemory.h"
#include "Game/SceneLevel.h"
#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/BuildSlot.h"
#include "Game/GoalThink.h"

#include "Core/IPhysics.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{

	namespace Game
	{
		#pragma region Class
		UnitSelection::UnitSelection(GameState* gameState)
			: EngineObject(gameState->GetEngine()), gameState(gameState), 
			enabled(true), dirty(true), mouseButton(false), changed(false),
			newDragging(false)
		{
			selectionRect = RectangleF::Create(0, 0, 0, 0);

			selectButton = new GUIButton(gameState->GetEngine());
			selectButton->AddRef();
		}

		UnitSelection::~UnitSelection()
		{
			selectedUnits.Clear();
			selectedSlots.Clear();
			SafeRelease(&selectButton);
		}
		#pragma endregion

		#pragma region Member - MoveCommand
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
#if TIKI_USE_SCENEGRAPH
			if (enabled && mouseButton)
				selectButton->Draw(args);

			this->selectionFrustum.Draw(args);
#else
			if(enabled && selectionRect.Width != 0 && selectionRect.Height != 0)
				selectButton->Draw(args);
#endif
		}
		#pragma endregion

		#pragma region Member - Update
		void UnitSelection::Update(const UpdateArgs& args)
		{
			if (!enabled) return;

			this->changed = false;
			this->dirty = false;

#if TIKI_USE_SCENEGRAPH && 0
			// Handle Rectangle
			// Mouse left button has just been pressed down
			if (args.Input.GetMousePressed(MB_Left))
			{
				if (selectedUnits.Count() != 0) changed = true;

				selectionStartPoint = args.Input.MousePositionDisplay;

				// Set the selection box starting point
				selectionRect.X = args.Input.MousePositionDisplay.X;
				selectionRect.Y = args.Input.MousePositionDisplay.Y;
				selectionRect.Width = 0;
				selectionRect.Height = 0;
				selectButton->SPosition() = Vector2(selectionRect.X, selectionRect.Y);
				this->dirty = true;
			}

			if(args.Input.GetMouse(MB_Left))
			{
				// Mouse left button is being held down ( dragging )
				// Calculate new width,height
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
				this->dirty = true;
			}

			if (args.Input.GetMouseRelease(MB_Left))
			{
				//selectionRect = RectangleF::Create(0, 0, 0, 0);
				this->dirty = true;
				
			}

			this->mouseButton = args.Input.GetMouse(MB_Left);

			if(!dirty)
				return;

			//this->worldToScreen = gameState->GetScene()->GCamera()->WorldToScreen();

			Matrix view = Matrix::Transpose(gameState->GetScene()->GCamera()->GetViewMatrix());
			Matrix proj = Matrix::Transpose(gameState->GetScene()->GCamera()->GetProjectionMatrix());

			proj = Frustum::ProjectionRectangle(
				selectionRect,
				engine->graphics->GetViewPort()->GetSize(),
				proj);


			selectionFrustum.CreatePlanes(view * proj);

			this->gameState->GetScene()->SceneGraph.Do([&](GameObject* go){
				
				if(selectionFrustum.PointInFrustum(go->PRS.GPosition()))
				{
					BuildSlot* slot = go->GetComponent<BuildSlot>();
					if(slot != 0)
					{
						HandleBuildSlot(go);
						return;
					}

					TikiBot* bot = go->GetComponent<TikiBot>();
					if(bot != 0)
					{
						HandleTikiBot(go);
						return;
					}
				}
			});

			//this->gameState->GetScene()->SceneGraph.Do([&](GameObject* go){ this->HandleBuildSlot(go); });
			//this->gameState->GetScene()->SceneGraph.Do([&](GameObject* go){ this->HandleTikiBot(go); });
#else
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
			
				newDragging = true;
			}

			if(args.Input.GetMouse(MB_Left))
			{
				// Mouse left button is being held down ( dragging )
				// Calculate new width,height
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
					Vector3 screenPos = Vector3::Project(slot->GetGameObject()->PRS.GPosition(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

					if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && (!selectedSlots.Contains(go) || newDragging))
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

						Vector3 screenPos = Vector3::Project(ent->Pos3D(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

						if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && (!selectedUnits.Contains(go) || newDragging))
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
						RemoveBot(ent);
						changed = true;
					}
				}
				#pragma endregion

				if (found && newDragging && !args.Input.GetKey(KEY_LSHIFT))
				{
					selectedUnits.Clear();
					selectedSlots.Clear();
					(found == 1 ? selectedSlots : selectedUnits).Add(go);
					newDragging = false;
				}

				i++;
			}
#endif

			if (changed)
				gameState->UnitSelectionChanged.RaiseEvent(gameState, UnitSelectionChangedArgs(selectedUnits, selectedSlots));

			selectButton->Update(args);
		}
		#pragma endregion

		#pragma region Member - Helper
		void UnitSelection::HandleTikiBot(GameObject* go)
		{
			TikiBot* ent = go->GetComponent<TikiBot>();

			if(ent->GetFaction() == 0)
			{
				if(!selectedUnits.Contains(go))
				{
					selectedUnits.Add(go);
					changed = true;
				}
			}
			if(ent->IsDead())
				RemoveBot(ent);


			//TikiBot* ent = go->GetComponent<TikiBot>();
			//if(ent == 0)
			//	return;

			//if(ent->GetFaction() == 0)
			//{
			//	if(IsUnderMouse(go, this->worldToScreen) && !selectedUnits.Contains(go))
			//	{
			//		selectedUnits.Add(go);
			//		changed = true;
			//	}
			//}
			//if(ent->IsDead())
			//	RemoveBot(ent);
		}

		void UnitSelection::HandleBuildSlot(GameObject* go)
		{
			BuildSlot* slot = go->GetComponent<BuildSlot>();
			if(slot == 0)
				return;
		}

		bool UnitSelection::IsUnderMouse(GameObject* go, Matrix& worldToScreen, float eps)
		{
			Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();
			Vector3 screenPos = Vector3::Project(go->PRS.GPosition(), 0, 0, bbDim.X, bbDim.Y, -1, 1, worldToScreen);
			if(selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)))
				return true;
			
			if(mouseButton)
			{
				if(screenPos.X <= selectionRect.X + eps && 
					screenPos.X >= selectionRect.X - eps &&
					screenPos.Y <= selectionRect.Y + eps && 
					screenPos.Y >= selectionRect.Y - eps)
				{
					return true;
				}
			}
			return false;
		}
		#pragma endregion

		#pragma region Member - RemoveBot
		void UnitSelection::RemoveBot(TikiBot* bot/*, UInt32 index*/)
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

				// Clear old GameObject
				gameState->GetScene()->RemoveElement(bot->GetGameObject());

				// Create new GameObject and BuildSlot
				GameObject* go = new GameObject(engine);
				gameState->GetBotFactory()->CreateBuildSlot(go);
				go->PRS.SPosition() = towerPos;

				BuildSlot* slot = go->GetComponent<BuildSlot>();
				slot->Enable();
			}
			else 
			{
				//engine->HLog.Write("Released bot go");
				gameState->GetScene()->RemoveElement(bot->GetGameObject());
			}
		}
		#pragma endregion 
	}
}
