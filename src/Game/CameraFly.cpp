
#include "Game/CameraFly.h"

#include "Core/TypeGlobals.h"
#include "Core/UpdateArgs.h"
#include "Core/InputState.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Scripts
	{
		CameraFly::CameraFly(Engine* engine, GameObject* gameObject)
			: IScript(engine, gameObject)
		{
			camera = gameObject->GetComponent<Camera>();
		}

		CameraFly::~CameraFly()
		{
			SafeRelease(&camera);
		}

		void CameraFly::Draw(const DrawArgs& args)
		{
		}

		void CameraFly::Update(const UpdateArgs& args)
		{
			Vector2 move = Vector2(
				(args.Input.GetKey(KEY_LEFT) || args.Input.GetKey(KEY_A) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_RIGHT) || args.Input.GetKey(KEY_D) ? -1.0f : 0.0f),
				(args.Input.GetKey(KEY_UP)  || args.Input.GetKey(KEY_W) ?  1.0f : 0.0f) + (args.Input.GetKey(KEY_DOWN)  || args.Input.GetKey(KEY_S) ?  -1.0f : 0.0f)
			) * (args.Input.GetKey(KEY_LSHIFT) || args.Input.GetKey(KEY_RSHIFT) ? 50.0f : 25.0f);
			
			Vector3 pos = (gameObject->PRS.GetLeft() * move.X) + (gameObject->PRS.GetForward() * move.Y);

			gameObject->PRS.SetPosition(gameObject->PRS.GetPosition() + pos * (float)args.Time.ElapsedTime);
			gameObject->PRS.SetRotation(gameObject->PRS.GetRotation() * Quaternion::CreateFromYawPitchRoll(-args.Input.MouseDistance.X, -args.Input.MouseDistance.Y, 0));
		}
	}
}