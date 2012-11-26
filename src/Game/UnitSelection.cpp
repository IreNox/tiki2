

#include "Game/UnitSelection.h"
#include "Game/GameState.h"

#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"

#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		UnitSelection::UnitSelection(GameState* gameState)
			: EngineObject(gameState->GetEngine()), gameState(gameState)
		{
			selectionRect = RectangleF::Create(0, 0, 0, 0);

			selectButton = new GUIButton(gameState->GetEngine());
			selectButton->AddRef();
		}

		UnitSelection::~UnitSelection()
		{
			selectedUnits.Clear();
			SafeRelease(&selectButton);
		}
		#pragma endregion

		#pragma region Member - Get/Draw
		List<GameObject*>* UnitSelection::GetSelectedUnits()
		{
			return &selectedUnits;
		}

		void UnitSelection::Draw(const DrawArgs& args)
		{
			if (selectionRect.Width != 0 && selectionRect.Height != 0)
				selectButton->Draw(args);
		}
		#pragma endregion

		#pragma region Member - Update
		void UnitSelection::Update(const UpdateArgs& args)
		{
			bool changed = false;

			// Handle Rectangle
			// Mouse left button has just been pressed down
			if (args.Input.GetMousePressed(MB_Left))
			{
				if (selectedUnits.Count() != 0) changed = true;
				// clear list from last selection
				selectedUnits.Clear();

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
			
			// Check entity intersection
			UInt32 i = 0;
			while (i < gameState->GetScene()->GetObjects()->Count())
			{
				GameObject* go = gameState->GetScene()->GetObjects()->Get(i);

				TikiBot* ent = go->GetComponent<TikiBot>();
				if(ent != 0)
				{
					Camera* cam = gameState->GetScene()->GetCamera();
					Vector2 bbDim = gameState->GetEngine()->graphics->GetViewPort()->GetSize();

					Matrix vp = //Matrix::CreateTranslation(cam->GetGameObject()->PRS.GPosition()) *
								Matrix::Transpose(*cam->GetViewMatrix()) * 
								Matrix::Transpose(*cam->GetProjectionMatrix());

					Vector3 screenPos = Vector3::Project(ent->Pos3D(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);
										
					if (selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)) && !selectedUnits.Contains(go))
					{
						engine->HLog.Write("Rect-Select unit.");
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
							engine->HLog.Write("click-Select unit.\n");
							selectedUnits.Add(go);
						}

					}


				}
 				i++;
			}

			selectButton->Update(args);
		}
		#pragma endregion
	}
}