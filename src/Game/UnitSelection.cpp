

#include "Game/UnitSelection.h"
#include "Game/GameState.h"

#include "Game/SensorMemory.h"
#include "Game/SceneLevel.h"

#include "Core/IGraphics.h"
#include "Game/BuildSlot.h"

#include "Game/TikiBotFactory.h"
#include "Core/IPhysics.h"

namespace TikiEngine
{

	namespace Game
	{
		#pragma region Class
		UnitSelection::UnitSelection(GameState* gameState)
			: EngineObject(gameState->GetEngine()), gameState(gameState), enabled(true), dirty(true), mouseButton(false), changed(false)
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
			if (enabled && selectionRect.Width != 0 && selectionRect.Height != 0)
				selectButton->Draw(args);
		}
		#pragma endregion

		#pragma region Member - Update
		void UnitSelection::Update(const UpdateArgs& args)
		{
			if (!enabled) return;

			this->changed = false;


			// Handle Rectangle
			// Mouse left button has just been pressed down
			if (args.Input.GetMousePressed(MB_Left))
			{
				if (selectedUnits.Count() != 0) changed = true;

				// clear list from last selection
				if (!args.Input.GetKey(KEY_LSHIFT))
				{
					selectedUnits.Clear();
					selectedSlots.Clear();
				}
				selectionStartPoint = args.Input.MousePositionDisplay;

				// Set the selection box starting point
				selectionRect.X = args.Input.MousePositionDisplay.X;
				selectionRect.Y = args.Input.MousePositionDisplay.Y;
				selectButton->SPosition() = Vector2(selectionRect.X, selectionRect.Y);
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


#if TIKI_USE_SCENEGRAPH
			this->mouseButton = args.Input.GetMouse(MB_Left);
			this->worldToScreen = gameState->GetScene()->GCamera()->WorldToScreen();

			this->gameState->GetScene()->SceneGraph.Do([&](GameObject* go){ this->HandleBuildSlot(go); });
			this->gameState->GetScene()->SceneGraph.Do([&](GameObject* go){ this->HandleTikiBot(go); });
#else
			UInt32 i = 0;
			while (i < gameState->GetScene()->GetElements().Count())
			{
				GameObject* go = gameState->GetScene()->GetElements()[i];

#pragma region SlotSelection
				BuildSlot* slot = 0;
				slot = go->GetComponent<BuildSlot>();
				if(slot != 0)
				{
					Camera* cam = gameState->GetScene()->GCamera();
					Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();

					Matrix vp = cam->WorldToScreen();
					Vector3 screenPos = Vector3::Project(slot->GetGameObject()->PRS.GPosition(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

					if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && !selectedSlots.Contains(go))
					{
						engine->HLog.Write("Rect-Select slot.");
						selectedSlots.Add(go);
						changed = true;
					}

					float eps = 15.0f;
					if (args.Input.GetMousePressed(MB_Left))
					{
						if(screenPos.X <= selectionRect.X + eps && 
							screenPos.X >= selectionRect.X - eps &&
							screenPos.Y <= selectionRect.Y + eps && 
							screenPos.Y >= selectionRect.Y - eps)
						{
							if (!selectedSlots.Contains(go))
							{
								engine->HLog.Write("click-Select slot.\n");
								selectedSlots.Add(go);
								changed = true;
							}
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
						Camera* cam = gameState->GetScene()->GCamera();
						Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();

						Matrix vp = cam->WorldToScreen(); //Matrix::CreateTranslation(cam->GetGameObject()->PRS.GPosition()) *
						//Matrix::Transpose(cam->GetViewMatrix()) * 
						//Matrix::Transpose(cam->GetProjectionMatrix());

						Vector3 screenPos = Vector3::Project(ent->Pos3D(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

						if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && !selectedUnits.Contains(go))
						{
							//engine->HLog.Write("Rect-Select unit.");
							selectedUnits.Add(go);
							changed = true;
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
								selectedUnits.Add(go);
								changed = true;
							}

						}
					}

					// check if dead and clear from list
					if (ent->IsDead())
						RemoveBot(ent);
				}
#pragma endregion


				i++;
			}
#endif

			

			if (changed)
				gameState->UnitSelectionChanged.RaiseEvent(gameState, UnitSelectionChangedArgs(&selectedUnits));

			selectButton->Update(args);
		}
		#pragma endregion

#pragma region helper

		void UnitSelection::HandleTikiBot(GameObject* go)
		{
			TikiBot* ent = go->GetComponent<TikiBot>();
			if(ent == 0)
				return;

			if(ent->GetFaction() == 0)
			{
				if(IsUnderMouse(go, this->worldToScreen) && !selectedUnits.Contains(go))
				{
					selectedUnits.Add(go);
					changed = true;
				}
			}
			if(ent->IsDead())
				RemoveBot(ent);
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

#if TIKI_USE_SCENEGRAPH
			GameObject* tmpGO = gameState->GetScene()->RemoveElement(bot->GetGameObject());

			gameState->GetScene()->SceneGraph.Do(
				[&](GameObject* go)
			{
				TikiBot* ent = go->GetComponent<TikiBot>();
				if(ent == 0)
					return;

				if(ent->EntityType() != ET_Building)
				{
					ent->GetSensorMem()->RemoveBotFromMemory(bot);

					if (ent->GetTargetSys()->GetTarget() == bot)
						ent->GetTargetSys()->ClearTarget();

					if (ent->GetTargetSys()->GetGlobalTarget() == bot)
						ent->GetTargetSys()->ClearGlobalTarget();
				}
			});


			if (selectedUnits.Contains(tmpGO))
			{
				//engine->HLog.Write("Removed dead bot from selction.");
				selectedUnits.Remove(tmpGO);
			}

			if (bot->EntityType() == ET_Tower)
			{
				//engine->HLog.Write("Dead tower, Adding Player BuiltSlot");

				// Save old tower position
				Vector3 towerPos = bot->GetController()->GetCenter();
				towerPos.Y -= (bot->GetController()->GetHeight() * 0.5f + bot->GetController()->GetRadius());

				// Clear old GameObject
				bot->GetGameObject()->Release();

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
				bot->GetGameObject()->Release();
			}
#else

			UInt32 i = 0;
			while (i < gameState->GetScene()->GetElements().Count())
			{
				GameObject* go = gameState->GetScene()->GetElements()[i];

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
				bot->GetGameObject()->Release();

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
				bot->GetGameObject()->Release();
			}

#endif

		}
		#pragma endregion 
	}
}
