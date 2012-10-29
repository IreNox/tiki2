
#include "Core/GUIButton.h"

#include "Core/ISpriteBatch.h"
#include "Core/IContentManager.h"

#include "Core/sqlite3.h"

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIButton::GUIButton(Engine* engine)
			: GUIControl(engine)
		{
			tex = engine->content->LoadTexture(L"controls");

			if (rdNormal == 0)
			{
				rdNormal = new GUIButton::ButtonRectangles("button_normal");
				rdHover = new GUIButton::ButtonRectangles("button_hover");
				rdClick = new GUIButton::ButtonRectangles("button_click");
			}
			else
			{
				rdNormal->AddRef();
				rdHover->AddRef();
				rdClick->AddRef();
			}
		}

		GUIButton::~GUIButton()
		{
			SafeRelease(&tex);
			
			rdNormal->Release();
			rdHover->Release();
			rdClick->Release();
		}
		#pragma endregion

		#pragma region Member - Get/Set
		wstring GUIButton::Text() const
		{
			return text;	
		}

		wstring& GUIButton::Text()
		{
			isDirty = true;
			return text;
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIButton::Draw(const DrawArgs& args)
		{
			ButtonRectangles* rd = (mouseOver ? (args.Update.Input.GetMouse(MB_Left) ? rdClick : rdHover) : rdNormal);

			engine->sprites->DrawString(
				GUIControl::GetDefaultFont(),
				text,
				posText
			);

			engine->sprites->Draw(tex, rectLT, rd->rectLT);
			engine->sprites->Draw(tex, rectLC, rd->rectLC);
			engine->sprites->Draw(tex, rectLB, rd->rectLB);

			engine->sprites->Draw(tex, rectCT, rd->rectCT);
			engine->sprites->Draw(tex, rectCC, rd->rectCC);
			engine->sprites->Draw(tex, rectCB, rd->rectCB);

			engine->sprites->Draw(tex, rectRT, rd->rectRT);
			engine->sprites->Draw(tex, rectRC, rd->rectRC);
			engine->sprites->Draw(tex, rectRB, rd->rectRB);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIButton::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			Vector2 sizeText = GUIControl::GetDefaultFont()->MeasureString(text) / 2;

			posText = position + (size / 2) - sizeText;

			rectLT = RectangleF::Create(
				position.X,
				position.Y,
				rdNormal->rectLT.Width,
				rdNormal->rectLT.Height
			);

			rectLC = RectangleF::Create(
				position.X,
				position.Y + rdNormal->rectLT.Height,
				rdNormal->rectLC.Width,
				(rect.Height - rdNormal->rectLT.Height) - rdNormal->rectLB.Height
			);

			rectLB = RectangleF::Create(
				position.X,
				rect.Bottom() - rdNormal->rectLB.Height,
				rdNormal->rectLB.Width,
				rdNormal->rectLB.Height
			);

			rectCT = RectangleF::Create(
				position.X + rdNormal->rectLT.Width,
				position.Y,
				(rect.Width - rdNormal->rectLT.Width) - rdNormal->rectRT.Width,
				rdNormal->rectCT.Height
			);

			rectCC = RectangleF::Create(
				position.X + rdNormal->rectLC.Width,
				position.Y + rdNormal->rectLT.Height,
				(rect.Width - rdNormal->rectLC.Width) - rdNormal->rectRC.Width,
				(rect.Height - rdNormal->rectLT.Height) - rdNormal->rectCB.Height
			);

			rectCB = RectangleF::Create(
				position.X + rdNormal->rectLB.Width,
				rect.Bottom() - rdNormal->rectCB.Height,
				(rect.Width - rdNormal->rectLB.Width) - rdNormal->rectRB.Width,
				rdNormal->rectCB.Height
			);

			rectRT = RectangleF::Create(
				rect.Right() - rdNormal->rectRT.Width,
				position.Y,
				rdNormal->rectRT.Width,
				rdNormal->rectRT.Height
			);

			rectRC = RectangleF::Create(
				rect.Right() - rdNormal->rectRC.Width,
				position.Y + rdNormal->rectRT.Height,
				rdNormal->rectRC.Width,
				(rect.Height - rdNormal->rectRT.Height) - rdNormal->rectRB.Height
			);

			rectRB = RectangleF::Create(
				rect.Right() - rdNormal->rectRB.Width,
				rect.Bottom() - rdNormal->rectRB.Height,
				rdNormal->rectRB.Width,
				rdNormal->rectRB.Height
			);

			return rect;
		}
		#pragma endregion

		#pragma region Rechtangles
		GUIButton::ButtonRectangles* GUIButton::rdNormal = 0;
		GUIButton::ButtonRectangles* GUIButton::rdHover = 0;
		GUIButton::ButtonRectangles* GUIButton::rdClick = 0;

		GUIButton::ButtonRectangles::ButtonRectangles(string control)
		{
			sqlite3* db;
			sqlite3_open("Data/TikiData.sqlite", &db);

			const char* tmp = 0;
			sqlite3_stmt* state = 0;

			ostringstream sql;
			sql << "SELECT * FROM \"tiki_gui\" WHERE \"Control\" = '" << control << "';";

			int r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{					
					RectangleF* rect = new RectangleF();

					Int32 i = 0;
					Int32 count = sqlite3_column_count(state);

					while (i < count)
					{
						string name = sqlite3_column_name(state, i);

						if (name == "Top")
						{
							rect->Y = (float)sqlite3_column_double(state, i);
						}
						else if (name == "Left")
						{
							rect->X = (float)sqlite3_column_double(state, i);
						}
						else if (name == "Width")
						{
							rect->Width = (float)sqlite3_column_double(state, i);
						}
						else if (name == "Height")
						{
							rect->Height = (float)sqlite3_column_double(state, i);
						}
						else if (name == "ArrayIndex")
						{
							int index = sqlite3_column_int(state, i);

							rects[index] = *rect;
							delete(rect);

							rect = &rects[index];
						}

						i++;
					}
										
				}
				sqlite3_finalize(state);
			}
		}

		GUIButton::ButtonRectangles::~ButtonRectangles()
		{
		}
		#pragma endregion
	}
}