
#include "Core/GUIControlRectangles.h"

#include "Core/sqlite3.h"

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region Class
		GUIControlRectangles::GUIControlRectangles()
		{		
		}

		GUIControlRectangles::~GUIControlRectangles()
		{
		}
		#pragma endregion

		#pragma region Class - Database
		GUIControlRectangles::GUIControlRectangles(string control)
		{
			sqlite3* db;
			sqlite3_open("Data/TikiData.sqlite", &db);

			const char* tmp = 0;
			sqlite3_stmt* state = 0;

			ostringstream sql;
			sql << "SELECT * FROM \"tiki_gui\" WHERE \"Control\" = '" << control << "';";

			int r = sqlite3_prepare(db, sql.str().c_str(), (int)sql.str().size(), &state, &tmp);

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

			sqlite3_close(db);
		}
		#pragma endregion

		#pragma region Class - From Source Rectangles
		GUIControlRectangles::GUIControlRectangles(const RectangleF& destRect, GUIControlRectangles* srcRects)
		{	
			rectLT = RectangleF::Create(
				destRect.X,
				destRect.Y,
				srcRects->rectLT.Width,
				srcRects->rectLT.Height
			);

			rectLC = RectangleF::Create(
				destRect.X,
				destRect.Y + srcRects->rectLT.Height,
				srcRects->rectLC.Width,
				(destRect.Height - srcRects->rectLT.Height) - srcRects->rectLB.Height
			);

			rectLB = RectangleF::Create(
				destRect.X,
				destRect.Bottom() - srcRects->rectLB.Height,
				srcRects->rectLB.Width,
				srcRects->rectLB.Height
			);

			rectCT = RectangleF::Create(
				destRect.X + srcRects->rectLT.Width,
				destRect.Y,
				(destRect.Width - srcRects->rectLT.Width) - srcRects->rectRT.Width,
				srcRects->rectCT.Height
			);

			rectCC = RectangleF::Create(
				destRect.X + srcRects->rectLC.Width,
				destRect.Y + srcRects->rectLT.Height,
				(destRect.Width - srcRects->rectLC.Width) - srcRects->rectRC.Width,
				(destRect.Height - srcRects->rectLT.Height) - srcRects->rectCB.Height
			);

			rectCB = RectangleF::Create(
				destRect.X + srcRects->rectLB.Width,
				destRect.Bottom() - srcRects->rectCB.Height,
				(destRect.Width - srcRects->rectLB.Width) - srcRects->rectRB.Width,
				srcRects->rectCB.Height
			);

			rectRT = RectangleF::Create(
				destRect.Right() - srcRects->rectRT.Width,
				destRect.Y,
				srcRects->rectRT.Width,
				srcRects->rectRT.Height
			);

			rectRC = RectangleF::Create(
				destRect.Right() - srcRects->rectRC.Width,
				destRect.Y + srcRects->rectRT.Height,
				srcRects->rectRC.Width,
				(destRect.Height - srcRects->rectRT.Height) - srcRects->rectRB.Height
			);

			rectRB = RectangleF::Create(
				destRect.Right() - srcRects->rectRB.Width,
				destRect.Bottom() - srcRects->rectRB.Height,
				srcRects->rectRB.Width,
				srcRects->rectRB.Height
			);
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIControlRectangles::Draw(ISpriteBatch* batch, ITexture* tex, GUIControlRectangles* dst, GUIControlRectangles* src)
		{
			batch->Draw(tex, dst->rectLT, src->rectLT);
			batch->Draw(tex, dst->rectLC, src->rectLC);
			batch->Draw(tex, dst->rectLB, src->rectLB);

			batch->Draw(tex, dst->rectCT, src->rectCT);
			batch->Draw(tex, dst->rectCC, src->rectCC);
			batch->Draw(tex, dst->rectCB, src->rectCB);

			batch->Draw(tex, dst->rectRT, src->rectRT);
			batch->Draw(tex, dst->rectRC, src->rectRC);
			batch->Draw(tex, dst->rectRB, src->rectRB);
		}
		#pragma endregion
	}
}