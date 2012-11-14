
#include "Graphics/DebugConsole.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"

#include "Core/IInput.h"

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		DebugConsole::DebugConsole(Engine* engine)
			: GameObject(engine), bgTexture(0), font(0), enabled(false), lastTime(0)
		{
			UInt32 color = 0x99000000;

			bgTexture = new Texture(engine);
			bgTexture->Create(1, 1, true);
			bgTexture->SetData(0, &color, 4);
			bgTexture->AddRef();

			font = new Font(engine);
			font->Create(L"Arial", 8.0f);
			font->AddRef();

			this->Handle(
				DllMain::ModuleGraphics,
				ScreenSizeChangedArgs(DllMain::ModuleGraphics, DllMain::ModuleGraphics->GetViewPort())
			);

			HelperLog::MessageReceived.AddHandler(this);
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
			if (enabled)
			{
				bgRect.Height = 14.0f * (lines.Count() + 1);
				DllMain::ModuleSpriteBatch->Draw(bgTexture, bgRect, Color::White);

				UInt32 i = 0;
				while (i < lines.Count())
				{
					DllMain::ModuleSpriteBatch->DrawString(
						font,
						lines.GetKVP(i).GetKey(),
						Vector2(5, 14.0f * i),
						Color::White
					);

					lines[lines.GetKVP(i).GetKey()] -= args.Time.ElapsedTime;

					i++;
				}

				wostringstream s;
				s << L"> " << cmdEnter;

				DllMain::ModuleSpriteBatch->DrawString(
					font,
					s.str(),
					Vector2(5, 14.0f * i),
					Color::White
				);
			}
			else
			{
				UInt32 i = 0;
				UInt32 c = 0;
				while (i < lines.Count())
				{
					KeyValuePair<wstring, double> kvp = lines.GetKVP(i);

					if (kvp.GetValue() > 0.0f)
					{
						DllMain::ModuleSpriteBatch->DrawString(
							font,
							kvp.GetKey(),
							Vector2(5, 14.0f * c),
							Color(1.0f, 1.0f, 1.0f, min(kvp.GetValue(), 1.0))
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

			if (enabled && args.Time.TotalTime - lastTime > 0.1)
			{
				List<Key> keys = args.Input.GetKeys();
				
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
							HelperLog::Write(
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

				lastTime = args.Time.TotalTime;
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void DebugConsole::Handle(void* sender, const MessageReceivedArgs& args)
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

			return true;
		}
		#pragma endregion
	}
}