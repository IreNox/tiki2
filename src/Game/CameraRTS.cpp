
#include "Game/CameraRTS.h"

#include "Core/UpdateArgs.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Scripts
	{
		CameraRTS::CameraRTS(Engine* engine, GameObject* gameObject)
			: IScript(engine, gameObject)
		{
			gameObject->PRS.Position.Y = 192.0f;
			gameObject->PRS.Rotation *= Quaternion::CreateFromYawPitchRoll(0, -1, 0);
		}

		CameraRTS::~CameraRTS()
		{
		}

		void CameraRTS::Draw(const DrawArgs& args)
		{
		}

		void CameraRTS::Update(const UpdateArgs& args)
		{
			Vector2 move = Vector2(
				(args.Input.GetKey(KEY_LEFT) || args.Input.GetKey(KEY_A) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_RIGHT) || args.Input.GetKey(KEY_D) ? -1.0f : 0.0f),
				(args.Input.GetKey(KEY_UP)  || args.Input.GetKey(KEY_W) ?  1.0f : 0.0f) + (args.Input.GetKey(KEY_DOWN)  || args.Input.GetKey(KEY_S) ?  -1.0f : 0.0f)
			) * (args.Input.GetKey(KEY_LSHIFT) || args.Input.GetKey(KEY_RSHIFT) ? 150.0f : 75.0f);

			gameObject->PRS.Position += ((Vector3::Left * move.X) + (Vector3::ForwardRH * move.Y)) * (float)args.Time.ElapsedTime;

			float speed = 200.0f * (float)args.Time.ElapsedTime;

			if (args.Input.MousePosition.X == 0)
			{
				gameObject->PRS.Position.X -= speed;
			}
			else if (args.Input.MousePosition.X == 1)
			{
				gameObject->PRS.Position.X += speed;
			}
			else if (args.Input.MousePosition.Y == 0)
			{
				gameObject->PRS.Position.Z -= speed;
			}
			else if (args.Input.MousePosition.Y == 1)
			{
				gameObject->PRS.Position.Z += speed;
			}
		}
	}
}