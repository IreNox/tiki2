

#include "Game/UnitSelection.h"
#include "Game/GameState.h"

#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"


#include "Core/IGraphics.h"
#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Game
	{



		UnitSelection::UnitSelection(GameState* gameState)
		{
			this->gameState = gameState;
			selectionRect.X = 0;
			selectionRect.Y = 0;
			selectionRect.Width = 0;
			selectionRect.Height = 0;

			selectButton = new GUIButton(gameState->GetEngine());
		

		}

		UnitSelection::~UnitSelection()
		{
			//selectedUnits.Clear();
		}



		void UnitSelection::Update(const UpdateArgs& args)
		{
			// Handle Rectangle
			// Mouse left button has just been pressed down
			if (args.Input.GetMousePressed(MB_Left))
			{
				selectionStartPoint = args.Input.MousePositionDisplay;

				// Set the selection box starting point
				selectionRect.X = args.Input.MousePositionDisplay.X;
				selectionRect.Y = args.Input.MousePositionDisplay.Y;
				selectButton->Position() = Vector2(selectionRect.X, selectionRect.Y);
				
				wostringstream str;
				str << "GetKeyReleased X=" << selectionRect.X << " Y=" << selectionRect.Y << "\n";
				OutputDebugString(str.str().c_str());
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
					selectionRect.Y = args.Input.MousePositionDisplay.Y;
					selectButton->Position() = Vector2(selectionRect.X, selectionRect.Y);
				}

				selectButton->Size() = Vector2(selectionRect.Width, selectionRect.Height);

				wostringstream str;
				str << "Mouse left button dragging Width=" << selectionRect.Width << " Height=" << selectionRect.Height << "\n";
				OutputDebugString(str.str().c_str());

			}

			if (args.Input.GetMouseRelease(MB_Left))
			{
				selectionRect.X = 0;
				selectionRect.Y = 0;
				selectionRect.Width = 0;
				selectionRect.Height = 0;
				OutputDebugString(L"Reset\n");
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




					if(selectionRect.Contains(Vector2(screenPos.X, screenPos.Y)))
					{
						OutputDebugString(L"Selected unit");
						selectedUnits.Add(go);
					}
				}
				//	continue;
 


 				i++;
			}

			selectButton->Update(args);
		}

		void UnitSelection::Draw(const DrawArgs& args)
		{
			if (selectionRect.Width != 0 && selectionRect.Height != 0)
				selectButton->Draw(args);
		}


	}
}