
#include "Game/DebugConsole.h"

#include "Core/TypeDef.h"
#include "Core/IInput.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		DebugConsole::DebugConsole(Engine* engine)
			: GameObject(engine), bgTexture(0), font(0), enabled(false)
		{
			UInt32 color = 0x99000000;

			bgTexture = engine->librarys->CreateResource<ITexture>();
			bgTexture->Create(1, 1, true, PF_R8G8B8A8);
			bgTexture->SetData(PF_A8R8G8B8, &color, 4);
			bgTexture->AddRef();

			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 8.0f);
			font->AddRef();

			this->Handle(
				engine->graphics,
				ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort())
			);

			engine->HLog.MessageReceived.AddHandler(this);
			engine->graphics->ScreenSizeChanged.AddHandler(this);
		}

		DebugConsole::~DebugConsole()
		{
			SafeRelease(&font);
			SafeRelease(&bgTexture);
		}
		#pragma endregion

		#pragma region Member - Draw
		void DebugConsole::Draw(const DrawArgs& args)
		{			
			UInt32 c = 0;
			UInt32 i = (UInt32)TIKI_MAX( 0, (Int32)lines.Count( ) - 10 );

			if (enabled)
			{
				bgRect.Height = 14.0f * (lines.Count() - i + 1);
				args.SpriteBatch->Draw(bgTexture, bgRect, Color::White);

				while (i < lines.Count())
				{
					args.SpriteBatch->DrawString(
						font,
						lines.GetKVP(i).GetKey(),
						Vector2(5, 14.0f * c),
						Color::White,
						0.8f
					);

					lines[lines.GetKVP(i).GetKey()] -= args.Time.ElapsedTime;

					i++;
					c++;
				}

				args.SpriteBatch->DrawString(
					font,
					L"> " + cmdEnter,
					Vector2(5, 14.0f * c),
					Color::White,
					0.8f
				);
			}
			else
			{
				while (i < lines.Count())
				{
					KeyValuePair<wstring, double> kvp = lines.GetKVP(i);

					if (kvp.GetValue() > 0.0f)
					{
						args.SpriteBatch->DrawString(
							font,
							kvp.GetKey(),
							Vector2( 5, 14.0f * c ),
							Color( 1.0f, 1.0f, 1.0f, (float)TIKI_MIN( kvp.GetValue(), 1.0 ) )
						);

						lines[kvp.GetKey()] -= args.Time.ElapsedTime;
						c++;
					}

					i++;
				}
			}
		}
		#pragma endregion

		#pragma region Member - Update
		void DebugConsole::Update(const UpdateArgs& args)
		{
			if (args.Input.GetKeyReleased(KEY_GRAVE))
			{
				enabled = !enabled;
			}

			if (enabled)
			{
				List<Key> keys = args.Input.GetKeysPressed();
				
				UInt32 i = 0;
				while (i < keys.Count())
				{
					switch (keys[i])
					{
					case KEY_BACK:
						if (cmdEnter.Length() != 0) cmdEnter.Remove(cmdEnter.Length() - 1, 1);
						break;
					case KEY_RETURN:
						if (executeCommand())
						{
							engine->HLog.Write(
								StringWtoA(cmdEnter)
							);
							cmdEnter = L"";
						}
						break;
					}

					wchar_t c = engine->input->KeyCodeToChar(keys[i]);
					
					if (font->ContainsChar(c))
					{
						cmdEnter += c;
					}

					i++;
				}
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void DebugConsole::Handle(const HelperLog* sender, const MessageReceivedArgs& args)
		{
			lines.Add(
				StringAtoW(args.Message),
				7.5
			);
		}

		void DebugConsole::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			bgRect = RectangleF::Create(
				0,
				0,
				(float)args.CurrentViewPort->Width,
				100
			);
		}
		#pragma endregion

		#pragma region Private Member
		bool DebugConsole::executeCommand()
		{
			if (cmdEnter == L"clear")
			{
				lines.Clear();
			}
			else if (cmdEnter == L"")
			{
				return false;
			}
			else
			{
				engine->HLog.ConsoleCommand.RaiseEvent(&engine->HLog, cmdEnter);
			}

			return true;
		}
		#pragma endregion
	}
}