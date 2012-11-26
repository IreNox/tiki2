
#include "Core/GUIControl.h"
#include "Core/GUIButton.h"
#include "Core/GUIControlRectangles.h"
#include "Core/GUICustomButton.h"
#include "Core/GUIImage.h"
#include "Core/GUILabel.h"
#include "Core/GUIWindow.h"

#include "Core/sqlite3.h"
#include "Core/ISpriteBatch.h"
#include "Core/IContentManager.h"

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace UserInterface
	{
		#pragma region GUIControl
		#pragma region Class
		GUIControl::GUIControl(Engine* engine)
			: EngineObject(engine), isDirty(true), mouseOver(false), parent(0), UserData(0)
		{
		}

		GUIControl::~GUIControl()
		{
			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Release();
				i++;
			}
			childs.Clear();
		}
		#pragma endregion

		#pragma region Member
		bool GUIControl::Clicked()
		{
			return mouseClicked;
		}

		bool GUIControl::GetReady()
		{
			return true;
		}
		#pragma endregion

		#pragma region Member - Childs
		void GUIControl::AddChild(GUIControl* child)
		{
			if (child->parent)
			{
				child->parent->RemoveChild(child);
			}

			child->parent = this;
			child->AddRef();
			childs.Add(child);
		}

		bool GUIControl::RemoveChild(GUIControl* child)
		{
			if (child->parent == this)
			{
				child->parent = 0;
				child->Release();
				return childs.Remove(child);
			}

			return false;
		}

		const List<GUIControl*>& GUIControl::ChildControls()
		{
			return childs;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		const Vector2& GUIControl::GPosition() const
		{
			return position;
		}

		Vector2& GUIControl::SPosition()
		{
			isDirty = true;
			return position;
		}

		const Vector2& GUIControl::GSize() const
		{
			return size;
		}

		Vector2& GUIControl::SSize()
		{
			isDirty = true;
			return size;
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GUIControl::Draw(const DrawArgs& args)
		{
			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Draw(args);
				i++;
			}
		}

		void GUIControl::Update(const UpdateArgs& args)
		{
			if (isDirty || (parent && parent->isDirty))
			{
				boundingBox = this->createBoundingBox();
			}

			mouseOver = boundingBox.Contains(args.Input.MousePositionDisplay);

			mouseClicked = (args.Input.GetMousePressed(MB_Left) && mouseOver);
			if (mouseClicked) this->Click.RaiseEvent(this, ClickEventArgs(this));

			UInt32 i = 0;
			while (i < childs.Count())
			{
				childs[i]->Update(args);
				i++;
			}

			isDirty = false;
		}
		#pragma endregion

		#pragma region Static Member
		IFont* GUIControl::defaultFont = 0;

		IFont* GUIControl::GetDefaultFont()
		{
			return defaultFont;
		}

		void GUIControl::SetDefaultFont(IFont* font)
		{
			SafeRelease(&defaultFont);
			SafeAddRef(font, &defaultFont);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIControl::createBoundingBox()
		{
			Vector2 base = (parent ? parent->position : Vector2::Zero);

			return RectangleF::Create(
				base.X + position.X,
				base.Y + position.Y,
				size.X,
				size.Y
			);
		}
		#pragma endregion
		#pragma endregion

		#pragma region GUIButton
		#pragma region Class
		GUIButton::GUIButton(Engine* engine)
			: GUIControl(engine)
		{
			tex = engine->content->LoadTexture(L"controls");
			tex->AddRef();

			if (rdNormal == 0)
			{
				rdNormal = new GUIControlRectangles("button_normal");
				rdHover = new GUIControlRectangles("button_hover");
				rdClick = new GUIControlRectangles("button_click");
			}

			rdNormal->AddRef();
			rdHover->AddRef();
			rdClick->AddRef();
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
			GUIControlRectangles* rd = (mouseOver ? (args.Update.Input.GetMouse(MB_Left) ? rdClick : rdHover) : rdNormal);

			GUIControlRectangles::Draw(
				engine->sprites,
				tex,
				&rects,
				rd
				);

			engine->sprites->DrawString(
				GUIControl::GetDefaultFont(),
				text,
				posText,
				Color::White
				);

			GUIControl::Draw(args);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIButton::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			Vector2 sizeText = GUIControl::GetDefaultFont()->MeasureString(text) / 2;

			posText = rect.Position() + (size / 2) - sizeText;
			rects = GUIControlRectangles(rect, rdNormal);

			return rect;
		}
		#pragma endregion

		#pragma region Static
		GUIControlRectangles* GUIButton::rdNormal = 0;
		GUIControlRectangles* GUIButton::rdHover = 0;
		GUIControlRectangles* GUIButton::rdClick = 0;		
		#pragma endregion
		#pragma endregion

		#pragma region GUIControlRectangle
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
			batch->Draw(tex, dst->rectLT, src->rectLT, Color::White);
			batch->Draw(tex, dst->rectLC, src->rectLC, Color::White);
			batch->Draw(tex, dst->rectLB, src->rectLB, Color::White);

			batch->Draw(tex, dst->rectCT, src->rectCT, Color::White);
			batch->Draw(tex, dst->rectCC, src->rectCC, Color::White);
			batch->Draw(tex, dst->rectCB, src->rectCB, Color::White);

			batch->Draw(tex, dst->rectRT, src->rectRT, Color::White);
			batch->Draw(tex, dst->rectRC, src->rectRC, Color::White);
			batch->Draw(tex, dst->rectRB, src->rectRB, Color::White);
		}
		#pragma endregion
		#pragma endregion

		#pragma region GUICustomButton
		#pragma region Class
		GUICustomButton::GUICustomButton(Engine* engine)
			: GUIControl(engine), texDefault(0), texMouseOver(0), texClick(0)
		{
		}

		GUICustomButton::~GUICustomButton()
		{
			SafeRelease(&texDefault);
			SafeRelease(&texMouseOver);
			SafeRelease(&texClick);
		}
		#pragma endregion

		#pragma region Mmeber - Get/Set
		ITexture* GUICustomButton::GetTextureDefault()
		{
			return texDefault;
		}

		void GUICustomButton::SetTextureDefault(ITexture* texture)
		{
			SafeRelease(&texDefault);
			SafeAddRef(texture, &texDefault);
		}

		ITexture* GUICustomButton::GetTextureMouseOver()
		{
			return texMouseOver;
		}

		void GUICustomButton::SetTextureMouseOver(ITexture* texture)
		{
			SafeRelease(&texMouseOver);
			SafeAddRef(texture, &texMouseOver);
		}

		ITexture* GUICustomButton::GetTextureClick()
		{
			return texClick;
		}

		void GUICustomButton::SetTextureClick(ITexture* texture)
		{
			SafeRelease(&texClick);
			SafeAddRef(texture, &texClick);
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUICustomButton::Draw(const DrawArgs& args)
		{
			if (args.Update.Input.GetMousePressed(MB_Left) && mouseOver)
			{
				engine->sprites->Draw(texClick, position);
			}
			else if (mouseOver)
			{
				engine->sprites->Draw(texMouseOver, position);
			}
			else
			{
				engine->sprites->Draw(texDefault, position);
			}
		}
		#pragma endregion
		#pragma endregion

		#pragma region GUIImage
		#pragma region Class
		GUIImage::GUIImage(Engine* engine)
			: GUIControl(engine), texture(0), textureSize()
		{
		}

		GUIImage::~GUIImage()
		{
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member
		bool GUIImage::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		ITexture* GUIImage::GetTexture()
		{
			return texture;
		}

		void GUIImage::SetTexture(ITexture* texture)
		{
			SafeRelease(&this->texture);
			SafeAddRef(texture, &this->texture);

			if (texture)
			{
				isDirty = true;
				size = texture->GetSize();
				textureSize = size;
			}
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIImage::Draw(const DrawArgs& args)
		{
			engine->sprites->Draw(
				texture,
				RectangleF::Create(
				position.X,
				position.Y,
				size.X,
				size.Y
				),
				Color::White
				);
		}
		#pragma endregion
		#pragma endregion

		#pragma region GUILable
		#pragma region Class
		GUILabel::GUILabel(Engine* engine)
			: GUIControl(engine), font(GUIControl::defaultFont)
		{
		}

		GUILabel::~GUILabel()
		{
		}
		#pragma endregion

		#pragma region Member
		bool GUILabel::GetReady()
		{
			return (font != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		IFont* GUILabel::GetFont() const
		{
			return font;
		}

		void GUILabel::SetFont(IFont* font)
		{
			SafeRelease(&this->font);
			SafeAddRef(font, &this->font);

			isDirty = true;
		}

		const wstring GUILabel::Text() const
		{
			return text;
		}

		wstring& GUILabel::Text()
		{
			isDirty = true;
			return text;
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUILabel::Draw(const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			engine->sprites->DrawString(font, text, position, Color::White);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUILabel::createBoundingBox()
		{
			if (font)
			{
				size = font->MeasureString(text);
			}
			else
			{
				size = Vector2::Zero;
			}

			return GUIControl::createBoundingBox();
		}
		#pragma endregion
		#pragma endregion

		#pragma region GUIWindow
		GUIControlRectangles* GUIWindow::rd = 0;

		#pragma region Class
		GUIWindow::GUIWindow(Engine* engine)
			: GUIControl(engine)
		{
			tex = engine->content->LoadTexture(L"controls");
			tex->AddRef();

			if (rd == 0)
			{
				rd = new GUIControlRectangles("window");
			}
			else
			{
				rd->AddRef();
			}
		}

		GUIWindow::~GUIWindow()
		{
			rd->Release();
			SafeRelease(&tex);
		}
		#pragma endregion

		#pragma region Member - Draw
		void GUIWindow::Draw(const DrawArgs& args)
		{
			GUIControlRectangles::Draw(
				engine->sprites,
				tex,
				&rects,
				rd
				);

			GUIControl::Draw(args);
		}
		#pragma endregion

		#pragma region Protected Member
		RectangleF GUIWindow::createBoundingBox()
		{
			RectangleF rect = GUIControl::createBoundingBox();

			rects = GUIControlRectangles(rect, rd);

			return rect;
		}
		#pragma endregion
		#pragma endregion
	}
}