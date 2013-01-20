
#include "Graphics/DebugConsole.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"

#include "Core/IInput.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		DebugConsole::DebugConsole(Engine* engine)
			: GameObject(engine), bgTexture(0), font(0), enabled(false)
		{
			UInt32 color = 0x99000000;

			bgTexture = new Texture(engine);
			bgTexture->Create(1, 1, true, PF_R8G8B8A8);
			bgTexture->SetData(PF_A8R8G8B8, &color, 4);
			bgTexture->AddRef();

			font = new Font(engine);
			font->Create(L"Arial", 8.0f);
			font->AddRef();

			this->Handle(
				DllMain::ModuleGraphics,
				ScreenSizeChangedArgs(DllMain::ModuleGraphics, DllMain::ModuleGraphics->GetViewPort())
			);

			engine->HLog.MessageReceived.AddHandler(this);
			DllMain::ModuleGraphics->ScreenSizeChanged.AddHandler(this);
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
			UInt32 i = (UInt32)max(0, (Int32)lines.Count() - 10);

			if (enabled)
			{
				bgRect.Height = 14.0f * (lines.Count() - i + 1);
				DllMain::ModuleSpriteBatch->Draw(bgTexture, bgRect, Color::White);

				while (i < lines.Count())
				{
					DllMain::ModuleSpriteBatch->DrawString(
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

				wostringstream s;
				s << L"> " << cmdEnter;

				DllMain::ModuleSpriteBatch->DrawString(
					font,
					s.str(),
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
						DllMain::ModuleSpriteBatch->DrawString(
							font,
							kvp.GetKey(),
							Vector2(5, 14.0f * c),
							Color(1.0f, 1.0f, 1.0f, (float)min(kvp.GetValue(), 1.0))
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
						if (cmdEnter.length() != 0) cmdEnter.pop_back();
						break;
					case KEY_RETURN:
						if (executeCommand())
						{
							engine->HLog.Write(
								StringWtoA(cmdEnter)
							);
							cmdEnter.erase();
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