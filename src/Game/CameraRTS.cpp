
#include "Game/CameraRTS.h"

#include "Core/GameObject.h"

#include "Core/HelperLog.h"
#include <math.h>

namespace TikiEngine
{
	namespace Scripts
	{
		CameraRTS::CameraRTS(GameObject* gameObject, ITerrainRenderer* terrain)
			: IScript(gameObject->GetEngine(), gameObject), zoom(0.0f), targetZoom(0.0f)
		{
			SafeAddRef(terrain, &this->terrain);

			gameObject->PRS.SPosition() = Vector3(0, 192.0f, 0);
			gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, -1, 0);
		}

		CameraRTS::~CameraRTS()
		{
			SafeRelease(&terrain);
		}

		void CameraRTS::Draw(const DrawArgs& args)
		{
		}

		void CameraRTS::Update(const UpdateArgs& args)
		{
			float speed = (args.Input.GetKey(KEY_LSHIFT) || args.Input.GetKey(KEY_RSHIFT) ? 150.0f : 75.0f);

			Vector2 move = Vector2(
				(args.Input.GetKey(KEY_LEFT) || args.Input.GetKey(KEY_A) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_RIGHT) || args.Input.GetKey(KEY_D) ? 1.0f : 0.0f),
				(args.Input.GetKey(KEY_UP)  || args.Input.GetKey(KEY_W) ?  -1.0f : 0.0f) + (args.Input.GetKey(KEY_DOWN)  || args.Input.GetKey(KEY_S) ? 1.0f : 0.0f)
			) * speed;

			move += Vector2(
				(args.Input.MousePosition.X < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.X > 0.99f ? 1.0f : 0.0f),
				(args.Input.MousePosition.Y < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.Y > 0.99f ? 1.0f : 0.0f)
			) * speed;		

			gameObject->PRS.SPosition() += Vector3(move.X, 0, move.Y) * (float)args.Time.ElapsedTime;

			if (args.Input.MouseWheel != 0)
			{
				targetZoom += args.Input.MouseWheel / 10;
				targetZoom = Clamp(zoom, -260.0f, 100.0f);
			}

			zoom = Lerp(zoom, targetZoom, (float)args.Time.ElapsedTime);
			
			float rot = (-zoom / 120) + 1;
			rot = Clamp(rot, 0.2f, 1.57f);
			gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, -rot, 0);

			float sample = terrain->SampleHeight(gameObject->PRS.GPosition());
			gameObject->PRS.SPosition().Y = sample + (192.0f - zoom);

			if (args.Input.MouseWheel != 0)
			{
				ostringstream s;
				s << "Sample: " << sample << ", Zoom: " << zoom << "Rot: " << rot;

				engine->HLog.Write(s.str());
			}
		}
	}
}