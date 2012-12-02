
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

			targetZoom = -150.0f;
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
			float speed = (args.Input.GetKey(KEY_LSHIFT) || args.Input.GetKey(KEY_RSHIFT) ? 400.0f : 200.0f);

			Vector2 move = Vector2(
				(args.Input.GetKey(KEY_LEFT) || args.Input.GetKey(KEY_A) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_RIGHT) || args.Input.GetKey(KEY_D) ? 1.0f : 0.0f),
				(args.Input.GetKey(KEY_UP)  || args.Input.GetKey(KEY_W) ?  -1.0f : 0.0f) + (args.Input.GetKey(KEY_DOWN)  || args.Input.GetKey(KEY_S) ? 1.0f : 0.0f)
			) * speed;

			move += Vector2(
				(args.Input.MousePosition.X < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.X > 0.99f ? 1.0f : 0.0f),
				(args.Input.MousePosition.Y < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.Y > 0.99f ? 1.0f : 0.0f)
			) * speed;		

			float sizeOver2 = ((float)terrain->GSize() / 2) * 0.8f;

			Vector3 pos = gameObject->PRS.GPosition() + Vector3(move.X, 0, move.Y) * (float)args.Time.ElapsedTime;
			pos.X = Clamp(pos.X, -sizeOver2, sizeOver2);
			pos.Z = Clamp(pos.Z, -sizeOver2, sizeOver2);
			gameObject->PRS.SPosition() = pos;

			if (args.Input.MouseWheel != 0)
			{
				targetZoom += args.Input.MouseWheel / 10;
				targetZoom = Clamp(targetZoom, -600.0f, 100.0f);
			}

			if (abs(zoom - targetZoom) > 0.01f)
			{
				zoom = Lerp(zoom, targetZoom, (float)args.Time.ElapsedTime * 2);

				float rot = ((-zoom / 600) + 0.34f) / 1.34f;
				rot = Lerp(0.2f, 1.57f, rot);
				gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, -rot, 0);

				float sample = terrain->SampleHeight(gameObject->PRS.GPosition());
				height = Lerp(height, sample, (float)args.Time.ElapsedTime * 2);
				height = Clamp(height, sample, 1000.0f);
				gameObject->PRS.SPosition().Y = height + (164.0f - zoom);

				//if (args.Input.MouseWheel != 0)
				//{
				//	ostringstream s;
				//	s << "Sample: " << sample << ", Zoom: " << zoom << "Rot: " << rot;
				//	engine->HLog.Write(s.str());
				//}
			}
		}
	}
}