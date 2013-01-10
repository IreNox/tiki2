
#include "Game/CameraRTS.h"

#include "Core/GameObject.h"

#include "Core/HelperLog.h"
#include <math.h>

namespace TikiEngine
{
	namespace Scripts
	{
		CameraRTS::CameraRTS(GameObject* gameObject, ITerrainRenderer* terrain)
			: IScript(gameObject->GetEngine(), gameObject), zoom(1.0f), targetZoom(1.1f)
#if _DEBUG
			, useMouse(false), useRealCamera(true)
#endif
		{
			SafeAddRef(terrain, &this->terrain);
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
			float speed = (args.Input.GetKey(KEY_LSHIFT) || args.Input.GetKey(KEY_RSHIFT) ? 60.0f : 30.0f);

			Vector2 move = Vector2(
				(args.Input.GetKey(KEY_LEFT) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_RIGHT) ? 1.0f : 0.0f),
				(args.Input.GetKey(KEY_UP) ?   -1.0f : 0.0f) + (args.Input.GetKey(KEY_DOWN) ?  1.0f : 0.0f)
			) * speed;

#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F10)) useMouse = !useMouse;
			if (args.Input.GetKeyPressed(KEY_F5))
			{
				useRealCamera = !useRealCamera;
				zoom = 0;
				targetZoom = 0;
			}

			if (useMouse)
			{
#endif
			move += Vector2(
				(args.Input.MousePosition.X < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.X > 0.99f ? 1.0f : 0.0f),
				(args.Input.MousePosition.Y < 0.01f ? -1.0f : 0.0f) + (args.Input.MousePosition.Y > 0.99f ? 1.0f : 0.0f)
			) * speed;
#if _DEBUG
			}
#endif

			float sample = terrain->SampleHeight(gameObject->PRS.GPosition());
			height = Lerp(height, sample, (float)args.Time.ElapsedTime * 2);
			height = Clamp(height, sample, 100.0f);

			float sizeOver2 = ((float)terrain->GSize() / 2) * 0.8f;

			Vector3 pos = gameObject->PRS.GPosition() + Vector3(move.X, 0, move.Y) * (float)args.Time.ElapsedTime;
			pos.X = Clamp(pos.X, -sizeOver2, sizeOver2);
			pos.Z = Clamp(pos.Z, -sizeOver2, sizeOver2);
			gameObject->PRS.SPosition() = pos;

#if _DEBUG
			if (!useRealCamera)
			{

				if (args.Input.MouseWheel != 0)
				{
					targetZoom += args.Input.MouseWheel / 10;
					targetZoom = Clamp(targetZoom, -600.0f, 100.0f);
				}

				if (abs(zoom - targetZoom) > 0.01f || move != Vector2::Zero || gameObject->PRS.IsDirty())
				{
					zoom = Lerp(zoom, targetZoom, (float)args.Time.ElapsedTime * 2);

					float rot = ((-zoom / 600) + 0.34f) / 1.34f;
					rot = Lerp(0.2f, 1.57f, rot);
					gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, -rot, 0);

					gameObject->PRS.SPosition().Y = height + (32.0f - zoom);

					//if (args.Input.MouseWheel != 0)
					//{
					//	ostringstream s;
					//	s << "Sample: " << sample << ", Zoom: " << zoom << "Rot: " << rot;
					//	engine->HLog.Write(s.str());
					//}
				}
			}
			else
			{
#endif
				if (args.Input.MouseWheel != 0)
				{
					targetZoom -= args.Input.MouseWheel / 14.157f;
					targetZoom = Clamp(targetZoom, 0.0f, 50.0f);

					//ostringstream s;
					//s << "Sample: " << sample << ", Zoom: " << zoom << ", TargetZoom: " << targetZoom;
					//engine->HLog.Write(s.str());
				}

				if (abs(zoom - targetZoom) > 0.1f || move != Vector2::Zero)
				{
					zoom = Lerp(zoom, targetZoom, (float)args.Time.ElapsedTime * 2);

					float rot = (zoom / 200) + 0.5f;
					rot = Lerp(0.2f, 1.57f, rot);
					gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, -rot, 0);

					gameObject->PRS.SPosition().Y = height + 12.0f + zoom;
				}
#if _DEBUG
			}
#endif
		}
	}
}